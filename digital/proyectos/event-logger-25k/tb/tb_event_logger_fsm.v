`timescale 1ns / 1ps

module tb_event_logger_fsm;

    reg clk;
    reg rst;
    reg arm_pulse;
    reg capture_pulse;
    reg tx_pulse;
    reg clear_pulse;
    reg mem_full;
    reg uart_busy;
    wire capture_en;
    wire tx_start;
    wire armed_led;
    wire [1:0] state_out;

    event_logger_fsm uut (
        .clk(clk),
        .rst(rst),
        .arm_pulse(arm_pulse),
        .capture_pulse(capture_pulse),
        .tx_pulse(tx_pulse),
        .clear_pulse(clear_pulse),
        .mem_full(mem_full),
        .uart_busy(uart_busy),
        .capture_en(capture_en),
        .tx_start(tx_start),
        .armed_led(armed_led),
        .state_out(state_out)
    );

    always #5 clk = ~clk;

    integer error_count;

    task check_state(input [63:0] msg, input [1:0] expected_state,
                     input exp_capture, input exp_tx, input exp_armed);
        if (state_out !== expected_state) begin
            $display("ERROR: %s - state=%b, expected %b", msg, state_out, expected_state);
            error_count = error_count + 1;
        end
        if (capture_en !== exp_capture) begin
            $display("ERROR: %s - capture_en=%b, expected %b", msg, capture_en, exp_capture);
            error_count = error_count + 1;
        end
        if (tx_start !== exp_tx) begin
            $display("ERROR: %s - tx_start=%b, expected %b", msg, tx_start, exp_tx);
            error_count = error_count + 1;
        end
        if (armed_led !== exp_armed) begin
            $display("ERROR: %s - armed_led=%b, expected %b", msg, armed_led, exp_armed);
            error_count = error_count + 1;
        end
    endtask

    initial begin
        $dumpfile("tb_event_logger_fsm.vcd");
        $dumpvars(0, tb_event_logger_fsm);

        clk = 0;
        rst = 1;
        arm_pulse = 0;
        capture_pulse = 0;
        tx_pulse = 0;
        clear_pulse = 0;
        mem_full = 0;
        uart_busy = 0;
        error_count = 0;

        #10 rst = 0;
        @(posedge clk);

        check_state("After reset - IDLE", 2'b00, 0, 0, 0);

        arm_pulse = 1;
        @(posedge clk);
        arm_pulse = 0;
        @(posedge clk);
        check_state("After arm - ARMED", 2'b01, 0, 0, 1);

        capture_pulse = 1;
        @(posedge clk);
        capture_pulse = 0;
        @(posedge clk);
        check_state("After capture - CAPTURE then back to ARMED", 2'b01, 0, 0, 1);

        tx_pulse = 1;
        @(posedge clk);
        check_state("After tx - TX", 2'b11, 0, 1, 1);
        uart_busy = 1;
        @(posedge clk);
        check_state("UART busy - back to ARMED", 2'b01, 0, 0, 1);
        uart_busy = 0;

        clear_pulse = 1;
        @(posedge clk);
        clear_pulse = 0;
        @(posedge clk);
        check_state("After clear - IDLE", 2'b00, 0, 0, 0);

        arm_pulse = 1;
        @(posedge clk);
        arm_pulse = 0;
        @(posedge clk);
        check_state("Re-arm - ARMED", 2'b01, 0, 0, 1);

        mem_full = 1;
        capture_pulse = 1;
        @(posedge clk);
        capture_pulse = 0;
        @(posedge clk);
        check_state("Mem full + capture - stay ARMED", 2'b01, 0, 0, 1);
        mem_full = 0;

        clear_pulse = 1;
        arm_pulse = 1;
        @(posedge clk);
        clear_pulse = 0;
        arm_pulse = 0;
        @(posedge clk);
        check_state("Clear from IDLE - stays IDLE", 2'b00, 0, 0, 0);

        arm_pulse = 1;
        @(posedge clk);
        arm_pulse = 0;
        @(posedge clk);

        clear_pulse = 1;
        tx_pulse = 1;
        @(posedge clk);
        clear_pulse = 0;
        tx_pulse = 0;
        check_state("Clear has priority over tx - IDLE", 2'b00, 0, 0, 0);

        if (error_count == 0) begin
            $display("PASS: tb_event_logger_fsm passed all checks");
        end else begin
            $display("FAIL: tb_event_logger_fsm had %0d errors", error_count);
        end

        $finish;
    end

endmodule
