#ifndef CONSOLE_H
#define CONSOLE_H

void console_init(void);
void console_print_boot_banner(void);
void console_print_state(const char *state);
void console_print_weight(float grams);
void console_print_temperature(float celsius);
void console_print_event(const char *event);
void console_print_warning(const char *message);
void console_print_mesa(const char *message);

#endif
