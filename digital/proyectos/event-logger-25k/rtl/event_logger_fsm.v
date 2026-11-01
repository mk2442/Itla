`timescale 1ns / 1ps

module event_logger_fsm (
    input  wire       clk,
    input  wire       rst,
    input  wire       arm_pulse,
    input  wire       capture_pulse,
    input  wire       tx_pulse,
    input  wire       clear_pulse,
    input  wire       mem_full,
    input  wire       uart_busy,
    output reg        capture_en,
    output reg        tx_start,
    output reg        armed_led,
    output wire [1:0] state_out
);

    localparam S_IDLE    = 2'b00;
    localparam S_ARMED   = 2'b01;
    localparam S_CAPTURE = 2'b10;
    localparam S_TX      = 2'b11;

    reg [1:0] state;
    reg [1:0] next_state;

    assign state_out = state;

    always @(posedge clk) begin
        if (rst) begin
            state <= S_IDLE;
        end else begin
            state <= next_state;
        end
    end

    always @(*) begin
        next_state = state;
        case (state)
            S_IDLE: begin
                if (clear_pulse) begin
                    next_state = S_IDLE;
                end else if (arm_pulse) begin
                    next_state = S_ARMED;
                end
            end

            S_ARMED: begin
                if (clear_pulse) begin
                    next_state = S_IDLE;
                end else if (mem_full) begin
                    next_state = S_ARMED;
                end else if (capture_pulse) begin
                    next_state = S_CAPTURE;
                end else if (tx_pulse) begin
                    next_state = S_TX;
                end
            end

            S_CAPTURE: begin
                if (clear_pulse) begin
                    next_state = S_IDLE;
                end else begin
                    next_state = S_ARMED;
                end
            end

            S_TX: begin
                if (clear_pulse) begin
                    next_state = S_IDLE;
                end else if (uart_busy) begin
                    next_state = S_ARMED;
                end
            end

            default: next_state = S_IDLE;
        endcase
    end

    always @(*) begin
        capture_en = 1'b0;
        tx_start   = 1'b0;
        armed_led  = 1'b0;
        case (state)
            S_CAPTURE: capture_en = 1'b1;
            S_TX:      tx_start   = 1'b1;
            default: begin end
        endcase
        if (state == S_ARMED || state == S_CAPTURE || state == S_TX) begin
            armed_led = 1'b1;
        end
    end

endmodule
