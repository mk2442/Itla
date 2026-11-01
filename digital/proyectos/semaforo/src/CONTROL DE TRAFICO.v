module maquina_estados_trafico #(
    parameter TIEMPO_ROJO_LARGO  = 8'd130,
    parameter TIEMPO_SEGURIDAD   = 8'd1,
    parameter TIEMPO_VERDE       = 8'd20,  // ← CAMBIADO
    parameter TIEMPO_AMBAR       = 8'd25,
    parameter TIEMPO_PREPARACION = 8'd10 //si
) (
    input  wire clk_principal,
    input  wire rst_sistema,
    input  wire tick_1hz,
    input  wire sw_mantenimiento,
    output reg  [5:0] bus_luces,
    output reg  [7:0] contador_via_A,
    output reg  [7:0] contador_via_B,
    output reg  [2:0] estado_fsm,
    output reg  flag_modo_mant,
    output reg  pulso_parpadeo
);
    localparam ST_VIA_A_VERDE    = 3'd0;
    localparam ST_VIA_A_AMBAR    = 3'd1;
    localparam ST_SEGURIDAD_1    = 3'd2;
    localparam ST_VIA_B_TRANS    = 3'd3;
    localparam ST_VIA_B_VERDE    = 3'd4;
    localparam ST_VIA_B_AMBAR    = 3'd5;
    localparam ST_SEGURIDAD_2    = 3'd6;
    localparam ST_VIA_A_TRANS    = 3'd7;

    reg [7:0] reg_tiempo_A;
    reg [7:0] reg_tiempo_B;
    reg flanco_anterior;
    reg bandera_mant_prev;

    always @(posedge clk_principal or negedge rst_sistema) begin
        if (!rst_sistema) begin
            estado_fsm        <= ST_SEGURIDAD_1;
            reg_tiempo_A      <= TIEMPO_SEGURIDAD;
            reg_tiempo_B      <= TIEMPO_SEGURIDAD;
            pulso_parpadeo    <= 1'b0;
            flag_modo_mant    <= 1'b0;
            bandera_mant_prev <= 1'b0;
            flanco_anterior   <= 1'b0;
        end else begin
            bandera_mant_prev <= flag_modo_mant;
            flag_modo_mant    <= sw_mantenimiento;

            if (bandera_mant_prev && !flag_modo_mant) begin
                estado_fsm   <= ST_SEGURIDAD_1;
                reg_tiempo_A <= TIEMPO_SEGURIDAD;
                reg_tiempo_B <= TIEMPO_SEGURIDAD;
            end

            if (!flag_modo_mant) begin
                if (tick_1hz && !flanco_anterior)
                    pulso_parpadeo <= ~pulso_parpadeo;
                flanco_anterior <= tick_1hz;

                if (tick_1hz) begin
                    if (reg_tiempo_A > 8'd0) reg_tiempo_A <= reg_tiempo_A - 1'b1;
                    if (reg_tiempo_B > 8'd0) reg_tiempo_B <= reg_tiempo_B - 1'b1;

                    case (estado_fsm)
                        ST_VIA_A_VERDE: begin
                            if (reg_tiempo_A == 8'd0) begin
                                estado_fsm   <= ST_VIA_A_AMBAR;
                                reg_tiempo_A <= TIEMPO_AMBAR;
                            end
                        end
                        ST_VIA_A_AMBAR: begin
                            if (reg_tiempo_A == 8'd0) begin
                                estado_fsm   <= ST_SEGURIDAD_1;
                                reg_tiempo_A <= TIEMPO_SEGURIDAD;
                                reg_tiempo_B <= TIEMPO_SEGURIDAD;
                            end
                        end
                        ST_SEGURIDAD_1: begin
                            if (reg_tiempo_A == 8'd0 && reg_tiempo_B == 8'd0) begin
                                estado_fsm   <= ST_VIA_B_TRANS;
                                reg_tiempo_A <= TIEMPO_ROJO_LARGO;
                                reg_tiempo_B <= TIEMPO_PREPARACION;
                            end
                        end
                        ST_VIA_B_TRANS: begin
                            if (reg_tiempo_B == 8'd0) begin
                                estado_fsm   <= ST_VIA_B_VERDE;
                                reg_tiempo_B <= TIEMPO_VERDE;
                            end
                        end
                        ST_VIA_B_VERDE: begin
                            if (reg_tiempo_B == 8'd0) begin
                                estado_fsm   <= ST_VIA_B_AMBAR;
                                reg_tiempo_B <= TIEMPO_AMBAR;
                            end
                        end
                        ST_VIA_B_AMBAR: begin
                            if (reg_tiempo_B == 8'd0) begin
                                estado_fsm   <= ST_SEGURIDAD_2;
                                reg_tiempo_A <= TIEMPO_SEGURIDAD;
                                reg_tiempo_B <= TIEMPO_SEGURIDAD;
                            end
                        end
                        ST_SEGURIDAD_2: begin
                            if (reg_tiempo_A == 8'd0 && reg_tiempo_B == 8'd0) begin
                                estado_fsm   <= ST_VIA_A_TRANS;
                                reg_tiempo_A <= TIEMPO_PREPARACION;
                                reg_tiempo_B <= TIEMPO_ROJO_LARGO;
                            end
                        end
                        ST_VIA_A_TRANS: begin
                            if (reg_tiempo_A == 8'd0) begin
                                estado_fsm   <= ST_VIA_A_VERDE;
                                reg_tiempo_A <= TIEMPO_VERDE;
                            end
                        end
                        default: begin
                            estado_fsm   <= ST_SEGURIDAD_1;
                            reg_tiempo_A <= TIEMPO_SEGURIDAD;
                            reg_tiempo_B <= TIEMPO_SEGURIDAD;
                        end
                    endcase
                end
            end
        end
    end

    always @(*) begin
        contador_via_A = reg_tiempo_A;
        contador_via_B = reg_tiempo_B;
    end

    always @(*) begin
        if (flag_modo_mant) begin
            bus_luces = {1'b0, pulso_parpadeo, 1'b0, 1'b0, pulso_parpadeo, 1'b0};
        end else begin
            case (estado_fsm)
                ST_VIA_A_VERDE:  bus_luces = 6'b001_100;
                ST_VIA_A_AMBAR:  bus_luces = 6'b010_100;
                ST_SEGURIDAD_1:  bus_luces = 6'b100_100;
                ST_VIA_B_TRANS:  bus_luces = 6'b100_110;
                ST_VIA_B_VERDE:  bus_luces = 6'b100_001;
                ST_VIA_B_AMBAR:  bus_luces = 6'b100_010;
                ST_SEGURIDAD_2:  bus_luces = 6'b100_100;
                ST_VIA_A_TRANS:  bus_luces = 6'b110_100;
                default:         bus_luces = 6'b100_100;
            endcase
        end
    end
endmodule