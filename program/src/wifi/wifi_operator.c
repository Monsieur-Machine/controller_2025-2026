#include "headers/wifi_operator.h"

#include <stdio.h>
#include <pico/cyw43_arch.h>
#include <lwip/netif.h>
#include <lwip/ip4_addr.h>

int wifi_operator_init(void)
{
    if(cyw43_wifi_pm(&cyw43_state, CYW43_NO_POWERSAVE_MODE))
    {
        puts("CYW43 no powersave mode failed");
        return -1;
    }

    cyw43_arch_enable_ap_mode(WIFI_OPERATOR_SSID, WIFI_OPERATOR_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);

    cyw43_wifi_ap_set_channel(&cyw43_state, WIFI_OPERATOR_CHANNEL);

    puts("AP mode enabled");

    return 0;
}
