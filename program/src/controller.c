#include "headers/controller.h"

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <time.h>
#include <pico/mutex.h>
#include "wifi/headers/udp_server.h"
#include "wifi/headers/wifi_operator.h"

void controller_init(void)
{
    controller.is_running = true;

    stdio_init_all();

    if(cyw43_arch_init_with_country(CYW43_COUNTRY_FRANCE))
        controller.is_running = false;

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

    if(wifi_operator_init())
        controller.is_running = false;

    if(dhcp_server_init())
        controller.is_running = false;

    if(udp_server_init())
        controller.is_running = false;

    // Initialisation ended
    for(uint8_t i = 0, led_state = true; i < 5; i++)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);

        sleep_ms(100);

        led_state = !led_state;
    }
}

static inline void update_time(void)
{
    static float last_time = 0.0;
    float start_time = (float)clock() * 1000.0f / (float)CLOCKS_PER_SEC;
    controller.delta_time_ms = start_time - last_time;
    last_time = start_time;

    static float elapsed_time = 0.0f;
    elapsed_time += controller.delta_time_ms;

    static bool led_state = false;
    if(elapsed_time >= 1000.0f)
    {
        elapsed_time = 0.0f;

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);

        led_state = !led_state;
    }
}

void controller_handle_inputs_outputs(void)
{
    cyw43_arch_poll();

    update_time();

    udp_server_send();

    tight_loop_contents();
}

void controller_deinit(void)
{
    udp_server_deinit();
}
