`timescale 1ns / 1ps

module cdc_pulse_toggle (
    input  wire src_clk,
    input  wire src_rst,
    input  wire src_pulse,
    input  wire dst_clk,
    input  wire dst_rst,
    output wire dst_pulse
);

    reg toggle_src;
    reg toggle_meta;
    reg toggle_dst;
    reg toggle_dst_delay;

    always @(posedge src_clk) begin
        if (src_rst) begin
            toggle_src <= 0;
        end else if (src_pulse) begin
            toggle_src <= ~toggle_src;
        end
    end

    always @(posedge dst_clk) begin
        if (dst_rst) begin
            toggle_meta <= 0;
            toggle_dst  <= 0;
        end else begin
            toggle_meta <= toggle_src;
            toggle_dst  <= toggle_meta;
        end
    end

    always @(posedge dst_clk) begin
        if (dst_rst) begin
            toggle_dst_delay <= 0;
        end else begin
            toggle_dst_delay <= toggle_dst;
        end
    end

    assign dst_pulse = toggle_dst ^ toggle_dst_delay;

endmodule
