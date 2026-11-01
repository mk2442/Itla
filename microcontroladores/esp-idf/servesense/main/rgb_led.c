#include "rgb_led.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"

void rgb_led_init(void)
{
    ESP_LOGI(TAG_LED, "Inicializando LED RGB...");

    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << LED_RED_PIN) |
                        (1ULL << LED_GREEN_PIN) |
                        (1ULL << LED_BLUE_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_config);
    rgb_led_off();

    ESP_LOGI(TAG_LED, "Inicializado correctamente.");
}

void rgb_led_set_color(led_color_t color)
{
    gpio_set_level(LED_RED_PIN, 0);
    gpio_set_level(LED_GREEN_PIN, 0);
    gpio_set_level(LED_BLUE_PIN, 0);

    switch (color) {
        case LED_COLOR_GREEN:
            gpio_set_level(LED_GREEN_PIN, 1);
            ESP_LOGI(TAG_LED, "Verde");
            break;
        case LED_COLOR_YELLOW:
            gpio_set_level(LED_RED_PIN, 1);
            gpio_set_level(LED_GREEN_PIN, 1);
            ESP_LOGI(TAG_LED, "Amarillo");
            break;
        case LED_COLOR_RED:
            gpio_set_level(LED_RED_PIN, 1);
            ESP_LOGI(TAG_LED, "Rojo");
            break;
        case LED_COLOR_OFF:
        default:
            ESP_LOGI(TAG_LED, "Apagado");
            break;
    }
}

void rgb_led_off(void)
{
    gpio_set_level(LED_RED_PIN, 0);
    gpio_set_level(LED_GREEN_PIN, 0);
    gpio_set_level(LED_BLUE_PIN, 0);
}
