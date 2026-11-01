`timescale 1ns / 1ps

module tb_debounce_onepulse;

    reg clk;
    reg rst;
    reg noisy_in;
    wire level;
    wire pulse;

    debounce_onepulse #(
        .STABLE_CYCLES(5),
        .COUNTER_WIDTH(4)
    ) uut (
        .clk(clk),
        .rst(rst),
        .noisy_in(noisy_in),
        .level(level),
        .pulse(pulse)
    );

    always #5 clk = ~clk;

    integer error_count;

    task check(input [63:0] msg, input expected_level, input expected_pulse);
        if (level !== expected_level || pulse !== expected_pulse) begin
            $display("ERROR: %s - level=%b (exp %b), pulse=%b (exp %b)",
                     msg, level, expected_level, pulse, expected_pulse);
            error_count = error_count + 1;
        end
    endtask

    initial begin
        $dumpfile("tb_debounce_onepulse.vcd");
        $dumpvars(0, tb_debounce_onepulse);

        clk = 0;
        rst = 1;
        noisy_in = 0;
        error_count = 0;

        #10 rst = 0;

        @(posedge clk);

        check("After reset", 0, 0);

        noisy_in = 1;
        repeat (4) @(posedge clk);
        check("Before stable (4 cycles)", 0, 0);

        @(posedge clk);
        check("After 5 stable cycles - level high", 1, 1);

        @(posedge clk);
        check("Next cycle - pulse should be 0", 1, 0);

        noisy_in = 0;
        repeat (5) @(posedge clk);
        check("Release - level low, no pulse", 0, 0);
        @(posedge clk);
        check("After release - no extra pulse", 0, 0);

        noisy_in = 1;
        repeat (10) @(posedge clk);
        check("Long press - level high, no extra pulse", 1, 0);

        noisy_in = 0;
        repeat (5) @(posedge clk);
        check("Release after long press", 0, 0);

        noisy_in = 1;
        repeat (2) @(posedge clk);
        noisy_in = 0;
        repeat (2) @(posedge clk);
        check("Bounce - not stable yet", 0, 0);

        noisy_in = 1;
        repeat (2) @(posedge clk);
        noisy_in = 0;
        repeat (10) @(posedge clk);
        check("Bounce - never went stable, level stays 0", 0, 0);

        noisy_in = 1;
        repeat (5) @(posedge clk);
        check("Press after bouncing", 1, 1);
        @(posedge clk);
        check("No extra pulse after press", 1, 0);

        if (error_count == 0) begin
            $display("PASS: tb_debounce_onepulse passed all checks");
        end else begin
            $display("FAIL: tb_debounce_onepulse had %0d errors", error_count);
        end

        $finish;
    end

endmodule
