#ifndef DHCP_SERVER_H
#define DHCP_SERVER_H

#include "lwip/ip_addr.h"

#define DHCPS_BASE_IP (16)
#define DHCPS_MAX_IP (8)

typedef struct _dhcp_server_lease_t {
    uint8_t mac[6];
    uint16_t expiry;
} dhcp_server_lease_t;

typedef struct _dhcp_server_t {
    ip_addr_t ip;
    ip_addr_t nm;
    dhcp_server_lease_t lease[DHCPS_MAX_IP];
    struct udp_pcb *pcb;
} dhcp_server_t;

int dhcp_server_init(void);
void dhcp_server_deinit(void);

#endif // DHCP_SERVER_H
