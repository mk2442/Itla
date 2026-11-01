`timescale 1ns / 1ps

module tb_ram32x4;

    reg clk;
    reg we;
    reg [4:0] addr;
    reg [3:0] din;
    wire [3:0] dout;

    ram32x4 uut (
        .clk(clk),
        .we(we),
        .addr(addr),
        .din(din),
        .dout(dout)
    );

    always #5 clk = ~clk;

    integer error_count;

    task write_mem(input [4:0] waddr, input [3:0] wdata);
        @(posedge clk);
        addr = waddr;
        din = wdata;
        we = 1;
        @(posedge clk);
        we = 0;
    endtask

    task read_mem(input [4:0] raddr, input [3:0] expected);
        @(posedge clk);
        addr = raddr;
        we = 0;
        @(posedge clk);
        if (dout !== expected) begin
            $display("ERROR: Read addr %0d = %h, expected %h", raddr, dout, expected);
            error_count = error_count + 1;
        end else begin
            $display("OK: Read addr %0d = %h", raddr, dout);
        end
    endtask

    initial begin
        $dumpfile("tb_ram32x4.vcd");
        $dumpvars(0, tb_ram32x4);

        clk = 0;
        we = 0;
        addr = 0;
        din = 0;
        error_count = 0;

        #10;

        write_mem(3, 4'hA);
        read_mem(3, 4'hA);

        write_mem(7, 4'h5);
        read_mem(7, 4'h5);

        read_mem(3, 4'hA);

        write_mem(0, 4'hF);
        read_mem(0, 4'hF);

        write_mem(31, 4'h1);
        read_mem(31, 4'h1);

        read_mem(7, 4'h5);

        $display("Testing dout changes with registered read:");
        addr = 3;
        we = 0;
        @(posedge clk);
        if (dout !== 4'hA) begin
            $display("ERROR: addr=3 should still be A, got %h", dout);
            error_count = error_count + 1;
        end
        addr = 0;
        @(posedge clk);
        if (dout !== 4'hF) begin
            $display("ERROR: addr=0 should be F, got %h", dout);
            error_count = error_count + 1;
        end

        $display("Testing write at addr 5 with value 7, then read:");
        write_mem(5, 4'h7);
        read_mem(5, 4'h7);

        if (error_count == 0) begin
            $display("PASS: tb_ram32x4 passed all checks");
        end else begin
            $display("FAIL: tb_ram32x4 had %0d errors", error_count);
        end

        $finish;
    end

endmodule
