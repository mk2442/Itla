`timescale 1ns / 1ps

module write_pointer (
    input  wire       clk,
    input  wire       rst,
    input  wire       increment,
    input  wire       clear,
    output wire [4:0] write_addr,
    output wire       full
);

    reg [5:0] count;

    always @(posedge clk) begin
        if (rst) begin
            count <= 0;
        end else if (clear) begin
            count <= 0;
        end else if (increment && (count < 32)) begin
            count <= count + 1;
        end
    end

    assign write_addr = count[4:0];
    assign full = (count == 32);

endmodule
