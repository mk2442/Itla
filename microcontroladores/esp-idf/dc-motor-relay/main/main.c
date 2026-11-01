#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_console.h"
#include "linenoise/linenoise.h"
#include "motor.h"
#include "consola.h"

static void cli_task(void *arg)
{
    printf("\n===== CONTROL DC MOTOR =====\n");
    printf("motor on|off  | dir left|right | status | help\n\n");

    while (1) {
        char *line = linenoise("> ");
        if (!line) continue;
        linenoiseHistoryAdd(line);
        int ret;
        esp_console_run(line, &ret);
        linenoiseFree(line);
    }
}

void app_main(void)
{
    motor_init();

    setvbuf(stdin, NULL, _IONBF, 0);
    esp_console_config_t cfg = { .max_cmdline_length = 256, .max_cmdline_args = 8, .hint_color = 0 };
    esp_console_init(&cfg);
    linenoiseSetMultiLine(1);
    linenoiseHistorySetMaxLen(50);
    consola_init();

    xTaskCreate(cli_task, "cli", 4096, NULL, 5, NULL);
}
