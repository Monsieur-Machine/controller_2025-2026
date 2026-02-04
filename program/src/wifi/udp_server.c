#include "headers/udp_server.h"

#include <stdio.h>

udp_server_t udp_server;

int udp_server_init(void)
{
    udp_server.pcb = udp_new();
    if(udp_server.pcb == NULL)
    {
        puts("Error creating UDP server");
        return -1;
    }

    if(udp_bind(udp_server.pcb, IP_ADDR_ANY, UDP_SERVER_PORT))
    {
        printf("Error bind UDP server");
        return -1;
    }

    puts("UDP client started");

    return 0;
}

void udp_server_send(void)
{

}

void udp_server_deinit(void)
{
    if(udp_server.pcb)
    {
        udp_remove(udp_server.pcb);
        udp_server.pcb = NULL;
    }
}
