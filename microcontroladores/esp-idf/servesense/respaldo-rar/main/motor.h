/**
 * @file motor.h
 * @brief Driver del motor vibrador.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

void motor_init(void);
void motor_on(void);
void motor_off(void);
void motor_vibrate_ms(uint32_t duration_ms);

#endif
