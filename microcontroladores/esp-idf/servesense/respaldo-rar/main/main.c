/**
 * @file main.c
 * @brief Punto de entrada del firmware ServeSense.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "config.h"
#include "hx711.h"
#include "temperature.h"
#include "motor.h"
#include "rgb_led.h"
#include "button.h"
#include "console.h"
#include "app_logic.h"

static const char *TAG = "MAIN";

static void hx711_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Tarea HX711 iniciada.");
    while (1) {
        hx711_read_grams();
        vTaskDelay(pdMS_TO_TICKS(LOADCELL_READ_INTERVAL));
    }
}

static void temperature_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Tarea de temperatura iniciada.");
    while (1) {
        temperature_read_celsius();
        vTaskDelay(pdMS_TO_TICKS(TEMP_READ_INTERVAL));
    }
}

static void button_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Tarea de boton iniciada.");
    while (1) {
        button_is_pressed();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void app_main(void)
{
    console_print_boot_banner();

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Borrando NVS...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    console_init();
    ESP_LOGI(TAG_BOOT, "Inicializando modulos...");

    hx711_init();
    hx711_calibrate();

    temperature_init();

    rgb_led_init();
    rgb_led_set_color(LED_COLOR_GREEN);

    motor_init();
    button_init();
    app_logic_init();

    ESP_LOGI(TAG_BOOT, "Todos los modulos inicializados.");
    ESP_LOGI(TAG_BOOT, "Sistema listo.");

    xTaskCreate(hx711_task, "hx711_task", TASK_STACK_SIZE, NULL, TASK_PRIORITY_NORMAL, NULL);
    xTaskCreate(temperature_task, "temperature_task", TASK_STACK_SIZE, NULL, TASK_PRIORITY_NORMAL, NULL);
    xTaskCreate(button_task, "button_task", TASK_STACK_SIZE, NULL, TASK_PRIORITY_LOW, NULL);
    xTaskCreate(app_logic_task, "app_logic_task", TASK_STACK_SIZE * 2, NULL, TASK_PRIORITY_HIGH, NULL);

    ESP_LOGI(TAG, "Todas las tareas creadas.");

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
