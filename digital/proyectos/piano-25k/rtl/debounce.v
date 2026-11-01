`timescale 1ns / 1ps

module debounce #(
    parameter STABLE_CYCLES = 500000,
    parameter COUNTER_WIDTH = 20
)(
    input  wire clk,
    input  wire rst,
    input  wire noisy_in,
    output reg  level
);

    reg [COUNTER_WIDTH-1:0] counter;

    always @(posedge clk) begin
        if (rst) begin
            counter <= 0;
            level   <= 0;
        end else begin
            if (noisy_in != level) begin
                if (counter == STABLE_CYCLES - 1) begin
                    level   <= noisy_in;
                    counter <= 0;
                end else begin
                    counter <= counter + 1;
                end
            end else begin
                counter <= 0;
            end
        end
    end

endmodule
