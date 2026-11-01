`timescale 1ns / 1ps

// ============================================================
// clk_div.v - Clock divider with reset synchronizer
// ============================================================
// Divides the input clock by a configurable factor.
// Includes a reset synchronizer to avoid metastability.
//
// Usage:
//   - Default: divides 27 MHz by 2 -> 13.5 MHz output
//   - Change DIV_RATIO parameter for other frequencies
//
// For 27 MHz input:
//   DIV_RATIO=1  -> 27 MHz (bypass)
//   DIV_RATIO=2  -> 13.5 MHz
//   DIV_RATIO=3  -> 9 MHz
//   DIV_RATIO=4  -> 6.75 MHz
//   DIV_RATIO=5  -> 5.4 MHz
//   DIV_RATIO=10 -> 2.7 MHz
//   DIV_RATIO=27 -> 1 MHz
// ============================================================

module clk_div #(
    parameter DIV_RATIO = 2
)(
    input  wire clk_in,
    input  wire rst_n,
    output wire clk_out,
    output wire rst_out
);

    // --------------------------------------------------------
    // Reset synchronizer (2 FF)
    // --------------------------------------------------------
    reg rst_sync1;
    reg rst_sync2;

    always @(posedge clk_in or negedge rst_n) begin
        if (!rst_n) begin
            rst_sync1 <= 1'b1;
            rst_sync2 <= 1'b1;
        end else begin
            rst_sync1 <= 1'b0;
            rst_sync2 <= rst_sync1;
        end
    end

    assign rst_out = rst_sync2;

    // --------------------------------------------------------
    // Clock divider
    // --------------------------------------------------------
    localparam CNT_WIDTH = $clog2(DIV_RATIO);

    reg [CNT_WIDTH-1:0] counter;
    reg                 clk_divided;

    always @(posedge clk_in or negedge rst_n) begin
        if (!rst_n) begin
            counter     <= 0;
            clk_divided <= 0;
        end else begin
            if (counter == DIV_RATIO/2 - 1) begin
                counter     <= 0;
                clk_divided <= ~clk_divided;
            end else begin
                counter <= counter + 1;
            end
        end
    end

    // --------------------------------------------------------
    // Output assignment
    // --------------------------------------------------------
    // Bypass divider when DIV_RATIO = 1
    generate
        if (DIV_RATIO == 1) begin : gen_bypass
            assign clk_out = clk_in;
        end else begin : gen_divide
            assign clk_out = clk_divided;
        end
    endgenerate

endmodule
