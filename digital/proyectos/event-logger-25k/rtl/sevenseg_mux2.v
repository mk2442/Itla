`timescale 1ns / 1ps

module sevenseg_mux2 #(
    parameter SEG_ACTIVE_LOW = 1'b1
)(
    input  wire       clk,
    input  wire       rst,
    input  wire       scan_tick,
    input  wire [6:0] seg_units,
    input  wire [6:0] seg_tens,
    input  wire       blank_units,
    input  wire       blank_tens,
    output wire [6:0] seg,
    output wire       sel,
    output wire       sel2
);

    localparam BLANK = SEG_ACTIVE_LOW ? 7'b1111111 : 7'b0000000;

    reg        sel_reg;
    reg [6:0]  muxed_seg;

    always @(posedge clk) begin
        if (rst) begin
            sel_reg <= 0;
        end else if (scan_tick) begin
            sel_reg <= ~sel_reg;
        end
    end

    always @(*) begin
        case (sel_reg)
            1'b0: begin
                if (blank_units) begin
                    muxed_seg = BLANK;
                end else begin
                    muxed_seg = seg_units;
                end
            end
            1'b1: begin
                if (blank_tens) begin
                    muxed_seg = BLANK;
                end else begin
                    muxed_seg = seg_tens;
                end
            end
            default: muxed_seg = BLANK;
        endcase
    end

    assign seg = muxed_seg;
    assign sel = SEG_ACTIVE_LOW ? ~sel_reg : sel_reg;
    assign sel2 = SEG_ACTIVE_LOW ? sel_reg : ~sel_reg;

endmodule
