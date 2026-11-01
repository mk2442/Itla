/**
 * @file temperature.h
 * @brief Driver del sensor de temperatura.
 */

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdbool.h>

void temperature_init(void);
float temperature_read_celsius(void);
bool temperature_is_over_limit(void);

#endif
