`timescale 1ns / 1ps

module tick_enable #(
    parameter PERIOD = 100,
    parameter COUNTER_WIDTH = 8
)(
    input  wire clk,
    input  wire rst,
    output wire tick
);

    reg [COUNTER_WIDTH-1:0] counter;

    always @(posedge clk) begin
        if (rst) begin
            counter <= 0;
        end else if (counter == PERIOD - 1) begin
            counter <= 0;
        end else begin
            counter <= counter + 1;
        end
    end

    assign tick = (counter == PERIOD - 1);

endmodule
