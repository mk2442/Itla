module main(
    input  sw_P0,
    input  sw_P1,
    input  sw_P2,
    input  sw_P3,
    output led_S0,
    output led_S1,
    output led_S2,
    output led_S3
);
    wire P0, P1, P2, P3;
 
    or_module pass(
        .A1(sw_P0), .B1(1'b0), .Y1(P0),
        .A2(sw_P1), .B2(1'b0), .Y2(P1),
        .A3(sw_P2), .B3(1'b0), .Y3(P2),
        .A4(sw_P3), .B4(1'b0), .Y4(P3)
    );
 
    control_rotonda control(
        .P0(P0), .P1(P1), .P2(P2), .P3(P3),
        .S0(led_S0), .S1(led_S1), .S2(led_S2), .S3(led_S3)
    );
endmodule