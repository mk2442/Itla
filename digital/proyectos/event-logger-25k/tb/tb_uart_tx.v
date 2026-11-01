`timescale 1ns / 1ps

module tb_uart_tx;

    reg clk;
    reg rst;
    reg start;
    reg [7:0] data;
    wire tx;
    wire busy;
    wire done;

    uart_tx #(
        .CLKS_PER_BIT(8),
        .COUNTER_WIDTH(8)
    ) uut (
        .clk(clk),
        .rst(rst),
        .start(start),
        .data(data),
        .tx(tx),
        .busy(busy),
        .done(done)
    );

    always #5 clk = ~clk;

    integer error_count;
    integer bit_pos;
    reg [7:0] recv_data;
    reg [15:0] bit_samples;

    task verify_frame(input [7:0] expected_data);
        integer i;
        reg [15:0] samples;
        reg expected_bit;
        begin
            @(posedge clk);
            if (busy !== 1) begin
                $display("ERROR: should be busy after start");
                error_count = error_count + 1;
            end

            bit_samples = 0;
            for (i = 0; i < 10 * 8; i = i + 1) begin
                @(posedge clk);
                if (busy) begin
                    bit_samples = {bit_samples[14:0], tx};
                end
            end

            if (done !== 1 && busy !== 0) begin
                $display("ERROR: done expected at end, got busy=%b done=%b", busy, done);
                error_count = error_count + 1;
            end

            $display("Tx samples: %b", bit_samples);

            if (bit_samples[7:0] !== 8'b0) begin
                $display("ERROR: start bit should be 0, got start region=%b", bit_samples[7:0]);
                error_count = error_count + 1;
            end

            recv_data = 0;
            for (i = 0; i < 8; i = i + 1) begin
                expected_bit = (expected_data >> i) & 1;
                if (bit_samples[8*(i+1)] !== expected_bit) begin
                    $display("ERROR: data bit %0d = %b, expected %b (data=0x%h)",
                             i, bit_samples[8*(i+1)], expected_bit, expected_data);
                    error_count = error_count + 1;
                end
                recv_data[i] = bit_samples[8*(i+1)];
            end

            if (recv_data !== expected_data) begin
                $display("ERROR: received 0x%h, expected 0x%h (LSB first)", recv_data, expected_data);
                error_count = error_count + 1;
            end else begin
                $display("OK: received 0x%h (LSB first %b)", recv_data, recv_data);
            end
        end
    endtask

    initial begin
        $dumpfile("tb_uart_tx.vcd");
        $dumpvars(0, tb_uart_tx);

        clk = 0;
        rst = 1;
        start = 0;
        data = 0;
        error_count = 0;

        #10 rst = 0;
        @(posedge clk);

        if (tx !== 1) begin
            $display("ERROR: tx should be 1 (idle) after reset");
            error_count = error_count + 1;
        end

        if (busy !== 0) begin
            $display("ERROR: busy should be 0 after reset");
            error_count = error_count + 1;
        end

        $display("--- Testing 0x41 (A) ---");
        data = 8'h41;
        start = 1;
        @(posedge clk);
        start = 0;
        verify_frame(8'h41);

        @(posedge clk);
        @(posedge clk);

        $display("--- Testing 0x35 (5) ---");
        data = 8'h35;
        start = 1;
        @(posedge clk);
        start = 0;
        verify_frame(8'h35);

        @(posedge clk);
        @(posedge clk);

        $display("--- Testing start ignored while busy ---");
        data = 8'hA5;
        start = 1;
        @(posedge clk);
        start = 0;
        @(posedge clk);
        data = 8'hFF;
        start = 1;
        @(posedge clk);
        start = 0;
        if (busy !== 1) begin
            $display("ERROR: should still be busy after second start");
            error_count = error_count + 1;
        end
        verify_frame(8'hA5);

        @(posedge clk);
        @(posedge clk);

        if (error_count == 0) begin
            $display("PASS: tb_uart_tx passed all checks");
        end else begin
            $display("FAIL: tb_uart_tx had %0d errors", error_count);
        end

        $finish;
    end

endmodule
