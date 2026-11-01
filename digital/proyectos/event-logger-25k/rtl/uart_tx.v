`timescale 1ns / 1ps

module uart_tx #(
    parameter CLKS_PER_BIT = 100,
    parameter COUNTER_WIDTH = 16
)(
    input  wire       clk,
    input  wire       rst,
    input  wire       start,
    input  wire [7:0] data,
    output reg        tx,
    output reg        busy,
    output reg        done
);

    localparam IDLE       = 2'b00;
    localparam START_BIT  = 2'b01;
    localparam DATA_BITS  = 2'b10;
    localparam STOP_BIT   = 2'b11;

    reg [1:0] state;
    reg [1:0] next_state;

    reg [7:0] data_reg;
    reg [2:0] bit_index;
    reg [COUNTER_WIDTH-1:0] clk_count;

    wire tick;

    assign tick = (clk_count == CLKS_PER_BIT - 1);

    always @(posedge clk) begin
        if (rst) begin
            state <= IDLE;
            clk_count <= 0;
        end else begin
            state <= next_state;
            if (state != IDLE) begin
                if (tick) begin
                    clk_count <= 0;
                end else begin
                    clk_count <= clk_count + 1;
                end
            end else begin
                clk_count <= 0;
            end
        end
    end

    always @(*) begin
        next_state = state;
        case (state)
            IDLE: begin
                if (start) begin
                    next_state = START_BIT;
                end
            end
            START_BIT: begin
                if (tick) begin
                    next_state = DATA_BITS;
                end
            end
            DATA_BITS: begin
                if (tick && (bit_index == 3'd7)) begin
                    next_state = STOP_BIT;
                end
            end
            STOP_BIT: begin
                if (tick) begin
                    next_state = IDLE;
                end
            end
            default: next_state = IDLE;
        endcase
    end

    always @(posedge clk) begin
        if (rst) begin
            data_reg  <= 0;
            bit_index <= 0;
            tx        <= 1;
            busy      <= 0;
            done      <= 0;
        end else begin
            done <= 0;
            case (state)
                IDLE: begin
                    tx   <= 1;
                    busy <= 0;
                    if (start) begin
                        data_reg <= data;
                        bit_index <= 0;
                        tx   <= 0;
                        busy <= 1;
                    end
                end
                START_BIT: begin
                    tx   <= 0;
                    busy <= 1;
                    if (tick) begin
                        bit_index <= 0;
                    end
                end
                DATA_BITS: begin
                    tx   <= data_reg[bit_index];
                    busy <= 1;
                    if (tick) begin
                        if (bit_index == 3'd7) begin
                            bit_index <= 0;
                        end else begin
                            bit_index <= bit_index + 1;
                        end
                    end
                end
                STOP_BIT: begin
                    tx   <= 1;
                    busy <= 1;
                    if (tick) begin
                        busy <= 0;
                        done <= 1;
                    end
                end
                default: begin
                    tx   <= 1;
                    busy <= 0;
                end
            endcase
        end
    end

endmodule
