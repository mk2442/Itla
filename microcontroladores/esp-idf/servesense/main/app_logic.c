#include "app_logic.h"
#include "config.h"
#include "hx711.h"
#include "lm35.h"
#include "ttp223.h"
#include "vibration.h"
#include "rgb_led.h"
#include "console.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static system_state_t current_state = SYSTEM_STATE_IDLE;
static float last_logged_weight = -1.0f;
static float last_logged_temp = -999.0f;

static void trigger_alert_low_battery(void)
{
    ESP_LOGW(TAG_WARNING, "Peso: %.0f g", last_logged_weight);
    rgb_led_set_color(LED_COLOR_RED);
    vibration_pulse(VIBRATION_DURATION_MS);
    console_print_mesa("Bebida agotada.");
}

static void trigger_alert_high_temp(void)
{
    ESP_LOGW(TAG_WARNING, "Temperatura: %.1f C", last_logged_temp);
    rgb_led_set_color(LED_COLOR_YELLOW);
    vibration_pulse(VIBRATION_DURATION_MS);
    console_print_mesa("Temperatura fuera del rango.");
}

static void handle_idle_state(void)
{
    float weight = hx711_read_grams();
    float temperature = lm35_read_celsius();

    if (weight != last_logged_weight) {
        console_print_weight(weight);
        last_logged_weight = weight;
    }
    if (temperature != last_logged_temp) {
        console_print_temperature(temperature);
        last_logged_temp = temperature;
    }

    if (hx711_container_detected()) {
        current_state = SYSTEM_STATE_CONTAINER;
        console_print_event("Recipiente detectado.");
        console_print_state("Monitoreando bebida...");
        rgb_led_set_color(LED_COLOR_GREEN);
    }
}

static void handle_container_state(void)
{
    float weight = hx711_read_grams();
    float temperature = lm35_read_celsius();

    if (weight != last_logged_weight) {
        console_print_weight(weight);
        last_logged_weight = weight;
    }
    if (temperature != last_logged_temp) {
        console_print_temperature(temperature);
        last_logged_temp = temperature;
    }

    if (!hx711_container_detected()) {
        current_state = SYSTEM_STATE_IDLE;
        last_logged_weight = -1.0f;
        last_logged_temp = -999.0f;
        console_print_event("Recipiente retirado.");
        rgb_led_set_color(LED_COLOR_OFF);
        console_print_state("Esperando recipiente.");
        return;
    }

    if (hx711_drink_depleted()) {
        current_state = SYSTEM_STATE_ALERT_LOW;
        trigger_alert_low_battery();
        return;
    }

    if (lm35_is_over_limit()) {
        current_state = SYSTEM_STATE_ALERT_TEMP;
        trigger_alert_high_temp();
        return;
    }

    rgb_led_set_color(LED_COLOR_GREEN);

    if (ttp223_is_pressed()) {
        console_print_mesa("Solicita atencion.");
        vibration_pulse(VIBRATION_DURATION_MS);
    }
}

static void handle_alert_low_state(void)
{
    hx711_read_grams();
    lm35_read_celsius();

    rgb_led_set_color(LED_COLOR_RED);

    if (!hx711_container_detected()) {
        current_state = SYSTEM_STATE_IDLE;
        last_logged_weight = -1.0f;
        last_logged_temp = -999.0f;
        console_print_event("Recipiente retirado.");
        rgb_led_set_color(LED_COLOR_OFF);
        console_print_state("Esperando recipiente.");
        return;
    }

    if (ttp223_is_pressed()) {
        console_print_mesa("Solicita atencion.");
        vibration_pulse(VIBRATION_DURATION_MS);
    }
}

static void handle_alert_temp_state(void)
{
    hx711_read_grams();
    lm35_read_celsius();

    rgb_led_set_color(LED_COLOR_YELLOW);

    if (!hx711_container_detected()) {
        current_state = SYSTEM_STATE_IDLE;
        last_logged_weight = -1.0f;
        last_logged_temp = -999.0f;
        console_print_event("Recipiente retirado.");
        rgb_led_set_color(LED_COLOR_OFF);
        console_print_state("Esperando recipiente.");
        return;
    }

    if (!lm35_is_over_limit()) {
        current_state = SYSTEM_STATE_CONTAINER;
        rgb_led_set_color(LED_COLOR_GREEN);
        console_print_event("Temperatura normalizada.");
        return;
    }

    if (ttp223_is_pressed()) {
        console_print_mesa("Solicita atencion.");
        vibration_pulse(VIBRATION_DURATION_MS);
    }
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
    last_logged_weight = -1.0f;
    last_logged_temp = -999.0f;
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
            case SYSTEM_STATE_ALERT_LOW:
                handle_alert_low_state();
                break;
            case SYSTEM_STATE_ALERT_TEMP:
                handle_alert_temp_state();
                break;
            case SYSTEM_STATE_ERROR:
                handle_error_state();
                break;
            default:
                current_state = SYSTEM_STATE_IDLE;
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(LOADCELL_READ_INTERVAL_MS));
    }
}
