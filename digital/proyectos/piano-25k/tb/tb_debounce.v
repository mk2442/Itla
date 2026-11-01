`timescale 1ns / 1ps

module tb_debounce;

    parameter STABLE_CYCLES = 20;
    parameter COUNTER_WIDTH = 5;

    reg  clk;
    reg  rst;
    reg  noisy_in;
    wire level;

    debounce #(
        .STABLE_CYCLES(STABLE_CYCLES),
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) dut (
        .clk(clk),
        .rst(rst),
        .noisy_in(noisy_in),
        .level(level)
    );

    initial clk = 0;
    always #18.5185 clk = ~clk;

    integer errors;
    integer i;

    initial begin
        errors = 0;
        rst = 1;
        noisy_in = 0;

        $display("\n=== TB_DEBOUNCE: Test 1 - Reset ===");
        repeat (5) @(posedge clk);
        rst = 0;
        repeat (5) @(posedge clk);

        if (level !== 1'b0) begin
            $display("  FAIL: level deberia ser 0 despues de reset, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: level = 0 despues de reset");
        end

        $display("\n=== TB_DEBOUNCE: Test 2 - Rebotes rapidos ===");
        for (i = 0; i < 8; i = i + 1) begin
            noisy_in = 1; repeat (2) @(posedge clk);
            noisy_in = 0; repeat (2) @(posedge clk);
        end
        repeat (5) @(posedge clk);
        if (level !== 1'b0) begin
            $display("  FAIL: level cambio con rebotes, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: rebotes ignorados correctamente");
        end

        $display("\n=== TB_DEBOUNCE: Test 3 - Señal estable 0->1 ===");
        noisy_in = 1;
        repeat (STABLE_CYCLES + 5) @(posedge clk);
        if (level !== 1'b1) begin
            $display("  FAIL: level deberia ser 1, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: level = 1 despues de %0d ciclos estables", STABLE_CYCLES);
        end

        $display("\n=== TB_DEBOUNCE: Test 4 - Señal estable 1->0 ===");
        noisy_in = 0;
        repeat (STABLE_CYCLES + 5) @(posedge clk);
        if (level !== 1'b0) begin
            $display("  FAIL: level deberia ser 0, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: level = 0 despues de soltar");
        end

        $display("\n=== TB_DEBOUNCE: Test 5 - Rebote interrumpido ===");
        noisy_in = 1;
        repeat (STABLE_CYCLES / 2) @(posedge clk);
        noisy_in = 0;
        repeat (3) @(posedge clk);
        noisy_in = 1;
        repeat (5) @(posedge clk);
        if (level !== 1'b0) begin
            $display("  FAIL: level cambio prematuramente, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: rebote interrumpido no cambio el nivel");
        end

        noisy_in = 1;
        repeat (STABLE_CYCLES + 5) @(posedge clk);
        if (level !== 1'b1) begin
            $display("  FAIL: level no se estabilizo en 1, es %b", level);
            errors = errors + 1;
        end else begin
            $display("  PASS: nivel establecido en 1");
        end

        $display("\n=== TB_DEBOUNCE: Completado ===");
        if (errors == 0)
            $display("=== TODOS LOS TESTS PASARON ===");
        else
            $display("=== %0d ERRORES ===", errors);

        $finish;
    end

    initial begin
        #1000000;
        $display("TIMEOUT");
        $finish;
    end

endmodule
