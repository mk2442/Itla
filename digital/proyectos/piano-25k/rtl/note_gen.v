`timescale 1ns / 1ps

module note_gen #(
    parameter CLK_FREQ = 27000000
)(
    input  wire       clk,
    input  wire       rst,
    input  wire [6:0] note_enable,
    input  wire [1:0] octave_sel,
    output reg        audio_out
);

    localparam [16:0] C4 = 17'd51586;
    localparam [16:0] D4 = 17'd45969;
    localparam [16:0] E4 = 17'd40957;
    localparam [16:0] F4 = 17'd38639;
    localparam [16:0] G4 = 17'd34439;
    localparam [16:0] A4 = 17'd30682;
    localparam [16:0] B4 = 17'd27334;

    reg [16:0] base_period;

    always @(*) begin
        case (1'b1)
            note_enable[0]: base_period = C4;
            note_enable[1]: base_period = D4;
            note_enable[2]: base_period = E4;
            note_enable[3]: base_period = F4;
            note_enable[4]: base_period = G4;
            note_enable[5]: base_period = A4;
            note_enable[6]: base_period = B4;
            default:         base_period = 17'd0;
        endcase
    end

    reg [16:0] half_period;

    always @(*) begin
        if (base_period == 0) begin
            half_period = 17'd0;
        end else begin
            case (octave_sel)
                2'b00:   half_period = base_period << 1;
                2'b01:   half_period = base_period;
                2'b10:   half_period = base_period >> 1;
                default: half_period = base_period >> 1;
            endcase
        end
    end

    reg [16:0] counter;
    reg [16:0] half_period_prev;

    wire note_changed;
    assign note_changed = (half_period != half_period_prev);

    always @(posedge clk) begin
        half_period_prev <= half_period;
    end

    always @(posedge clk) begin
        if (rst || half_period == 0) begin
            counter   <= 0;
            audio_out <= 0;
        end else if (note_changed) begin
            counter   <= 0;
            audio_out <= 0;
        end else if (counter >= half_period - 1) begin
            counter   <= 0;
            audio_out <= ~audio_out;
        end else begin
            counter <= counter + 1;
        end
    end

endmodule
