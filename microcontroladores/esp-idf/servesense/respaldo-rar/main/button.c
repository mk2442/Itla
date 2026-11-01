/**
 * @file button.c
 * @brief Driver del botón de solicitud con debounce.
 */

#include "button.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static uint32_t last_press_time = 0;

void button_init(void)
{
    ESP_LOGI(TAG_BUTTON, "Inicializando boton de solicitud...");

    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_config);
    last_press_time = 0;

    ESP_LOGI(TAG_BUTTON, "Boton inicializado correctamente.");
}

bool button_is_pressed(void)
{
    uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

    if (gpio_get_level(BUTTON_PIN) == 0) {
        if ((now - last_press_time) > BUTTON_DEBOUNCE_MS) {
            last_press_time = now;
            return true;
        }
    }

    return false;
}

void button_clear(void)
{
    last_press_time = xTaskGetTickCount() * portTICK_PERIOD_MS;
}
