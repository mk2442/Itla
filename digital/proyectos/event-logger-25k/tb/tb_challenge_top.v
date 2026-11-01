`timescale 1ns / 1ps

module tb_challenge_top;

    reg clk;
    reg rst_n;
    reg [3:0] button;
    reg [3:0] switches;
    wire [7:0] led;
    wire [6:0] seg;
    wire sel;
    wire sel2;
    wire uart_tx;

    challenge_top #(
        .CLKS_PER_BIT(8),
        .STABLE_CYCLES(4),
        .COUNTER_WIDTH(4),
        .SCAN_PERIOD(4),
        .SEG_ACTIVE_LOW(1'b1),
        .BTN_ACTIVE_LOW(1'b1),
        .LED_ACTIVE_LOW(1'b0)
    ) uut (
        .i_clk(clk),
        .i_rst_n(rst_n),
        .i_button(button),
        .i_switch(switches),
        .o_led(led),
        .o_seg(seg),
        .o_sel(sel),
        .o_sel2(sel2),
        .o_uart_tx(uart_tx)
    );

    always #5 clk = ~clk;

    integer error_count;

    task press_button(input integer b);
        button[b] = 0;
        repeat (10) @(posedge clk);
        button[b] = 1;
        repeat (10) @(posedge clk);
    endtask

    task wait_stable;
        repeat (20) @(posedge clk);
    endtask

    initial begin
        $dumpfile("tb_challenge_top.vcd");
        $dumpvars(0, tb_challenge_top);

        clk = 0;
        rst_n = 0;
        button = 4'b1111;
        switches = 4'h0;
        error_count = 0;

        #10 rst_n = 1;

        wait_stable;

        $display("--- Test 1: Arm the system ---");
        press_button(0);
        if (led[4] !== 1) begin
            $display("ERROR: led[4] (armed) should be 1 after arm");
            error_count = error_count + 1;
        end else begin
            $display("OK: System armed");
        end

        $display("--- Test 2: Capture event A at addr 0 ---");
        switches = 4'hA;
        press_button(1);

        $display("--- Test 3: Capture event 5 at addr 1 ---");
        switches = 4'h5;
        press_button(1);

        $display("--- Test 4: Transmit last event (0x35 via ASCII) ---");
        press_button(2);
        repeat (100) @(posedge clk);

        $display("--- Test 5: Clear ---");
        press_button(3);
        if (led[4] !== 0 && led[1:0] !== 2'b00) begin
            $display("ERROR: should be in IDLE after clear");
            error_count = error_count + 1;
        end else begin
            $display("OK: System cleared");
        end

        $display("--- Test 6: Fill memory to test full flag ---");
        begin : fill_test
            integer k;
            press_button(0);
            for (k = 0; k < 35; k = k + 1) begin
                switches = k[3:0];
                press_button(1);
                if (k < 32 && led[2] !== 0) begin
                    $display("ERROR: mem_full before 32 writes at k=%0d", k);
                    error_count = error_count + 1;
                end
                if (k >= 32 && led[2] !== 1) begin
                    $display("ERROR: mem_full should be 1 at k=%0d", k);
                    error_count = error_count + 1;
                end
            end
        end

        if (led[2] !== 1) begin
            $display("ERROR: mem_full expected after 32 writes");
            error_count = error_count + 1;
        end else begin
            $display("OK: mem_full asserted after 32 writes");
        end

        $display("--- Test 7: Capture ignored when full ---");
        switches = 4'hF;
        press_button(1);
        if (led[2] !== 1) begin
            $display("ERROR: still full after extra capture attempt");
            error_count = error_count + 1;
        end

        $display("--- Test 8: Clear and re-arm ---");
        press_button(3);
        if (led[2] !== 0) begin
            $display("ERROR: mem_full should clear");
            error_count = error_count + 1;
        end
        press_button(0);
        if (led[4] !== 1) begin
            $display("ERROR: should be armed again");
            error_count = error_count + 1;
        end

        if (error_count == 0) begin
            $display("PASS: tb_challenge_top passed all checks");
        end else begin
            $display("FAIL: tb_challenge_top had %0d errors", error_count);
        end

        $finish;
    end

endmodule
