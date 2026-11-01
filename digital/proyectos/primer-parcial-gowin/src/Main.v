`timescale 1ns / 1ps

module mini_panel (
    input wire clk,           // Reloj interno del FPGA
    input wire rst_n,         // Botón de reset (logica negativa)
    input wire enable,        // Interruptor para habilitar el contador
    input wire [1:0] mode,    // 2 interruptores para el modo de operación
    input wire [3:0] a,       // 4 interruptores para el número A
    input wire [3:0] b,       // 4 interruptores para el número B
    output reg [3:0] result,  // 4 LEDs para el resultado
    output wire led_status   
);

    // Registro interno para el contador (Memoria)
    reg [3:0] counter;

    // LÓGICA SECUENCIAL Contador interno
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            counter <= 4'b0000; // Reset asíncrono
        end else if (enable && mode == 2'b10) begin
            counter <= counter + 1; // Incremento del contador
        end
        // Si enable es 0, el contador mantiene su valor automáticamente
    end

    // LÓGICA COMBINACIONAL Multiplexor de salidas
    always @(*) begin
        // Valor por defecto para evitar "latches" (Regla de oro en combinacional)
        result = 4'b0000;

        case (mode)
            2'b00: result = a + b;            // Modo 00: Suma
            2'b01: result = a ^ b;            // Modo 01: XOR (Compuerta lógica)
            2'b10: result = counter;          // Modo 10: Contador interno
            2'b11: result = {a[1:0], b[1:0]}; // Modo 11: Concatenación
            default: result = 4'b0000;        // Caso por defecto
        endcase
    end

    // El led se enciende (1) si el resultado es 15 (4'hF o 4'b1111)
    assign led_status = (result == 4'hF) ? 1'b1 : 1'b0;

endmodule

// Módulo de Simulación: tb_mini_panel (NO se sube al FPGA, solo para probar)
// synthesis translate_off
module tb_mini_panel;

    // Entradas al simulador (regs)
    reg clk;
    reg rst_n;
    reg enable;
    reg [1:0] mode;
    reg [3:0] a;
    reg [3:0] b;

    // Salidas del simulador (wires)
    wire [3:0] result;
    wire led_status;

    // Instanciar el módulo principal
    mini_panel uut (
        .clk(clk), 
        .rst_n(rst_n), 
        .enable(enable), 
        .mode(mode), 
        .a(a), 
        .b(b), 
        .result(result), 
        .led_status(led_status)
    );

    // Generación del reloj de simulación 
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // Periodo de 10 unidades
    end

    // Proceso de pruebas
    initial begin
        // Monitor para ver los resultados en la consola
        $monitor("Tiempo=%0d | rst_n=%b en=%b mode=%b a=%d b=%d | result=%d led=%b", 
                 $time, rst_n, enable, mode, a, b, result, led_status);

        // Estado inicial
        rst_n = 0;
        enable = 0;
        mode = 2'b00;
        a = 4'd0;
        b = 4'd0;

        // Prueba 1: Reset
        #10; rst_n = 0; 
        #10; rst_n = 1; // Liberar reset
        
        // Prueba 2: Suma (mode 00) -> 7 + 8 = 15 (led_status debe encender)
        mode = 2'b00; enable = 1; a = 4'd7; b = 4'd8;
        #10;
        
        // Prueba 3: XOR (mode 01) -> 1010 ^ 0101 = 1111 (led_status debe encender)
        mode = 2'b01; a = 4'b1010; b = 4'b0101;
        #10;
        
        // Prueba 4: Concatenación (mode 11) -> a[1:0]=01, b[1:0]=11 -> 0111
        mode = 2'b11; a = 4'b1101; b = 4'b0011;
        #10;

        // Prueba 5: Contador inicio (mode 10)
        mode = 2'b10; enable = 1; a = 4'dx; b = 4'dx; 
        #30; // Dejar contar unos ciclos
        
        // Prueba 6: Contador detenido
        enable = 0;
        #20; // Verificar que mantiene el valor
        
        // Prueba 7: Dejar contar hasta que desborde y encienda el LED
        enable = 1;
        #150; 

        // Fin de la simulación
        #10 $finish;
    end

endmodule