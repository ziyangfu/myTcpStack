

#ifndef MYTCPSTACK_NETDEV_H
#define MYTCPSTACK_NETDEV_H

#include <stdint.h>

#define BUFLEN 1600
#define MAX_ADDR_LEN 32


struct netdev {
    uint32_t    addr;
    uint8_t     addr_len;
    uint8_t     hwaddr[6];
    uint32_t    mtu;
};

void netdev_init();
void netdev_transmit();
void *netdev_rx_loop();
void free_netdev();

struct netdev* netdev_get(uint32_t sip);

#endif //MYTCPSTACK_NETDEV_H
