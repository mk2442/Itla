`timescale 1ns / 1ps

module ram32x4 (
    input  wire       clk,
    input  wire       we,
    input  wire [4:0] addr,
    input  wire [3:0] din,
    output wire [3:0] dout
);

    reg [3:0] mem [0:31];
    reg [4:0] addr_reg;

    always @(posedge clk) begin
        if (we) begin
            mem[addr] <= din;
        end
        addr_reg <= addr;
    end

    assign dout = mem[addr_reg];

endmodule
