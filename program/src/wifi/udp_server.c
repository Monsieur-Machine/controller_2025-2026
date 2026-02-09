#include "headers/udp_server.h"

#include <stdio.h>
#include <string.h>
#include "headers/controller.h"

#define MSG_LEN (sizeof(uint16_t) + sizeof(inputs_t)) / sizeof(uint8_t)
#define MSG_DELAY_MS 50.0f

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
        puts("Error binding UDP server");
        return -1;
    }

    return 0;
}

void udp_server_send(void)
{
    static float elapsed_time_ms = 0.0f;
    elapsed_time_ms += controller.delta_time_ms;

    static uint8_t counter = 0;

    if(elapsed_time_ms >= MSG_DELAY_MS)
    {
        static union data_t {
            struct {
                uint16_t packet_number;
                inputs_t inputs;
            } hard;

            uint8_t raw[MSG_LEN];
        } data = {0};

        data.hard.packet_number++;
        data.hard.inputs = controller.inputs;

        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, MSG_LEN, PBUF_RAM);
        memcpy((uint8_t *)p->payload, data.raw, MSG_LEN);
        //printf("%d:%d   %d\n", data.raw[2], data.raw[3], data.raw[4]);

        err_t error_code = udp_sendto(controller.udp_server.pcb, p, IP_ADDR_ANY, UDP_CLIENT_PORT);

        pbuf_free(p);

        if(error_code)
        {
            printf("UDP send error : %d\n", error_code);
        }

        elapsed_time_ms = 0.0f;
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
