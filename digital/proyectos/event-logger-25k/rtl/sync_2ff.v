`timescale 1ns / 1ps

module sync_2ff #(
    parameter WIDTH = 1
)(
    input  wire               clk,
    input  wire               rst,
    input  wire [WIDTH-1:0]   async_in,
    output wire [WIDTH-1:0]   sync_out
);

    reg [WIDTH-1:0] meta;
    reg [WIDTH-1:0] sync;

    always @(posedge clk) begin
        if (rst) begin
            meta <= {WIDTH{1'b0}};
            sync <= {WIDTH{1'b0}};
        end else begin
            meta <= async_in;
            sync <= meta;
        end
    end

    assign sync_out = sync;

endmodule
