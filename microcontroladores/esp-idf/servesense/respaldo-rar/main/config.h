/**
 * @file config.h
 * @brief Configuración central del sistema ServeSense.
 */

#ifndef CONFIG_H
#define CONFIG_H

#define SYSTEM_NAME             "ServeSense"
#define SYSTEM_VERSION          "1.0.0"

#define TAG_BOOT                "BOOT"
#define TAG_HX711               "HX711"
#define TAG_TEMP                "TEMP"
#define TAG_SYSTEM              "SYSTEM"
#define TAG_LOADCELL            "LOADCELL"
#define TAG_EVENT               "EVENT"
#define TAG_BUTTON              "BUTTON"
#define TAG_NETWORK             "NETWORK"
#define TAG_MOTOR               "MOTOR"
#define TAG_LED                 "LED"

#define HX711_PIN_SCK           25
#define HX711_PIN_DOUT          26

#define LED_RED_PIN             14
#define LED_GREEN_PIN           12
#define LED_BLUE_PIN            13

#define TEMP_SENSOR_PIN         34

#define MOTOR_PIN               27

#define BUTTON_PIN              32

#define LOADCELL_THRESHOLD_G    50.0f
#define LOADCELL_MAX_KG         5.0f
#define LOADCELL_CALIBRATION    -7050.0f
#define LOADCELL_READ_INTERVAL  200

#define TEMPERATURA_MAXIMA      45.0f
#define TEMP_READ_INTERVAL      1000

#define MOTOR_VIBRATION_MS      2000

#define BUTTON_DEBOUNCE_MS      50

#define TASK_STACK_SIZE         4096
#define TASK_PRIORITY_LOW       1
#define TASK_PRIORITY_NORMAL    3
#define TASK_PRIORITY_HIGH      5

typedef enum {
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_CONTAINER,
    SYSTEM_STATE_REQUEST_SENT,
    SYSTEM_STATE_ERROR
} system_state_t;

typedef enum {
    LED_COLOR_OFF,
    LED_COLOR_GREEN,
    LED_COLOR_BLUE,
    LED_COLOR_YELLOW,
    LED_COLOR_RED
} led_color_t;

#endif
