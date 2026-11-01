#include "lm35.h"
#include "config.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static float current_temperature = 0.0f;
static adc_oneshot_unit_handle_t adc_handle = NULL;

void lm35_init(void)
{
    ESP_LOGI(TAG_LM35, "Inicializando sensor de temperatura...");

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &config));

    ESP_LOGI(TAG_LM35, "Inicializado correctamente.");
}

float lm35_read_celsius(void)
{
    int adc_raw = 0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL_6, &adc_raw));

    int voltage_mv = (adc_raw * 3300) / 4095;
    current_temperature = (float)voltage_mv / 10.0f;

    return current_temperature;
}

bool lm35_is_over_limit(void)
{
    return (current_temperature > TEMP_MAX_CELSIUS);
}
