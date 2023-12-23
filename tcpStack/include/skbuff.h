

#ifndef MYTCPSTACK_SKBUFF_H
#define MYTCPSTACK_SKBUFF_H

#include "list.h"
#include "netdev.h"
#include "route.h"

/*!
 * \brief sk_buff，串联IP层、TCP层
 * */
struct sk_buff {
    struct list_head    list;
    struct rtentry*     rt;             /** TODO: 释义 */
    struct netdev*      dev;
    int                 refcnt;
    uint16_t            protocol;
    uint32_t            len;
    uint32_t            dlen;
    uint32_t            seq;
    uint32_t            end_seq;
    uint8_t*            end;
    uint8_t*            head;
    uint8_t*            data;
    uint8_t*            payload;
};

struct sk_buff_head {
    struct list_head    head;
    uint32_t            qlen;
};


struct sk_buff* alloc_skb(uint32_t size);
void free_skb(struct sk_buff* skb);

uint8_t* skb_push(struct sk_buff* skb, uint32_t len);
uint8_t* skb_head(struct sk_buff* skb);

void* skb_reserve(struct sk_buff* skb, uint32_t len);
void skb_reset_header(struct sk_buff* skb);



#endif //MYTCPSTACK_SKBUFF_H
