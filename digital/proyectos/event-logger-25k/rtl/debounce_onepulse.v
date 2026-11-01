`timescale 1ns / 1ps

module debounce_onepulse #(
    parameter STABLE_CYCLES = 10,
    parameter COUNTER_WIDTH = 4
)(
    input  wire clk,
    input  wire rst,
    input  wire noisy_in,
    output wire level,
    output wire pulse
);

    reg [COUNTER_WIDTH-1:0] counter;
    reg                     level_reg;
    reg                     prev_level;

    wire                    stable;

    assign stable = (counter == STABLE_CYCLES - 1);

    always @(posedge clk) begin
        if (rst) begin
            counter    <= 0;
            level_reg  <= 0;
            prev_level <= 0;
        end else begin
            prev_level <= level_reg;

            if (level_reg != noisy_in) begin
                if (stable) begin
                    counter    <= 0;
                    level_reg  <= ~level_reg;
                end else begin
                    counter <= counter + 1;
                end
            end else begin
                counter <= 0;
            end
        end
    end

    assign level = level_reg;
    assign pulse = (level_reg != prev_level) && level_reg;

endmodule
