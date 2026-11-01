`timescale 1ns / 1ps

module tb_tick_enable;

    reg clk;
    reg rst;
    wire tick;

    tick_enable #(.PERIOD(4)) uut (
        .clk(clk),
        .rst(rst),
        .tick(tick)
    );

    always #5 clk = ~clk;

    integer error_count;
    integer cycle;

    initial begin
        $dumpfile("tb_tick_enable.vcd");
        $dumpvars(0, tb_tick_enable);

        clk = 0;
        rst = 1;
        error_count = 0;
        cycle = 0;

        #10 rst = 0;

        for (cycle = 0; cycle < 20; cycle = cycle + 1) begin
            @(posedge clk);
            if (cycle == 0 && tick !== 0) begin
                $display("ERROR cycle %0d: tick=1, expected 0 (just after reset)", cycle);
                error_count = error_count + 1;
            end
            if (cycle > 0 && (cycle % 4) == 0) begin
                if (tick !== 1) begin
                    $display("ERROR cycle %0d: tick=0, expected 1 (period %0d)", cycle, cycle/4);
                    error_count = error_count + 1;
                end
            end else begin
                if (tick !== 0) begin
                    $display("ERROR cycle %0d: tick=1, expected 0", cycle);
                    error_count = error_count + 1;
                end
            end
        end

        rst = 1;
        @(posedge clk);
        @(posedge clk);
        if (tick !== 0) begin
            $display("ERROR after reset: tick should be 0");
            error_count = error_count + 1;
        end
        rst = 0;

        @(posedge clk);
        if (tick !== 0) begin
            $display("ERROR cycle after reset: tick should be 0");
            error_count = error_count + 1;
        end

        if (error_count == 0) begin
            $display("PASS: tb_tick_enable passed all checks");
        end else begin
            $display("FAIL: tb_tick_enable had %0d errors", error_count);
        end

        $finish;
    end

endmodule
