#include "motor.h"
#include "esp_log.h"

static const char *TAG = "motor";
static bool encendido = false;
static motor_dir_t dir_actual = MOTOR_IZQ;

void motor_init(void)
{
    gpio_reset_pin(PIN_RELAY_DIR);
    gpio_reset_pin(PIN_RELAY_PWM);
    gpio_set_direction(PIN_RELAY_DIR, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_RELAY_PWM, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_RELAY_DIR, 0);
    gpio_set_level(PIN_RELAY_PWM, 0);
    ESP_LOGI(TAG, "Motor listo - IZQ, APAGADO");
}

void motor_encender(void)
{
    gpio_set_level(PIN_RELAY_PWM, 1);
    encendido = true;
    ESP_LOGI(TAG, "ON");
}

void motor_apagar(void)
{
    gpio_set_level(PIN_RELAY_PWM, 0);
    encendido = false;
    ESP_LOGI(TAG, "OFF");
}

bool motor_activo(void) { return encendido; }

void motor_direccion(motor_dir_t d)
{
    gpio_set_level(PIN_RELAY_DIR, d == MOTOR_DER ? 1 : 0);
    dir_actual = d;
    ESP_LOGI(TAG, "%s", d == MOTOR_DER ? "DERECHA" : "IZQUIERDA");
}

motor_dir_t motor_obtener_dir(void) { return dir_actual; }
