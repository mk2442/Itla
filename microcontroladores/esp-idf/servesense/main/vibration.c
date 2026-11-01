#include "vibration.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void vibration_init(void)
{
    ESP_LOGI(TAG_MOTOR, "Inicializando motor vibrador...");

    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << VIBRATION_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_config);
    gpio_set_level(VIBRATION_PIN, 0);

    ESP_LOGI(TAG_MOTOR, "Inicializado correctamente.");
}

void vibration_on(void)
{
    ESP_LOGI(TAG_MOTOR, "ON");
    gpio_set_level(VIBRATION_PIN, 1);
}

void vibration_off(void)
{
    ESP_LOGI(TAG_MOTOR, "OFF");
    gpio_set_level(VIBRATION_PIN, 0);
}

void vibration_pulse(uint32_t duration_ms)
{
    vibration_on();
    vTaskDelay(pdMS_TO_TICKS(duration_ms));
    vibration_off();
}
