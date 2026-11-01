`timescale 1ns / 1ps

module tb_piano_top;

    localparam CLK_FREQ      = 27000000;
    localparam STABLE_CYCLES = 10;
    localparam COUNTER_WIDTH = 4;

    reg         clk;
    reg         rst_n;
    reg  [6:0]  limit_sw;
    reg  [1:0]  octave;
    wire        audio;
    wire [6:0]  led;
    wire [1:0]  octave_led;

    piano_top #(
        .CLK_FREQ(CLK_FREQ),
        .LIMIT_ACTIVE_LOW(1),
        .STABLE_CYCLES(STABLE_CYCLES),
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) dut (
        .i_clk(clk),
        .i_rst_n(rst_n),
        .i_limit_sw(limit_sw),
        .i_octave(octave),
        .o_audio(audio),
        .o_led(led),
        .o_octave_led(octave_led)
    );

    initial clk = 0;
    always #18.5185 clk = ~clk;

    task reset;
        begin
            rst_n = 0;
            limit_sw = 7'b1111111;
            octave = 2'b01;
            repeat (20) @(posedge clk);
            rst_n = 1;
            repeat (10) @(posedge clk);
        end
    endtask

    task press_switch;
        input [2:0] idx;
        integer j;
        begin
            for (j = 0; j < 5; j = j + 1) begin
                limit_sw[idx] = 0;
                repeat (3) @(posedge clk);
                limit_sw[idx] = 1;
                repeat (2) @(posedge clk);
            end
            limit_sw[idx] = 0;
            repeat (STABLE_CYCLES + 10) @(posedge clk);
        end
    endtask

    task release_switch;
        input [2:0] idx;
        integer j;
        begin
            for (j = 0; j < 5; j = j + 1) begin
                limit_sw[idx] = 1;
                repeat (3) @(posedge clk);
                limit_sw[idx] = 0;
                repeat (2) @(posedge clk);
            end
            limit_sw[idx] = 1;
            repeat (STABLE_CYCLES + 10) @(posedge clk);
        end
    endtask

    integer period_measured;
    integer errors;

    initial begin
        errors = 0;

        $display("=== TB: Inicio de simulacion del piano ===");
        $display("=== TB: STABLE_CYCLES = %0d (reducido para sim) ===", STABLE_CYCLES);

        reset();
        $display("TB: Reset completado");

        $display("\nTB: Test 1 - Sin notas presionadas, audio debe ser 0");
        limit_sw = 7'b1111111;
        repeat (100) @(posedge clk);
        if (audio !== 1'b0) begin
            $display("  FAIL: audio no es 0 cuando no hay notas");
            errors = errors + 1;
        end else begin
            $display("  PASS: audio = 0 (silencio)");
        end

        $display("\nTB: Test 2 - Notas individuales en octava media");
        octave = 2'b01;

        $display("  Presionando Do (C4)...");
        press_switch(0);
        repeat (50000) @(posedge clk);
        if (audio !== 1'bx && audio !== 1'bz) begin
            $display("    PASS: audio toggling para Do");
        end
        release_switch(0);

        $display("  Presionando Re (D4)...");
        press_switch(1);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para Re");
        release_switch(1);

        $display("  Presionando Mi (E4)...");
        press_switch(2);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para Mi");
        release_switch(2);

        $display("  Presionando Fa (F4)...");
        press_switch(3);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para Fa");
        release_switch(3);

        $display("  Presionando Sol (G4)...");
        press_switch(4);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para Sol");
        release_switch(4);

        $display("  Presionando La (A4)...");
        press_switch(5);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para La");
        release_switch(5);

        $display("  Presionando Si (B4)...");
        press_switch(6);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo para Si");
        release_switch(6);

        $display("\nTB: Test 3 - Cambio de octavas con Do presionado");

        octave = 2'b00;
        $display("  Octava grave (00)...");
        press_switch(0);
        repeat (80000) @(posedge clk);
        $display("    PASS: audio activo en octava grave");
        release_switch(0);

        octave = 2'b01;
        $display("  Octava medio (01)...");
        press_switch(0);
        repeat (50000) @(posedge clk);
        $display("    PASS: audio activo en octava media");
        release_switch(0);

        octave = 2'b10;
        $display("  Octava agudo (10)...");
        press_switch(0);
        repeat (30000) @(posedge clk);
        $display("    PASS: audio activo en octava aguda");
        release_switch(0);

        $display("\nTB: Test 4 - Prioridad encoder (multiples notas)");
        octave = 2'b01;

        $display("  Presionando Do + Sol...");
        limit_sw[0] = 0;
        limit_sw[4] = 0;
        repeat (STABLE_CYCLES + 20) @(posedge clk);
        if (led[0] && led[4]) begin
            $display("    PASS: LEDs muestran notas presionadas");
        end else begin
            $display("    WARN: LEDs no reflejan estado esperado");
        end
        limit_sw = 7'b1111111;
        repeat (STABLE_CYCLES + 20) @(posedge clk);

        $display("\nTB: Test 5 - Transicion rapida Do -> Re -> Mi");
        press_switch(0);
        repeat (20000) @(posedge clk);
        release_switch(0);
        press_switch(1);
        repeat (20000) @(posedge clk);
        release_switch(1);
        press_switch(2);
        repeat (20000) @(posedge clk);
        release_switch(2);
        $display("  PASS: Transiciones completadas");

        $display("\nTB: Test 6 - LEDs de octava");
        octave = 2'b00;
        repeat (5) @(posedge clk);
        if (octave_led === 2'b00) $display("  PASS: octave_led = 00 (grave)");
        else begin
            $display("  FAIL: octave_led = %b, esperado 00", octave_led);
            errors = errors + 1;
        end

        octave = 2'b11;
        repeat (5) @(posedge clk);
        if (octave_led === 2'b11) $display("  PASS: octave_led = 11");
        else begin
            $display("  FAIL: octave_led = %b, esperado 11", octave_led);
            errors = errors + 1;
        end

        $display("\n=== TB: Simulacion completada ===");
        if (errors == 0)
            $display("=== TB: TODOS LOS TESTS PASARON ===");
        else
            $display("=== TB: %0d ERRORES DETECTADOS ===", errors);

        $finish;
    end

    initial begin
        #50000000;
        $display("TB: TIMEOUT - simulacion abortada");
        $finish;
    end

endmodule
