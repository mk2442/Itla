#ifndef STEPPER_H
#define STEPPER_H

#include "driver/gpio.h"

typedef struct {
    gpio_num_t pin1;
    gpio_num_t pin2;
    gpio_num_t pin3;
    gpio_num_t pin4;
    int step_index;
    int mode;
    long current_step;
    float current_deg;
    long steps_per_rev;
    unsigned long step_delay_us;
} stepper_t;

void stepper_init(stepper_t *s, gpio_num_t p1, gpio_num_t p2, gpio_num_t p3, gpio_num_t p4);
void stepper_release(stepper_t *s);
void stepper_set_mode(stepper_t *s, int mode);
void stepper_set_speed(stepper_t *s, unsigned long us);
void stepper_move_steps(stepper_t *s, long steps, int dir);
void stepper_move_degrees(stepper_t *s, float deg, int dir);
void stepper_move_rotations(stepper_t *s, float rot, int dir);
void stepper_home(stepper_t *s);

#endif
