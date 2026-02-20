#include "headers/inputs.h"

#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/adc.h>
#include "headers/controller.h"

#define JOYSTICK_DEAD_ZONE 5

void inputs_init(void)
{
    adc_init();
    adc_gpio_init(JOYSTICK_X_AXIS_PIN);
    adc_gpio_init(JOYSTICK_Y_AXIS_PIN);

    const uint BUTTONS_PIN[] = {BUTTON_BLACK_PIN, BUTTON_BLUE_PIN, BUTTON_WHITE_PIN, BUTTON_GREEN_PIN, BUTTON_L_PIN, BUTTON_R_PIN};

    for(size_t i = 0; i < sizeof(BUTTONS_PIN) / sizeof(uint); i++)
    {
        gpio_init(BUTTONS_PIN[i]);
        gpio_set_dir(BUTTONS_PIN[i], GPIO_IN);
        gpio_pull_up(BUTTONS_PIN[i]);
    }
}

void inputs_update(void)
{
    // Encoding in 9 bits for values to be between -256 and 255, not optimal now,
    // but useful later during transaction between the main controller and the motion controller.

    // Update joystick x and y position
    adc_select_input(JOYSTICK_X_AXIS_ADC_INPUT);
    uint16_t joystick_raw = adc_read();
    controller.inputs.joystick_x = (joystick_raw >> 3) - 256;

    adc_select_input(JOYSTICK_Y_AXIS_ADC_INPUT);
    joystick_raw = adc_read();
    controller.inputs.joystick_y = (joystick_raw >> 3) - 256;

    // Dead zone
    if(abs(controller.inputs.joystick_x) < JOYSTICK_DEAD_ZONE)
        controller.inputs.joystick_x = 0;

    if(abs(controller.inputs.joystick_y) < JOYSTICK_DEAD_ZONE)
        controller.inputs.joystick_y = 0;

    // Buttons
    controller.inputs.buttons.button_black = !gpio_get(BUTTON_BLACK_PIN);
    controller.inputs.buttons.button_blue  = !gpio_get(BUTTON_BLUE_PIN);
    controller.inputs.buttons.button_white = !gpio_get(BUTTON_WHITE_PIN);
    controller.inputs.buttons.button_green = !gpio_get(BUTTON_GREEN_PIN);
    controller.inputs.buttons.button_l     = !gpio_get(BUTTON_L_PIN);
    controller.inputs.buttons.button_r     = !gpio_get(BUTTON_R_PIN);
}
