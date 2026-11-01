/**
 * @file console.c
 * @brief Modulo de consola para monitoreo del sistema.
 */

#include "console.h"
#include "config.h"
#include "esp_log.h"

void console_init(void)
{
    ESP_LOGI(TAG_BOOT, "Inicializando consola de monitoreo...");
    ESP_LOGI(TAG_BOOT, "Consola lista.");
}

void console_print_boot_banner(void)
{
    ESP_LOGI(TAG_BOOT, "========================================");
    ESP_LOGI(TAG_BOOT, "  %s v%s", SYSTEM_NAME, SYSTEM_VERSION);
    ESP_LOGI(TAG_BOOT, "  Portavasos Inteligente");
    ESP_LOGI(TAG_BOOT, "========================================");
    ESP_LOGI(TAG_BOOT, "Inicializando sistema...");
}

void console_print_state(const char *state)
{
    ESP_LOGI(TAG_SYSTEM, "%s", state);
}

void console_print_weight(float grams)
{
    ESP_LOGI(TAG_LOADCELL, "Peso: %.1f g", grams);
}

void console_print_temperature(float celsius)
{
    ESP_LOGI(TAG_TEMP, "Temperatura: %.1f C", celsius);
}

void console_print_event(const char *event)
{
    ESP_LOGI(TAG_EVENT, "%s", event);
}

void console_print_network(const char *message)
{
    ESP_LOGI(TAG_NETWORK, "%s", message);
}
