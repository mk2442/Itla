module and_module(
    input  A1, B1, output Y1,
    input  A2, B2, output Y2,
    input  A3, B3, output Y3,
    input  A4, B4, output Y4
);
    and (Y1, A1, B1);
    and (Y2, A2, B2);
    and (Y3, A3, B3);
    and (Y4, A4, B4);
endmodule