`timescale 1ns / 1ps

module tb_cdc_pulse_toggle;

    reg src_clk;
    reg src_rst;
    reg src_pulse;
    reg dst_clk;
    reg dst_rst;
    wire dst_pulse;

    cdc_pulse_toggle uut (
        .src_clk(src_clk),
        .src_rst(src_rst),
        .src_pulse(src_pulse),
        .dst_clk(dst_clk),
        .dst_rst(dst_rst),
        .dst_pulse(dst_pulse)
    );

    always #5 src_clk = ~src_clk;
    always #13 dst_clk = ~dst_clk;

    integer error_count;
    integer dst_pulse_count;

    initial begin
        $dumpfile("tb_cdc_pulse_toggle.vcd");
        $dumpvars(0, tb_cdc_pulse_toggle);

        src_clk = 0;
        src_rst = 1;
        src_pulse = 0;
        dst_clk = 0;
        dst_rst = 1;
        error_count = 0;

        #10 src_rst = 0;
        #10 dst_rst = 0;

        @(posedge src_clk);

        if (dst_pulse !== 0) begin
            $display("ERROR: dst_pulse should be 0 after reset");
            error_count = error_count + 1;
        end

        src_pulse = 1;
        @(posedge src_clk);
        src_pulse = 0;

        repeat (10) @(posedge dst_clk);
        if (dst_pulse !== 0) begin
            $display("ERROR: Expected dst_pulse=0 after 10 dst_clk cycles");
            error_count = error_count + 1;
        end else begin
            $display("OK: dst_pulse captured correctly");
        end

        repeat (10) @(posedge src_clk);
        src_pulse = 1;
        @(posedge src_clk);
        src_pulse = 0;

        repeat (10) @(posedge dst_clk);
        dst_pulse_count = 0;
        repeat (10) @(posedge dst_clk) begin
            if (dst_pulse) dst_pulse_count = dst_pulse_count + 1;
        end

        if (dst_pulse_count !== 1) begin
            $display("ERROR: Expected exactly 1 dst_pulse, got %0d", dst_pulse_count);
            error_count = error_count + 1;
        end else begin
            $display("OK: Single pulse detected in dst domain");
        end

        repeat (10) @(posedge src_clk);

        begin : seq_test
            integer i;
            for (i = 0; i < 5; i = i + 1) begin
                src_pulse = 1;
                @(posedge src_clk);
                src_pulse = 0;
                repeat (5) @(posedge src_clk);
            end
        end

        repeat (30) @(posedge dst_clk);
        dst_pulse_count = 0;
        repeat (30) @(posedge dst_clk) begin
            if (dst_pulse) dst_pulse_count = dst_pulse_count + 1;
        end

        if (dst_pulse_count !== 5) begin
            $display("ERROR: Expected 5 dst_pulses for 5 src_pulses, got %0d", dst_pulse_count);
            error_count = error_count + 1;
        end else begin
            $display("OK: All 5 pulses transferred correctly");
        end

        if (error_count == 0) begin
            $display("PASS: tb_cdc_pulse_toggle passed all checks");
        end else begin
            $display("FAIL: tb_cdc_pulse_toggle had %0d errors", error_count);
        end

        $finish;
    end

endmodule
