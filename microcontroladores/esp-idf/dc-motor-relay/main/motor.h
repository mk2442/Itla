#pragma once
#include <stdbool.h>
#include "driver/gpio.h"

#define PIN_RELAY_DIR  GPIO_NUM_26
#define PIN_RELAY_PWM  GPIO_NUM_27

typedef enum { MOTOR_IZQ, MOTOR_DER } motor_dir_t;

void motor_init(void);
void motor_encender(void);
void motor_apagar(void);
bool motor_activo(void);
void motor_direccion(motor_dir_t d);
motor_dir_t motor_obtener_dir(void);
