module generador_1hz #(
    parameter FREC_ENTRADA = 25_000_000
) (
    input  wire clk_principal,
    input  wire rst_sistema,
    output reg  tick_1hz
);
    reg [31:0] registro_cuenta;
    localparam [31:0] TOPE_CUENTA = FREC_ENTRADA - 1;

    always @(posedge clk_principal or negedge rst_sistema) begin
        if (!rst_sistema) begin
            registro_cuenta <= 32'd0;
            tick_1hz        <= 1'b0;
        end else begin
            if (registro_cuenta >= TOPE_CUENTA) begin
                registro_cuenta <= 32'd0;
                tick_1hz        <= 1'b1;
            end else begin
                registro_cuenta <= registro_cuenta + 1'b1;
                tick_1hz        <= 1'b0;
            end
        end
    end
endmodule