#include "ttp223.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static uint32_t last_press_time = 0;

void ttp223_init(void)
{
    ESP_LOGI(TAG_TTP223, "Inicializando sensor tactil...");

    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << TTP223_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_config);
    last_press_time = 0;

    ESP_LOGI(TAG_TTP223, "Inicializado correctamente.");
}

bool ttp223_is_pressed(void)
{
    uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

    if (gpio_get_level(TTP223_PIN) == 1) {
        if ((now - last_press_time) > TTP223_DEBOUNCE_MS) {
            last_press_time = now;
            return true;
        }
    }

    return false;
}
