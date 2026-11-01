#include "stepper.h"
#include "rom/ets_sys.h"

static const int half_seq[8][4] = {
    {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},
    {0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}
};

static const int full_seq[4][4] = {
    {1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}
};

static void apply_pins(stepper_t *s) {
    const int (*seq)[4] = (s->mode == 0) ? half_seq : full_seq;
    gpio_set_level(s->pin1, seq[s->step_index][0]);
    gpio_set_level(s->pin2, seq[s->step_index][1]);
    gpio_set_level(s->pin3, seq[s->step_index][2]);
    gpio_set_level(s->pin4, seq[s->step_index][3]);
}

static void step_once(stepper_t *s, int dir) {
    int max_idx = (s->mode == 0) ? 7 : 3;
    s->step_index += dir;
    if (s->step_index > max_idx) s->step_index = 0;
    if (s->step_index < 0) s->step_index = max_idx;
    apply_pins(s);
    float deg = (s->mode == 0) ? 5.625f / 64.0f : 5.625f / 32.0f;
    s->current_step += dir;
    s->current_deg += dir * deg;
}

void stepper_init(stepper_t *s, gpio_num_t p1, gpio_num_t p2, gpio_num_t p3, gpio_num_t p4) {
    s->pin1 = p1; s->pin2 = p2; s->pin3 = p3; s->pin4 = p4;
    s->step_index = 0;
    s->mode = 0;
    s->current_step = 0;
    s->current_deg = 0.0f;
    s->steps_per_rev = 4096;
    s->step_delay_us = 2000;

    gpio_config_t io = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = (1ULL << p1) | (1ULL << p2) | (1ULL << p3) | (1ULL << p4)
    };
    gpio_config(&io);
    stepper_release(s);
}

void stepper_release(stepper_t *s) {
    gpio_set_level(s->pin1, 0);
    gpio_set_level(s->pin2, 0);
    gpio_set_level(s->pin3, 0);
    gpio_set_level(s->pin4, 0);
}

void stepper_set_mode(stepper_t *s, int mode) {
    s->mode = mode;
    s->steps_per_rev = (mode == 0) ? 4096 : 2048;
}

void stepper_set_speed(stepper_t *s, unsigned long us) {
    if (us < 500) us = 500;
    if (us > 10000) us = 10000;
    s->step_delay_us = us;
}

void stepper_move_steps(stepper_t *s, long steps, int dir) {
    for (long i = 0; i < steps; i++) {
        step_once(s, dir);
        ets_delay_us(s->step_delay_us);
    }
    stepper_release(s);
}

void stepper_move_degrees(stepper_t *s, float deg, int dir) {
    float dps = (s->mode == 0) ? 5.625f / 64.0f : 5.625f / 32.0f;
    stepper_move_steps(s, (long)(deg / dps), dir);
}

void stepper_move_rotations(stepper_t *s, float rot, int dir) {
    stepper_move_steps(s, (long)(rot * s->steps_per_rev), dir);
}

void stepper_home(stepper_t *s) {
    if (s->current_step == 0) return;
    int dir = (s->current_step > 0) ? -1 : 1;
    stepper_move_steps(s, s->current_step * dir, dir);
}
