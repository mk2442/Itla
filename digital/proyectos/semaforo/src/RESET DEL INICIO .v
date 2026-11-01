// BORRA ESTO — ya existe en "RESET DEL INICIO .v"
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