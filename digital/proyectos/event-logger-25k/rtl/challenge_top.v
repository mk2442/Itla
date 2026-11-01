`timescale 1ns / 1ps

module challenge_top #(
    parameter CLKS_PER_BIT  = 434,
    parameter STABLE_CYCLES = 100,
    parameter COUNTER_WIDTH = 8,
    parameter SCAN_PERIOD   = 1000,
    parameter SEG_ACTIVE_LOW = 1'b0,
    parameter BTN_ACTIVE_LOW = 1'b0,
    parameter LED_ACTIVE_LOW = 1'b0
)(
    input  wire       i_clk,
    input  wire       i_rst_n,
    input  wire [3:0] i_button,
    input  wire [3:0] i_switch,
    output wire [7:0] o_led,
    output wire [6:0] o_seg,
    output wire       o_sel,
    output wire       o_sel2,
    output wire       o_uart_tx
);

    wire rst;
    assign rst = ~i_rst_n;

    wire [3:0] button_high;
    wire [3:0] button_sync;
    wire [3:0] button_pulse;
    wire [3:0] button_level;

    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : btn_gen
            assign button_high[i] = BTN_ACTIVE_LOW ? ~i_button[i] : i_button[i];
            sync_2ff #(.WIDTH(1)) sync_inst (
                .clk(i_clk),
                .rst(rst),
                .async_in(button_high[i]),
                .sync_out(button_sync[i])
            );
            debounce_onepulse #(
                .STABLE_CYCLES(STABLE_CYCLES),
                .COUNTER_WIDTH(COUNTER_WIDTH)
            ) debounce_inst (
                .clk(i_clk),
                .rst(rst),
                .noisy_in(button_sync[i]),
                .level(button_level[i]),
                .pulse(button_pulse[i])
            );
        end
    endgenerate

    wire       capture_en;
    wire       tx_start;
    wire       armed_led;
    wire [1:0] state_out;
    wire       mem_full;
    wire       uart_busy;

    wire [3:0] event_code;
    wire       event_valid;
    wire [7:0] led_onehot;

    event_code_comb event_comb_inst (
        .switches(i_switch),
        .capture_request(capture_en),
        .event_code(event_code),
        .event_valid(event_valid),
        .led_onehot(led_onehot)
    );

    event_logger_fsm fsm_inst (
        .clk(i_clk),
        .rst(rst),
        .arm_pulse(button_pulse[0]),
        .capture_pulse(button_pulse[1]),
        .tx_pulse(button_pulse[2]),
        .clear_pulse(button_pulse[3]),
        .mem_full(mem_full),
        .uart_busy(uart_busy),
        .capture_en(capture_en),
        .tx_start(tx_start),
        .armed_led(armed_led),
        .state_out(state_out)
    );

    wire       increment;
    assign increment = capture_en;

    wire [4:0] write_addr;

    reg [5:0] event_count;

    write_pointer wp_inst (
        .clk(i_clk),
        .rst(rst),
        .increment(increment),
        .clear(button_pulse[3]),
        .write_addr(write_addr),
        .full(mem_full)
    );

    always @(posedge i_clk) begin
        if (rst || button_pulse[3]) begin
            event_count <= 0;
        end else if (capture_en && !mem_full) begin
            event_count <= event_count + 1;
        end
    end

    reg  [3:0] last_event_captured;
    wire [3:0] last_event;

    always @(posedge i_clk) begin
        if (rst) begin
            last_event_captured <= 0;
        end else if (capture_en && !mem_full) begin
            last_event_captured <= event_code;
        end
    end

    wire [3:0] ram_dout;

    ram32x4 ram_inst (
        .clk(i_clk),
        .we(capture_en),
        .addr(write_addr),
        .din(event_code),
        .dout(ram_dout)
    );

    assign last_event = last_event_captured;

    wire [7:0] ascii_data;
    hex_to_ascii ascii_inst (
        .hex_in(last_event),
        .ascii_out(ascii_data)
    );

    wire uart_done;

    uart_tx #(
        .CLKS_PER_BIT(CLKS_PER_BIT)
    ) uart_inst (
        .clk(i_clk),
        .rst(rst),
        .start(tx_start),
        .data(ascii_data),
        .tx(o_uart_tx),
        .busy(uart_busy),
        .done(uart_done)
    );

    wire [6:0] seg_units;
    wire [6:0] seg_tens;

    sevenseg_decoder #(
        .SEG_ACTIVE_LOW(SEG_ACTIVE_LOW)
    ) units_decoder (
        .hex_in(last_event),
        .blank(event_count == 0),
        .seg(seg_units)
    );

    sevenseg_decoder #(
        .SEG_ACTIVE_LOW(SEG_ACTIVE_LOW)
    ) tens_decoder (
        .hex_in(event_count[3:0]),
        .blank(1'b0),
        .seg(seg_tens)
    );

    wire scan_tick;

    tick_enable #(
        .PERIOD(SCAN_PERIOD),
        .COUNTER_WIDTH(16)
    ) scan_tick_inst (
        .clk(i_clk),
        .rst(rst),
        .tick(scan_tick)
    );

    sevenseg_mux2 #(
        .SEG_ACTIVE_LOW(SEG_ACTIVE_LOW)
    ) display_mux (
        .clk(i_clk),
        .rst(rst),
        .scan_tick(scan_tick),
        .seg_units(seg_units),
        .seg_tens(seg_tens),
        .blank_units(event_count == 0),
        .blank_tens(1'b0),
        .seg(o_seg),
        .sel(o_sel),
        .sel2(o_sel2)
    );

    wire [7:0] led_int;

    assign led_int[1:0] = state_out;
    assign led_int[2]   = mem_full;
    assign led_int[3]   = uart_busy;
    assign led_int[4]   = armed_led;
    assign led_int[7:5] = led_onehot[7:5];

    assign o_led = LED_ACTIVE_LOW ? ~led_int : led_int;

endmodule
