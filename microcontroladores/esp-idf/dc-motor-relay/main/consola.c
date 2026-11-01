#include "consola.h"
#include "motor.h"
#include <string.h>
#include "esp_console.h"
#include "esp_log.h"

static const char *TAG = "consola";

static int cmd_motor(int argc, char **argv)
{
    if (argc < 2) { printf("uso: motor on|off\n"); return 1; }
    if      (!strcmp(argv[1], "on"))  { motor_encender(); printf("OK on\n"); }
    else if (!strcmp(argv[1], "off")) { motor_apagar();   printf("OK off\n"); }
    else { printf("? %s\n", argv[1]); return 1; }
    return 0;
}

static int cmd_dir(int argc, char **argv)
{
    if (argc < 2) { printf("uso: dir left|right\n"); return 1; }
    if      (!strcmp(argv[1], "right")) { motor_direccion(MOTOR_DER); printf("OK derecha\n"); }
    else if (!strcmp(argv[1], "left"))  { motor_direccion(MOTOR_IZQ); printf("OK izquierda\n"); }
    else { printf("? %s\n", argv[1]); return 1; }
    return 0;
}

static int cmd_status(int argc, char **argv)
{
    printf("motor: %s\n", motor_activo() ? "ENCENDIDO" : "APAGADO");
    printf("dir:   %s\n", motor_obtener_dir() == MOTOR_DER ? "DERECHA" : "IZQUIERDA");
    return 0;
}

void consola_init(void)
{
    esp_console_register_help_command();

    esp_console_cmd_t cmds[] = {
        { .command = "motor",  .help = "motor on|off",          .func = cmd_motor },
        { .command = "dir",    .help = "dir left|right",        .func = cmd_dir },
        { .command = "status", .help = "estado del motor",      .func = cmd_status },
    };
    for (int i = 0; i < 3; i++)
        ESP_ERROR_CHECK(esp_console_cmd_register(&cmds[i]));

    ESP_LOGI(TAG, "cmds: motor, dir, status, help");
}
