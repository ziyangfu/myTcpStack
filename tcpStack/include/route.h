

#ifndef MYTCPSTACK_ROUTE_H
#define MYTCPSTACK_ROUTE_H

#include "list.h"
#include <stdint.h>

/*!
 * \brief  结构体释义
 * */
struct rtentry {
    struct list_head    list;
    uint32_t            dst;        /** 释义 */
    uint32_t            gateway;
    uint32_t            netmask;
    uint8_t             flags;
    uint32_t            metric;
    struct netdev*      dev;
};

void route_init();
struct rtentry* route_lookup(uint32_t daddr);
void free_routes();



#endif //MYTCPSTACK_ROUTE_H
