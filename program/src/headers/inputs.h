#ifndef INPUTS_H
#define INPUTS_H

#include <pico/types.h>

typedef enum inputs_pin_t {
    JOYSTICK_X_AXIS_PIN = 26,
    JOYSTICK_Y_AXIS_PIN = 27,

    BUTTON_BLACK_PIN = 1,
    BUTTON_BLUE_PIN = 5,
    BUTTON_WHITE_PIN = 6,
    BUTTON_GREEN_PIN = 2,

    BUTTON_L_PIN = 13,
    BUTTON_R_PIN = 9,
}  inputs_pin_t;

#define JOYSTICK_X_AXIS_ADC_INPUT 0
#define JOYSTICK_Y_AXIS_ADC_INPUT 1

typedef struct inputs_t {
    int16_t joystick_x;
    int16_t joystick_y;

    struct {
        bool button_black : 1;
        bool button_blue  : 1;
        bool button_white : 1;
        bool button_green : 1;
        bool button_l     : 1;
        bool button_r     : 1;
    } buttons;
} __attribute__((__packed__)) inputs_t;

// Init all inputs
void inputs_init(void);
// Update inputs
void inputs_update(void);

#endif // INPUTS_H