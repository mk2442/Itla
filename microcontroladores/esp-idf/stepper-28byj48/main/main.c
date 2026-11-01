#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/uart.h"
#include "stepper.h"

#define UART_PORT UART_NUM_0
#define BUF_SIZE 256

#define PIN_IN1 2
#define PIN_IN2 3
#define PIN_IN3 4
#define PIN_IN4 5

static stepper_t motor;
static char cmd_buf[BUF_SIZE];
static int cmd_pos = 0;

static void send(const char *s) {
    uart_write_bytes(UART_PORT, s, strlen(s));
}

static void print_help(void) {
    send("\r\n"
         "===========================================\r\n"
         "  STEPPER 28BYJ-48 - ESP-IDF - ESP32 Mini\r\n"
         "===========================================\r\n"
         "\r\n"
         "  M <pasos> <1/-1>    Mover pasos\r\n"
         "  D <grados> <1/-1>   Mover grados\r\n"
         "  R <vueltas> <1/-1>  Mover vueltas\r\n"
         "  SPD <us>            Velocidad (500-10000)\r\n"
         "  SPD?                Ver velocidad\r\n"
         "  MODE HALF           Half-step (4096/rev)\r\n"
         "  MODE FULL           Full-step (2048/rev)\r\n"
         "  MODE?               Ver modo\r\n"
         "  POS                 Posicion actual\r\n"
         "  HOME                Ir a home\r\n"
         "  RELEASE             Desenergizar motor\r\n"
         "  HELP                Esta ayuda\r\n"
         "===========================================\r\n\r\n");
}

static void process(char *raw) {
    while (*raw == ' ') raw++;
    if (!*raw) return;

    char cmd[64];
    strncpy(cmd, raw, 63);
    cmd[63] = '\0';
    for (int i = 0; cmd[i]; i++)
        if (cmd[i] >= 'a' && cmd[i] <= 'z') cmd[i] -= 32;

    char resp[128];

    if (!strcmp(cmd, "HELP") || !strcmp(cmd, "?")) {
        print_help();
    }
    else if (!strcmp(cmd, "STOP") || !strcmp(cmd, "RELEASE")) {
        stepper_release(&motor);
        send("[OK] Motor desenergizado.\r\n");
    }
    else if (!strcmp(cmd, "POS")) {
        sprintf(resp, "[POS] %ld pasos | %.2f grados\r\n", motor.current_step, motor.current_deg);
        send(resp);
    }
    else if (!strcmp(cmd, "HOME")) {
        stepper_home(&motor);
        send("[OK] En home.\r\n");
    }
    else if (!strcmp(cmd, "MODE?")) {
        send(motor.mode == 0 ? "[MODE] HALF-STEP\r\n" : "[MODE] FULL-STEP\r\n");
    }
    else if (!strcmp(cmd, "SPD?")) {
        sprintf(resp, "[SPD] %lu us\r\n", motor.step_delay_us);
        send(resp);
    }
    else if (!strncmp(cmd, "MODE ", 5)) {
        char *m = cmd + 5;
        while (*m == ' ') m++;
        if (!strcmp(m, "HALF")) {
            stepper_set_mode(&motor, 0);
            send("[OK] HALF-STEP (4096 pasos/rev)\r\n");
        } else if (!strcmp(m, "FULL")) {
            stepper_set_mode(&motor, 1);
            send("[OK] FULL-STEP (2048 pasos/rev)\r\n");
        } else {
            send("[ERR] Usa: HALF o FULL\r\n");
        }
    }
    else if (!strncmp(cmd, "SPD ", 4)) {
        long spd = atol(cmd + 4);
        if (spd >= 500 && spd <= 10000) {
            stepper_set_speed(&motor, spd);
            sprintf(resp, "[OK] %ld us\r\n", spd);
            send(resp);
        } else {
            send("[ERR] Rango: 500-10000\r\n");
        }
    }
    else if (cmd[0] == 'M' && cmd[1] == ' ') {
        long steps; int dir;
        if (sscanf(cmd + 2, "%ld %d", &steps, &dir) == 2 && steps > 0 && (dir == 1 || dir == -1)) {
            stepper_move_steps(&motor, steps, dir);
            sprintf(resp, "[OK] %ld pasos | %.2f grados\r\n", motor.current_step, motor.current_deg);
            send(resp);
        } else {
            send("[ERR] M <pasos> <1/-1>\r\n");
        }
    }
    else if (cmd[0] == 'D' && cmd[1] == ' ') {
        float deg; int dir;
        if (sscanf(cmd + 2, "%f %d", &deg, &dir) == 2 && deg > 0 && (dir == 1 || dir == -1)) {
            stepper_move_degrees(&motor, deg, dir);
            sprintf(resp, "[OK] %.2f grados | %ld pasos\r\n", motor.current_deg, motor.current_step);
            send(resp);
        } else {
            send("[ERR] D <grados> <1/-1>\r\n");
        }
    }
    else if (cmd[0] == 'R' && cmd[1] == ' ') {
        float rot; int dir;
        if (sscanf(cmd + 2, "%f %d", &rot, &dir) == 2 && rot > 0 && (dir == 1 || dir == -1)) {
            stepper_move_rotations(&motor, rot, dir);
            sprintf(resp, "[OK] %.2f vueltas | %.2f grados\r\n", rot, motor.current_deg);
            send(resp);
        } else {
            send("[ERR] R <vueltas> <1/-1>\r\n");
        }
    }
    else {
        send("[?] HELP\r\n");
    }
}

void app_main(void) {
    uart_config_t cfg = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(UART_PORT, &cfg);
    uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0);

    stepper_init(&motor, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);

    send("\r\n> ");
    uint8_t byte;
    while (1) {
        if (uart_read_bytes(UART_PORT, &byte, 1, portMAX_DELAY) == 1) {
            if (byte == '\r' || byte == '\n') {
                if (cmd_pos > 0) {
                    send("\r\n");
                    cmd_buf[cmd_pos] = '\0';
                    process(cmd_buf);
                    cmd_pos = 0;
                }
                send("> ");
            } else if (byte == '\b' || byte == 127) {
                if (cmd_pos > 0) { cmd_pos--; send("\b \b"); }
            } else if (cmd_pos < BUF_SIZE - 1) {
                cmd_buf[cmd_pos++] = byte;
                char echo[2] = {byte, 0};
                send(echo);
            }
        }
    }
}
