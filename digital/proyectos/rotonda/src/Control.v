module control_rotonda(
    input  P0, P1, P2, P3,
    output S0, S1, S2, S3
);
    wire nP0, nP1, nP2, nP3;
 
    // Inversores
    not_module inv(
        .A1(P0), .Y1(nP0),
        .A2(P1), .Y2(nP1),
        .A3(P2), .Y3(nP2),
        .A4(P3), .Y4(nP3)
    );
 
    // ----------------------------------------------------------
    // S0 = P0 | ~P1
    // ----------------------------------------------------------
    or_module s0_or(
        .A1(P0),   .B1(nP1),  .Y1(S0),
        .A2(1'b0), .B2(1'b0), .Y2(),
        .A3(1'b0), .B3(1'b0), .Y3(),
        .A4(1'b0), .B4(1'b0), .Y4()
    );
 
    // ----------------------------------------------------------
    // S1 = (~P1 & ~P2) | (~P0 & P1)
    // ----------------------------------------------------------
    wire s1_t1, s1_t2;
    and_module s1_and(
        .A1(nP1),  .B1(nP2),  .Y1(s1_t1),   // ~P1 & ~P2
        .A2(nP0),  .B2(P1),   .Y2(s1_t2),   // ~P0 &  P1
        .A3(1'b0), .B3(1'b0), .Y3(),
        .A4(1'b0), .B4(1'b0), .Y4()
    );
    or_module s1_or(
        .A1(s1_t1), .B1(s1_t2), .Y1(S1),
        .A2(1'b0),  .B2(1'b0),  .Y2(),
        .A3(1'b0),  .B3(1'b0),  .Y3(),
        .A4(1'b0),  .B4(1'b0),  .Y4()
    );
 
    // ----------------------------------------------------------
    // S2 = (~P3 & (~P1 | ~P2)) | (P2 & (~P1 | P0))
    //
    //   Término A: ~P3 & (~P1 | ~P2)
    //     or_nP1_nP2  = ~P1 | ~P2
    //     s2_tA       = ~P3 & or_nP1_nP2
    //
    //   Término B: P2 & (~P1 | P0)
    //     or_nP1_P0   = ~P1 | P0
    //     s2_tB       = P2  & or_nP1_P0
    // ----------------------------------------------------------
    wire or_nP1_nP2, s2_tA, or_nP1_P0, s2_tB;
 
    or_module s2_or_inner(
        .A1(nP1),  .B1(nP2), .Y1(or_nP1_nP2),  // ~P1 | ~P2
        .A2(nP1),  .B2(P0),  .Y2(or_nP1_P0),   // ~P1 | P0
        .A3(1'b0), .B3(1'b0),.Y3(),
        .A4(1'b0), .B4(1'b0),.Y4()
    );
    and_module s2_and(
        .A1(nP3),  .B1(or_nP1_nP2), .Y1(s2_tA),  // ~P3 & (~P1|~P2)
        .A2(P2),   .B2(or_nP1_P0),  .Y2(s2_tB),  //  P2 & (~P1|P0)
        .A3(1'b0), .B3(1'b0),        .Y3(),
        .A4(1'b0), .B4(1'b0),        .Y4()
    );
    or_module s2_or_final(
        .A1(s2_tA), .B1(s2_tB), .Y1(S2),
        .A2(1'b0),  .B2(1'b0),  .Y2(),
        .A3(1'b0),  .B3(1'b0),  .Y3(),
        .A4(1'b0),  .B4(1'b0),  .Y4()
    );
 
    // ----------------------------------------------------------
    // S3 = (~P0 | (P3 & ~P2)) & (P1 | ~P2 | ~P3)
    //
    //   Factor X: ~P0 | (P3 & ~P2)
    //     s3_P3nP2    = P3 & ~P2
    //     s3_factorX  = ~P0 | s3_P3nP2
    //
    //   Factor Y: P1 | ~P2 | ~P3
    //     s3_nP2_nP3  = ~P2 | ~P3
    //     s3_factorY  = P1  | s3_nP2_nP3
    //
    //   S3 = factorX & factorY
    // ----------------------------------------------------------
    wire s3_P3nP2, s3_factorX, s3_nP2_nP3, s3_factorY;
 
    and_module s3_and(
        .A1(P3),   .B1(nP2),  .Y1(s3_P3nP2),   // P3 & ~P2
        .A2(1'b0), .B2(1'b0), .Y2(),
        .A3(1'b0), .B3(1'b0), .Y3(),
        .A4(1'b0), .B4(1'b0), .Y4()
    );
    or_module s3_or_factors(
        .A1(nP0),      .B1(s3_P3nP2), .Y1(s3_factorX),  // ~P0 | (P3&~P2)
        .A2(nP2),      .B2(nP3),      .Y2(s3_nP2_nP3),  // ~P2 | ~P3
        .A3(P1),       .B3(s3_nP2_nP3),.Y3(s3_factorY), // P1 | ~P2 | ~P3
        .A4(1'b0),     .B4(1'b0),     .Y4()
    );
    and_module s3_and_final(
        .A1(s3_factorX), .B1(s3_factorY), .Y1(S3),       // X & Y
        .A2(1'b0),       .B2(1'b0),       .Y2(),
        .A3(1'b0),       .B3(1'b0),       .Y3(),
        .A4(1'b0),       .B4(1'b0),       .Y4()
    );
 
endmodule