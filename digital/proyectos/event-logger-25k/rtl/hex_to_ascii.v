`timescale 1ns / 1ps

module hex_to_ascii (
    input  wire [3:0] hex_in,
    output wire [7:0] ascii_out
);

    reg [7:0] ascii_reg;

    always @(*) begin
        case (hex_in)
            4'h0: ascii_reg = 8'h30;
            4'h1: ascii_reg = 8'h31;
            4'h2: ascii_reg = 8'h32;
            4'h3: ascii_reg = 8'h33;
            4'h4: ascii_reg = 8'h34;
            4'h5: ascii_reg = 8'h35;
            4'h6: ascii_reg = 8'h36;
            4'h7: ascii_reg = 8'h37;
            4'h8: ascii_reg = 8'h38;
            4'h9: ascii_reg = 8'h39;
            4'hA: ascii_reg = 8'h41;
            4'hB: ascii_reg = 8'h42;
            4'hC: ascii_reg = 8'h43;
            4'hD: ascii_reg = 8'h44;
            4'hE: ascii_reg = 8'h45;
            4'hF: ascii_reg = 8'h46;
            default: ascii_reg = 8'h30;
        endcase
    end

    assign ascii_out = ascii_reg;

endmodule
