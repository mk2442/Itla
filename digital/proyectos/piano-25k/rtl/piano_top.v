`timescale 1ns / 1ps

module piano_top #(
    parameter CLK_FREQ        = 27000000,
    parameter LIMIT_ACTIVE_LOW = 1,
    parameter STABLE_CYCLES   = 500000,
    parameter COUNTER_WIDTH   = 20
)(
    input  wire       i_clk,
    input  wire       i_rst_n,
    input  wire [6:0] i_limit_sw,
    input  wire [1:0] i_octave,
    output wire       o_audio,
    output wire [6:0] o_led,
    output wire [1:0] o_octave_led
);

    wire rst;
    assign rst = ~i_rst_n;

    wire [6:0] sw_clean;

    genvar i;
    generate
        for (i = 0; i < 7; i = i + 1) begin : deb_gen
            wire sw_raw;
            assign sw_raw = LIMIT_ACTIVE_LOW ? ~i_limit_sw[i] : i_limit_sw[i];

            debounce #(
                .STABLE_CYCLES(STABLE_CYCLES),
                .COUNTER_WIDTH(COUNTER_WIDTH)
            ) deb_inst (
                .clk(i_clk),
                .rst(rst),
                .noisy_in(sw_raw),
                .level(sw_clean[i])
            );
        end
    endgenerate

    reg [6:0] note_active;

    always @(*) begin
        if (sw_clean[6])      note_active = 7'b1000000;
        else if (sw_clean[5]) note_active = 7'b0100000;
        else if (sw_clean[4]) note_active = 7'b0010000;
        else if (sw_clean[3]) note_active = 7'b0001000;
        else if (sw_clean[2]) note_active = 7'b0000100;
        else if (sw_clean[1]) note_active = 7'b0000010;
        else if (sw_clean[0]) note_active = 7'b0000001;
        else                  note_active = 7'b0000000;
    end

    wire audio_raw;

    note_gen #(
        .CLK_FREQ(CLK_FREQ)
    ) note_inst (
        .clk(i_clk),
        .rst(rst),
        .note_enable(note_active),
        .octave_sel(i_octave),
        .audio_out(audio_raw)
    );

    assign o_audio = (note_active == 7'b0) ? 1'b0 : audio_raw;

    assign o_led        = sw_clean;
    assign o_octave_led = i_octave;

endmodule
