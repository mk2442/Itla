/**
 * @file app_logic.c
 * @brief Logica principal del sistema ServeSense - Maquina de estados.
 */

#include "app_logic.h"
#include "config.h"
#include "hx711.h"
#include "temperature.h"
#include "button.h"
#include "motor.h"
#include "rgb_led.h"
#include "console.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static system_state_t current_state = SYSTEM_STATE_IDLE;
static bool request_pending = false;

static void handle_idle_state(void)
{
    float weight = hx711_read_grams();
    float temperature = temperature_read_celsius();

    console_print_weight(weight);
    console_print_temperature(temperature);

    if (hx711_container_detected()) {
        current_state = SYSTEM_STATE_CONTAINER;
        console_print_event("Recipiente detectado.");
        rgb_led_set_color(LED_COLOR_GREEN);
    }
}

static void handle_container_state(void)
{
    float weight = hx711_read_grams();
    float temperature = temperature_read_celsius();

    console_print_weight(weight);
    console_print_temperature(temperature);

    if (!hx711_container_detected()) {
        current_state = SYSTEM_STATE_IDLE;
        console_print_event("Recipiente retirado.");
        rgb_led_set_color(LED_COLOR_OFF);
        console_print_state("Esperando recipiente.");
        return;
    }

    if (temperature_is_over_limit()) {
        rgb_led_set_color(LED_COLOR_YELLOW);
        console_print_event("Temperatura fuera del rango.");
    } else {
        rgb_led_set_color(LED_COLOR_GREEN);
    }

    if (button_is_pressed() && !request_pending) {
        request_pending = true;
        current_state = SYSTEM_STATE_REQUEST_SENT;
        console_print_event("Solicitud enviada.");
        rgb_led_set_color(LED_COLOR_BLUE);
        console_print_network("Esperando confirmacion...");
    }
}

static void handle_request_sent_state(void)
{
    float weight = hx711_read_grams();
    float temperature = temperature_read_celsius();

    console_print_weight(weight);
    console_print_temperature(temperature);

    if (!hx711_container_detected()) {
        request_pending = false;
        current_state = SYSTEM_STATE_IDLE;
        console_print_event("Recipiente retirado.");
        rgb_led_set_color(LED_COLOR_OFF);
        console_print_state("Esperando recipiente.");
        return;
    }

    confirmar_recepcion();
    console_print_network("Solicitud confirmada.");

    motor_vibrate_ms(MOTOR_VIBRATION_MS);

    request_pending = false;
    current_state = SYSTEM_STATE_CONTAINER;
    rgb_led_set_color(LED_COLOR_GREEN);
}

static void handle_error_state(void)
{
    rgb_led_set_color(LED_COLOR_RED);
    console_print_event("Error del sistema.");
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void app_logic_init(void)
{
    ESP_LOGI(TAG_SYSTEM, "Inicializando logica principal...");
    current_state = SYSTEM_STATE_IDLE;
    request_pending = false;
    ESP_LOGI(TAG_SYSTEM, "Logica principal inicializada.");
}

void app_logic_task(void *pvParameters)
{
    console_print_state("Esperando recipiente.");

    while (1) {
        switch (current_state) {
            case SYSTEM_STATE_IDLE:
                handle_idle_state();
                break;
            case SYSTEM_STATE_CONTAINER:
                handle_container_state();
                break;
            case SYSTEM_STATE_REQUEST_SENT:
                handle_request_sent_state();
                break;
            case SYSTEM_STATE_ERROR:
                handle_error_state();
                break;
            default:
                current_state = SYSTEM_STATE_IDLE;
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(LOADCELL_READ_INTERVAL));
    }
}

void confirmar_recepcion(void)
{
    ESP_LOGI(TAG_NETWORK, "Contactando al mesero...");
    vTaskDelay(pdMS_TO_TICKS(500));
    ESP_LOGI(TAG_NETWORK, "Confirmacion recibida del mesero.");
}
