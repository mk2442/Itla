#include "hx711.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static float calibration_factor = LOADCELL_CALIBRATION;
static float current_weight = 0.0f;

static void hx711_pulse_sck(int pulses)
{
    for (int i = 0; i < pulses; i++) {
        gpio_set_level(HX711_PIN_SCK, 1);
        esp_rom_delay_us(1);
        gpio_set_level(HX711_PIN_SCK, 0);
        esp_rom_delay_us(1);
    }
}

static bool hx711_wait_ready(void)
{
    int timeout = 100;
    while (gpio_get_level(HX711_PIN_DOUT) == 1 && timeout > 0) {
        vTaskDelay(pdMS_TO_TICKS(1));
        timeout--;
    }
    return (timeout > 0);
}

static int32_t hx711_read_raw(void)
{
    if (!hx711_wait_ready()) {
        ESP_LOGW(TAG_HX711, "Timeout esperando DOUT");
        return 0;
    }

    int32_t value = 0;
    for (int i = 0; i < 24; i++) {
        gpio_set_level(HX711_PIN_SCK, 1);
        esp_rom_delay_us(1);
        value = (value << 1) | gpio_get_level(HX711_PIN_DOUT);
        gpio_set_level(HX711_PIN_SCK, 0);
        esp_rom_delay_us(1);
    }

    hx711_pulse_sck(1);

    if (value & 0x800000) {
        value |= (int32_t)0xFF000000;
    }

    return value;
}

void hx711_init(void)
{
    ESP_LOGI(TAG_HX711, "Inicializando HX711...");

    gpio_config_t io_sck = {
        .pin_bit_mask = (1ULL << HX711_PIN_SCK),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_sck);

    gpio_config_t io_dout = {
        .pin_bit_mask = (1ULL << HX711_PIN_DOUT),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_dout);

    gpio_set_level(HX711_PIN_SCK, 0);
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG_HX711, "Inicializado correctamente.");
}

void hx711_calibrate(void)
{
    ESP_LOGI(TAG_HX711, "Calibrando celda de carga...");

    for (int i = 0; i < 10; i++) {
        hx711_read_raw();
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    calibration_factor = LOADCELL_CALIBRATION;
    ESP_LOGI(TAG_HX711, "Calibracion completada. Factor: %.2f", calibration_factor);
}

float hx711_read_grams(void)
{
    int32_t raw = hx711_read_raw();
    current_weight = (float)raw / calibration_factor;

    if (current_weight < 0.0f) {
        current_weight = 0.0f;
    }

    return current_weight;
}

bool hx711_container_detected(void)
{
    return (current_weight > (WEIGHT_EMPTY_GLASS_G - 50.0f));
}

bool hx711_drink_depleted(void)
{
    return (current_weight <= WEIGHT_THRESHOLD_G);
}
