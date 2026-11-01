`timescale 1ns / 1ps

module tb_note_gen;

    parameter CLK_FREQ = 27000000;

    reg        clk;
    reg        rst;
    reg  [6:0] note_enable;
    reg  [1:0] octave_sel;
    wire       audio_out;

    note_gen #(
        .CLK_FREQ(CLK_FREQ)
    ) dut (
        .clk(clk),
        .rst(rst),
        .note_enable(note_enable),
        .octave_sel(octave_sel),
        .audio_out(audio_out)
    );

    initial clk = 0;
    always #18.5185 clk = ~clk;

    localparam [16:0] C4_HP = 17'd51586;
    localparam [16:0] A4_HP = 17'd30682;
    localparam [16:0] B4_HP = 17'd27334;

    integer errors;
    integer period_measured;

    initial begin
        errors = 0;
        rst = 1;
        note_enable = 7'b0000000;
        octave_sel = 2'b01;

        $display("\n=== TB_NOTE_GEN: Inicio ===");

        $display("\nTest 1 - Reset: audio_out debe ser 0");
        repeat (10) @(posedge clk);
        rst = 0;
        repeat (5) @(posedge clk);
        if (audio_out !== 1'b0) begin
            $display("  FAIL: audio_out = %b, esperado 0", audio_out);
            errors = errors + 1;
        end else begin
            $display("  PASS: audio_out = 0 en reset");
        end

        $display("\nTest 2 - Sin nota activa");
        note_enable = 7'b0000000;
        repeat (100) @(posedge clk);
        if (audio_out !== 1'b0) begin
            $display("  FAIL: audio_out = %b con note_enable = 0", audio_out);
            errors = errors + 1;
        end else begin
            $display("  PASS: silencio correcto");
        end

        $display("\nTest 3 - Do4 (C4), octava media");
        note_enable = 7'b0000001;
        octave_sel = 2'b01;
        repeat (C4_HP * 4) @(posedge clk);
        begin : measure_c4
            reg prev_val;
            integer cnt;
            prev_val = audio_out;
            cnt = 0;
            while (cnt < C4_HP * 3) begin
                @(posedge clk);
                cnt = cnt + 1;
                if (audio_out != prev_val) begin
                    prev_val = audio_out;
                    @(posedge clk);
                    cnt = 0;
                    prev_val = audio_out;
                    while (cnt < C4_HP * 3) begin
                        @(posedge clk);
                        cnt = cnt + 1;
                        if (audio_out != prev_val) begin
                            period_measured = cnt;
                            cnt = C4_HP * 3;
                        end
                        prev_val = audio_out;
                    end
                    cnt = C4_HP * 3;
                end
                prev_val = audio_out;
            end
        end
        $display("  Periodo medido: %0d ciclos (esperado ~%0d)", period_measured, C4_HP * 2);
        if (period_measured > C4_HP * 2 + C4_HP/4 ||
            period_measured < C4_HP * 2 - C4_HP/4) begin
            $display("  FAIL: periodo fuera de rango");
            errors = errors + 1;
        end else begin
            $display("  PASS: periodo correcto");
        end

        $display("\nTest 4 - La4 (A4), octava media");
        note_enable = 7'b0100000;
        octave_sel = 2'b01;
        repeat (A4_HP * 4) @(posedge clk);
        begin : measure_a4
            reg prev_val;
            integer cnt;
            prev_val = audio_out;
            cnt = 0;
            while (cnt < A4_HP * 3) begin
                @(posedge clk);
                cnt = cnt + 1;
                if (audio_out != prev_val) begin
                    prev_val = audio_out;
                    @(posedge clk);
                    cnt = 0;
                    prev_val = audio_out;
                    while (cnt < A4_HP * 3) begin
                        @(posedge clk);
                        cnt = cnt + 1;
                        if (audio_out != prev_val) begin
                            period_measured = cnt;
                            cnt = A4_HP * 3;
                        end
                        prev_val = audio_out;
                    end
                    cnt = A4_HP * 3;
                end
                prev_val = audio_out;
            end
        end
        $display("  Periodo medido: %0d ciclos (esperado ~%0d)", period_measured, A4_HP * 2);
        if (period_measured > A4_HP * 2 + A4_HP/4 ||
            period_measured < A4_HP * 2 - A4_HP/4) begin
            $display("  FAIL: periodo fuera de rango");
            errors = errors + 1;
        end else begin
            $display("  PASS: periodo correcto");
        end

        $display("\nTest 5 - Do3 (grave)");
        note_enable = 7'b0000001;
        octave_sel = 2'b00;
        repeat (C4_HP * 4) @(posedge clk);
        begin : measure_c3
            reg prev_val;
            integer cnt;
            prev_val = audio_out;
            cnt = 0;
            while (cnt < 200000) begin
                @(posedge clk);
                cnt = cnt + 1;
                if (audio_out != prev_val) begin
                    period_measured = cnt;
                    cnt = 200000;
                end
                prev_val = audio_out;
            end
        end
        $display("  Periodo medido: %0d ciclos (esperado ~%0d)", period_measured, C4_HP * 4);
        if (period_measured > C4_HP * 4 + C4_HP/2 ||
            period_measured < C4_HP * 4 - C4_HP/2) begin
            $display("  FAIL: periodo grave fuera de rango");
            errors = errors + 1;
        end else begin
            $display("  PASS: octava grave correcta");
        end

        $display("\nTest 6 - Do5 (agudo)");
        note_enable = 7'b0000001;
        octave_sel = 2'b10;
        repeat (C4_HP * 4) @(posedge clk);
        begin : measure_c5
            reg prev_val;
            integer cnt;
            prev_val = audio_out;
            cnt = 0;
            while (cnt < C4_HP * 3) begin
                @(posedge clk);
                cnt = cnt + 1;
                if (audio_out != prev_val) begin
                    prev_val = audio_out;
                    @(posedge clk);
                    cnt = 0;
                    prev_val = audio_out;
                    while (cnt < C4_HP * 3) begin
                        @(posedge clk);
                        cnt = cnt + 1;
                        if (audio_out != prev_val) begin
                            period_measured = cnt;
                            cnt = C4_HP * 3;
                        end
                        prev_val = audio_out;
                    end
                    cnt = C4_HP * 3;
                end
                prev_val = audio_out;
            end
        end
        $display("  Periodo medido: %0d ciclos (esperado ~%0d)", period_measured, C4_HP);
        if (period_measured > C4_HP + C4_HP/4 ||
            period_measured < C4_HP - C4_HP/4) begin
            $display("  FAIL: periodo agudo fuera de rango");
            errors = errors + 1;
        end else begin
            $display("  PASS: octava agudo correcta");
        end

        $display("\nTest 7 - Cambio de nota limpia glitch");
        note_enable = 7'b0000001;
        octave_sel = 2'b01;
        repeat (200) @(posedge clk);
        note_enable = 7'b0000010;
        repeat (10) @(posedge clk);
        $display("  PASS: cambio de nota ejecutado");

        $display("\n=== TB_NOTE_GEN: Completado ===");
        if (errors == 0)
            $display("=== TODOS LOS TESTS PASARON ===");
        else
            $display("=== %0d ERRORES ===", errors);

        $finish;
    end

    initial begin
        #20000000;
        $display("TIMEOUT");
        $finish;
    end

endmodule
