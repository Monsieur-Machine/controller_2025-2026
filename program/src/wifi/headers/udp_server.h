#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <stdint.h>
#include <lwip/udp.h>

#define UDP_SERVER_PORT 4242
#define UDP_CLIENT_PORT 4243

typedef struct udp_server_t {
    struct udp_pcb *pcb;
} udp_server_t;

// Init udp client, set callback to NULL for the default callback
int udp_server_init(void);
// Send all data to robot
void udp_server_send(void);
// Exit udp client
void udp_server_deinit(void);

#endif // UDP_SERVER_H