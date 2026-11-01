module semaforo_uk_top (
    input  wire clk_principal,
    input  wire sw_mantenimiento,
    output wire [5:0] salidas_leds,
    output wire [6:0] seg7_A_unidad,
    output wire [6:0] seg7_A_decena,
    output wire [6:0] seg7_A_centena,
    output wire [6:0] seg7_B_unidad,
    output wire [6:0] seg7_B_decena,
    output wire [6:0] seg7_B_centena
);
    parameter invertir_leds    = 0;
    parameter frec_clk_fpga    = 25_000_000;

    localparam DURACION_LUZ_ROJA   = 8'd130; // ← CAMBIADO
    localparam DURACION_SEG_MIN    = 8'd1;
    localparam DURACION_LUZ_VERDE  = 8'd55;
    localparam DURACION_LUZ_AMBAR  = 8'd25;
    localparam DURACION_TRANSICION = 8'd10;

    wire rst_sistema;
    wire tick_1hz;
    wire [5:0] bus_luces;
    wire [7:0] contador_via_A;
    wire [7:0] contador_via_B;
    wire [2:0] estado_fsm;
    wire flag_modo_mant;
    wire pulso_parpadeo;

    generador_reset inicio_sistema (
        .clk_principal(clk_principal),
        .rst_sistema(rst_sistema)
    );

    generador_1hz #(.FREC_ENTRADA(frec_clk_fpga)) divisor_frecuencia (
        .clk_principal(clk_principal),
        .rst_sistema(rst_sistema),
        .tick_1hz(tick_1hz)
    );

    maquina_estados_trafico #(
        .TIEMPO_ROJO_LARGO(DURACION_LUZ_ROJA),
        .TIEMPO_SEGURIDAD(DURACION_SEG_MIN),
        .TIEMPO_VERDE(DURACION_LUZ_VERDE),
        .TIEMPO_AMBAR(DURACION_LUZ_AMBAR),
        .TIEMPO_PREPARACION(DURACION_TRANSICION)
    ) controlador_fsm (
        .clk_principal(clk_principal),
        .rst_sistema(rst_sistema),
        .tick_1hz(tick_1hz),
        .sw_mantenimiento(sw_mantenimiento),
        .bus_luces(bus_luces),
        .contador_via_A(contador_via_A),
        .contador_via_B(contador_via_B),
        .estado_fsm(estado_fsm),
        .flag_modo_mant(flag_modo_mant),
        .pulso_parpadeo(pulso_parpadeo)
    );

    decodificador_displays unidad_displays (
        .estado_fsm(estado_fsm),
        .contador_via_A(contador_via_A),
        .contador_via_B(contador_via_B),
        .flag_modo_mant(flag_modo_mant),
        .pulso_parpadeo(pulso_parpadeo),
        .seg7_A_unidad(seg7_A_unidad),
        .seg7_A_decena(seg7_A_decena),
        .seg7_A_centena(seg7_A_centena),
        .seg7_B_unidad(seg7_B_unidad),
        .seg7_B_decena(seg7_B_decena),
        .seg7_B_centena(seg7_B_centena)
    );

    assign salidas_leds = (invertir_leds) ? ~bus_luces : bus_luces;
endmodule


// ============================================================

module generador_reset (
    input  wire clk_principal,
    output reg  rst_sistema
);
    reg [5:0] cnt_rst = 6'd0;
    localparam CICLOS_RESET = 6'd50;

    always @(posedge clk_principal) begin
        if (cnt_rst < CICLOS_RESET) begin
            cnt_rst     <= cnt_rst + 1'b1;
            rst_sistema <= 1'b0;
        end else begin
            rst_sistema <= 1'b1;
        end
    end
endmodule