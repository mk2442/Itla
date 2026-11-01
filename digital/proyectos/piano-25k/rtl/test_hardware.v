`timescale 1ns / 1ps

module test_hardware (
    input  wire       i_clk,
    input  wire       i_rst_n,
    input  wire       i_sw0,
    output wire [7:0] o_led,
    output wire       o_buzzer
);

    wire rst;
    assign rst = ~i_rst_n;

    reg [24:0] blink_cnt;
    reg        blink;

    always @(posedge i_clk) begin
        if (rst) begin
            blink_cnt <= 0;
            blink     <= 0;
        end else if (blink_cnt == 27_000_000 - 1) begin
            blink_cnt <= 0;
            blink     <= ~blink;
        end else begin
            blink_cnt <= blink_cnt + 1;
        end
    end

    assign o_led = {8{blink}};

    reg [15:0] buz_cnt;
    reg        buz_out;

    always @(posedge i_clk) begin
        if (rst) begin
            buz_cnt <= 0;
            buz_out <= 0;
        end else if (buz_cnt >= 30681) begin
            buz_cnt <= 0;
            buz_out <= ~buz_out;
        end else begin
            buz_cnt <= buz_cnt + 1;
        end
    end

    assign o_buzzer = buz_out;

endmodule
