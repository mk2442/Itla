`timescale 1ns / 1ps

module event_code_comb (
    input  wire [3:0] switches,
    input  wire       capture_request,
    output wire [3:0] event_code,
    output wire       event_valid,
    output wire [7:0] led_onehot
);

    assign event_code = switches;

    assign event_valid = capture_request;

    assign led_onehot[0] = ~(switches[2:0] == 3'd0);
    assign led_onehot[1] = ~(switches[2:0] == 3'd1);
    assign led_onehot[2] = ~(switches[2:0] == 3'd2);
    assign led_onehot[3] = ~(switches[2:0] == 3'd3);
    assign led_onehot[4] = ~(switches[2:0] == 3'd4);
    assign led_onehot[5] = ~(switches[2:0] == 3'd5);
    assign led_onehot[6] = ~(switches[2:0] == 3'd6);
    assign led_onehot[7] = ~(switches[2:0] == 3'd7);

endmodule
