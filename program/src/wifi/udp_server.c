#include "headers/udp_server.h"

#include <stdio.h>
#include "headers/controller.h"

#define MSG_LEN 128

int udp_server_init(void)
{
    controller.udp_server.pcb = udp_new();
    if(controller.udp_server.pcb == NULL)
    {
        puts("Error creating UDP server");
        return -1;
    }

    if(udp_bind(controller.udp_server.pcb, IP_ADDR_ANY, UDP_SERVER_PORT))
    {
        printf("Error bind UDP server");
        return -1;
    }

    puts("UDP server started");

    return 0;
}

void udp_server_send(void)
{
    static float elapsed_time = 0.0f;
    elapsed_time += controller.delta_time_ms;

    static uint8_t counter = 0;

    if(elapsed_time >= 1000.0f)
    {
        elapsed_time = 0.0f;

        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, MSG_LEN, PBUF_RAM);
        uint8_t *payload = (uint8_t *)p->payload;
        payload[0] = counter;

        udp_sendto(controller.udp_server.pcb, p, IP_ADDR_ANY, UDP_CLIENT_PORT);

        pbuf_free(p);

        counter++;
    }
}

void udp_server_deinit(void)
{
    if(controller.udp_server.pcb)
    {
        udp_remove(controller.udp_server.pcb);
        controller.udp_server.pcb = NULL;
    }
}
