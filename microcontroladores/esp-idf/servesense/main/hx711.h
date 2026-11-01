#ifndef HX711_H
#define HX711_H

#include <stdbool.h>

void hx711_init(void);
void hx711_calibrate(void);
float hx711_read_grams(void);
bool hx711_container_detected(void);
bool hx711_drink_depleted(void);

#endif
