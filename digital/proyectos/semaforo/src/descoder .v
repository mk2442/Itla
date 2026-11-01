module decodificador_displays (
    input  wire [2:0] estado_fsm,
    input  wire [7:0] contador_via_A,
    input  wire [7:0] contador_via_B,
    input  wire flag_modo_mant,
    input  wire pulso_parpadeo,
    output reg  [6:0] seg7_A_unidad,
    output reg  [6:0] seg7_A_decena,
    output reg  [6:0] seg7_A_centena,
    output reg  [6:0] seg7_B_unidad,
    output reg  [6:0] seg7_B_decena,
    output reg  [6:0] seg7_B_centena
);
    localparam [6:0] DIGITO_0 = 7'b0111111; localparam [6:0] DIGITO_1 = 7'b0000110;
    localparam [6:0] DIGITO_2 = 7'b1011011; localparam [6:0] DIGITO_3 = 7'b1001111;
    localparam [6:0] DIGITO_4 = 7'b1100110; localparam [6:0] DIGITO_5 = 7'b1101101;
    localparam [6:0] DIGITO_6 = 7'b1111101; localparam [6:0] DIGITO_7 = 7'b0000111;
    localparam [6:0] DIGITO_8 = 7'b1111111; localparam [6:0] DIGITO_9 = 7'b1101111;
    localparam [6:0] PATRON_GUION   = 7'b1000000;
    localparam [6:0] PATRON_APAGADO = 7'b0000000;

    wire [3:0] centena_A = contador_via_A / 100;
    wire [3:0] decena_A  = (contador_via_A % 100) / 10;
    wire [3:0] unidad_A  = contador_via_A % 10;
    wire [3:0] centena_B = contador_via_B / 100;
    wire [3:0] decena_B  = (contador_via_B % 100) / 10;
    wire [3:0] unidad_B  = contador_via_B % 10;

    reg [6:0] patron_centena_A, patron_decena_A, patron_unidad_A;
    reg [6:0] patron_centena_B, patron_decena_B, patron_unidad_B;

    function [6:0] obtener_patron;
        input [3:0] digito;
        begin
            case (digito)
                4'd0: obtener_patron = DIGITO_0; 4'd1: obtener_patron = DIGITO_1;
                4'd2: obtener_patron = DIGITO_2; 4'd3: obtener_patron = DIGITO_3;
                4'd4: obtener_patron = DIGITO_4; 4'd5: obtener_patron = DIGITO_5;
                4'd6: obtener_patron = DIGITO_6; 4'd7: obtener_patron = DIGITO_7;
                4'd8: obtener_patron = DIGITO_8; 4'd9: obtener_patron = DIGITO_9;
                default: obtener_patron = PATRON_APAGADO;
            endcase
        end
    endfunction

    always @(*) begin
        patron_centena_A = obtener_patron(centena_A);
        patron_decena_A  = obtener_patron(decena_A);
        patron_unidad_A  = obtener_patron(unidad_A);
        patron_centena_B = obtener_patron(centena_B);
        patron_decena_B  = obtener_patron(decena_B);
        patron_unidad_B  = obtener_patron(unidad_B);

        if (flag_modo_mant) begin
            if (pulso_parpadeo) begin
                seg7_A_unidad  = PATRON_GUION; seg7_A_decena  = PATRON_GUION; seg7_A_centena = PATRON_GUION;
                seg7_B_unidad  = PATRON_GUION; seg7_B_decena  = PATRON_GUION; seg7_B_centena = PATRON_GUION;
            end else begin
                seg7_A_unidad  = PATRON_APAGADO; seg7_A_decena  = PATRON_APAGADO; seg7_A_centena = PATRON_APAGADO;
                seg7_B_unidad  = PATRON_APAGADO; seg7_B_decena  = PATRON_APAGADO; seg7_B_centena = PATRON_APAGADO;
            end
        end else begin
            seg7_A_unidad  = patron_unidad_A;
            seg7_A_decena  = (contador_via_A < 8'd10)  ? PATRON_APAGADO : patron_decena_A;
            seg7_A_centena = (contador_via_A < 8'd100) ? PATRON_APAGADO : patron_centena_A;
            seg7_B_unidad  = patron_unidad_B;
            seg7_B_decena  = (contador_via_B < 8'd10)  ? PATRON_APAGADO : patron_decena_B;
            seg7_B_centena = (contador_via_B < 8'd100) ? PATRON_APAGADO : patron_centena_B;
        end
    end
endmodule

