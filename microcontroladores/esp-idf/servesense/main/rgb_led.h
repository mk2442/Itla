#ifndef RGB_LED_H
#define RGB_LED_H

#include "config.h"

void rgb_led_init(void);
void rgb_led_set_color(led_color_t color);
void rgb_led_off(void);

#endif
