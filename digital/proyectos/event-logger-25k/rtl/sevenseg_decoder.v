`timescale 1ns / 1ps

module sevenseg_decoder #(
    parameter SEG_ACTIVE_LOW = 1'b1
)(
    input  wire [3:0] hex_in,
    input  wire       blank,
    output wire [6:0] seg
);

    reg [6:0] seg_reg;

    always @(*) begin
        if (blank) begin
            seg_reg = 7'b1111111;
        end else begin
            case (hex_in)
                4'h0: seg_reg = 7'b0000001;
                4'h1: seg_reg = 7'b1001111;
                4'h2: seg_reg = 7'b0010010;
                4'h3: seg_reg = 7'b0000110;
                4'h4: seg_reg = 7'b1001100;
                4'h5: seg_reg = 7'b0100100;
                4'h6: seg_reg = 7'b0100000;
                4'h7: seg_reg = 7'b0001111;
                4'h8: seg_reg = 7'b0000000;
                4'h9: seg_reg = 7'b0000100;
                4'hA: seg_reg = 7'b0001000;
                4'hB: seg_reg = 7'b1100000;
                4'hC: seg_reg = 7'b0110001;
                4'hD: seg_reg = 7'b1000010;
                4'hE: seg_reg = 7'b0110000;
                4'hF: seg_reg = 7'b0111000;
                default: seg_reg = 7'b1111111;
            endcase
        end
    end

    assign seg = SEG_ACTIVE_LOW ? seg_reg : ~seg_reg;

endmodule
