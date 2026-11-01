`timescale 1ns / 1ps

// ============================================================
// clk_pll.v - PLL clock generator for Gowin FPGA
// ============================================================
// Uses Gowin_rPLL primitive to generate a clean, low-jitter
// clock from the 27 MHz onboard oscillator.
//
// Default configuration: 27 MHz -> 27 MHz (bypass)
// To change output frequency, modify CLKOUT_DIV and CLKFB_SEL.
//
// For Tang Primer 25K (GW5A-25):
//   - Input: 27 MHz (E2 pin)
//   - VCO range: 400 MHz - 1200 MHz
//   - CLKOUT_DIV must be set so VCO stays in range
//
// Example configurations:
//   27 MHz -> 27 MHz:  CLKOUT_DIV=1,  CLKFB_SEL=CLKOUT
//   27 MHz -> 50 MHz:  Use external divider (PLL limited)
//   27 MHz -> 100 MHz: CLKOUT_DIV=4 (108 MHz VCO)
//   27 MHz -> 13.5 MHz: Use clk_div module instead
//
// NOTE: For precise frequency generation, use clk_div.v
//       This PLL is for applications needing low-jitter clock.
// ============================================================

module clk_pll (
    input  wire clk_in,     // 27 MHz input
    input  wire rst_n,      // Active low reset
    output wire clk_out,    // PLL output clock
    output wire lock        // PLL locked indicator
);

    // --------------------------------------------------------
    // Gowin rPLL instantiation
    // --------------------------------------------------------
    // Parameters for 27 MHz -> 27 MHz (bypass)
    // Adjust these for different output frequencies
    // --------------------------------------------------------
    rPLL #(
        .FCLKIN("27"),           // Input frequency in MHz
        .DEVICE("GW5A-25"),      // Target device
        .DYN_IDIV_SEL("false"),  // Static IDIV
        .IDIV_SEL(0),            // IDIV = 1 (0 means divide by 1)
        .DYN_FBDIV_SEL("false"), // Static FBDIV
        .FBDIV_SEL(0),           // FBDIV = 1 (0 means multiply by 1)
        .DYN_ODIV_SEL("false"),  // Static ODIV
        .ODIV_SEL(8),            // ODIV = 8 (VCO / 8 = output)
        .PSDA_SEL("0000"),       // Phase shift
        .DYN_DA_EN("true"),      // Dynamic duty cycle
        .DUTYDA_SEL("1000"),     // Duty cycle
        .CLKOUT_FT_DIR(1'b1),   // Edge type
        .CLKOUTP_FT_DIR(1'b1),  // Edge type
        .CLKOUT_DLY_STEP(0),    // Delay step
        .CLKOUTP_DLY_STEP(0),   // Delay step
        .CLKFB_SEL("internal"), // Internal feedback
        .CLKOUT_BYPASS("true"), // Bypass PLL (passthrough)
        .CLKOUTP_BYPASS("true"),// Bypass CLKOUTP
        .CLKOUTD_BYPASS("true"),// Bypass CLKOUTD
        .DYN_SDIV_SEL(2),       // Secondary divider
        .CLKOUTD_SRC("CLKOUT"), // Source for CLKOUTD
        .CLKOUTD3_SRC("CLKOUT") // Source for CLKOUTD3
    ) pll_inst (
        .CLKOUT(clk_out),       // Output clock
        .LOCK(lock),            // Lock signal
        .CLKOUTP(),             // Phase-shifted output (unused)
        .CLKOUTD(),             // Divided output (unused)
        .CLKOUTD3(),            // Divided output 3 (unused)
        .RESET(rst_n),          // Active high reset
        .RESET_P(rst_n),        // Active high preset
        .CLKIN(clk_in),         // Input clock
        .CLKFB(1'b0),           // External feedback
        .FBDSEL(4'b0000),       // Dynamic FBDIV select
        .IDSEL(4'b0000),        // Dynamic IDIV select
        .ODSEL(4'b0000),        // Dynamic ODIV select
        .PSDA(4'b0000),         // Dynamic phase shift
        .DUTYDA(4'b0000),       // Dynamic duty cycle
        .FDLY(4'b0000)          // Dynamic delay
    );

endmodule
