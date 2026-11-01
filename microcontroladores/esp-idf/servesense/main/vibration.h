#ifndef VIBRATION_H
#define VIBRATION_H

#include <stdint.h>

void vibration_init(void);
void vibration_on(void);
void vibration_off(void);
void vibration_pulse(uint32_t duration_ms);

#endif
