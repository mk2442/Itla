#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

#define SERVO_GPIO     GPIO_NUM_18
#define LEDC_TIMER     LEDC_TIMER_0
#define LEDC_MODE      LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL   LEDC_CHANNEL_0
#define LEDC_DUTY_RES  LEDC_TIMER_16_BIT

#define SERVO_MIN_PULSEWIDTH  500
#define SERVO_MAX_PULSEWIDTH  2500
#define SERVO_MIN_DEGREE      0
#define SERVO_MAX_DEGREE      180

static void servo_init(void)
{
    ledc_timer_config_t timer_conf = {
        .speed_mode      = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num       = LEDC_TIMER,
        .freq_hz         = 50,
        .clk_cfg         = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .speed_mode = LEDC_MODE,
        .channel    = LEDC_CHANNEL,
        .timer_sel  = LEDC_TIMER,
        .gpio_num   = SERVO_GPIO,
        .duty       = 0,
        .hpoint     = 0
    };
    ledc_channel_config(&channel_conf);
}

static void servo_set_angle(int angle)
{
    if (angle < SERVO_MIN_DEGREE) angle = SERVO_MIN_DEGREE;
    if (angle > SERVO_MAX_DEGREE) angle = SERVO_MAX_DEGREE;

    uint32_t max_duty = (1 << LEDC_DUTY_RES) - 1;
    uint32_t pulse_us = SERVO_MIN_PULSEWIDTH +
        (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * angle / SERVO_MAX_DEGREE;
    uint32_t duty = (pulse_us * max_duty) / (1000000 / 50);

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void app_main(void)
{
    servo_init();
    printf("Servo test iniciado\n");

    while (1) {
        for (int angle = 0; angle <= 180; angle += 5) {
            servo_set_angle(angle);
            printf("Angulo: %d grados\n", angle);
            vTaskDelay(pdMS_TO_TICKS(20));
        }

        for (int angle = 180; angle >= 0; angle -= 5) {
            servo_set_angle(angle);
            printf("Angulo: %d grados\n", angle);
            vTaskDelay(pdMS_TO_TICKS(20));
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
