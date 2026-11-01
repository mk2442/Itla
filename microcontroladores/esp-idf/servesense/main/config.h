#ifndef CONFIG_H
#define CONFIG_H

#define SYSTEM_NAME             "ServeSense"
#define SYSTEM_VERSION          "1.0.0"
#define TABLE_NAME              "Mesa 1"

#define TAG_BOOT                "BOOT"
#define TAG_HX711               "HX711"
#define TAG_LM35               "LM35"
#define TAG_TTP223             "TTP223"
#define TAG_SYSTEM              "SYSTEM"
#define TAG_LOADCELL            "LOADCELL"
#define TAG_TEMP                "TEMP"
#define TAG_WARNING             "WARNING"
#define TAG_LED                 "LED"
#define TAG_MOTOR               "MOTOR"
#define TAG_MESA                "MESA 1"
#define TAG_EVENT               "EVENT"
#define TAG_NETWORK             "NETWORK"

#define HX711_PIN_SCK           25
#define HX711_PIN_DOUT          26

#define LED_RED_PIN             14
#define LED_GREEN_PIN           12
#define LED_BLUE_PIN            13

#define LM35_PIN                34

#define VIBRATION_PIN           27

#define TTP223_PIN              32

#define LOADCELL_CALIBRATION    -7050.0f
#define LOADCELL_READ_INTERVAL_MS   200

#define WEIGHT_EMPTY_GLASS_G    600.0f
#define WEIGHT_FULL_GLASS_G     1003.0f
#define WEIGHT_DRINK_G          403.0f
#define WEIGHT_THRESHOLD_G      660.0f

#define TEMP_MAX_CELSIUS        12.0f
#define TEMP_READ_INTERVAL_MS   1000

#define VIBRATION_DURATION_MS   2000

#define TTP223_DEBOUNCE_MS      50

#define TASK_STACK_SIZE         4096
#define TASK_STACK_SIZE_LARGE   8192
#define TASK_PRIORITY_LOW       1
#define TASK_PRIORITY_NORMAL    3
#define TASK_PRIORITY_HIGH      5

typedef enum {
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_CONTAINER,
    SYSTEM_STATE_ALERT_LOW,
    SYSTEM_STATE_ALERT_TEMP,
    SYSTEM_STATE_ERROR
} system_state_t;

typedef enum {
    LED_COLOR_OFF,
    LED_COLOR_GREEN,
    LED_COLOR_YELLOW,
    LED_COLOR_RED
} led_color_t;

#endif
