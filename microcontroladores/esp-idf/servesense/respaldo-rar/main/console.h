/**
 * @file console.h
 * @brief Modulo de consola para monitoreo.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

void console_init(void);
void console_print_boot_banner(void);
void console_print_state(const char *state);
void console_print_weight(float grams);
void console_print_temperature(float celsius);
void console_print_event(const char *event);
void console_print_network(const char *message);

#endif
