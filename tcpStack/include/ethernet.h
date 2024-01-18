//
// Created by fzy on 23-12-26.
//

#ifndef MYTCPSTACK_ETHERNET_H
#define MYTCPSTACK_ETHERNET_H

#include <linux/if_ether.h>  /** 不需要 */
#include <arpa/inet.h>

#include "netdev.h"
#include "skbuff.h"

#define ETH_HDR_LEN sizeof(struct eth_hdr)

/** 照抄自 ethhdr，改了名字 */
struct eth_hdr {
    uint8_t dmac[6];        /** 目标mac地址 */
    uint8_t smac[6];        /** 源mac地址 */
    uint16_t ethertype;     /** 以太网协议类型，如 IPv4（0x0800）、ARP（0x0806）、IPv6（0x86DD），大端字节序 */
    uint8_t payload[];
} __attribute__((packed));  /** 表示这个结构体应该以紧凑的方式存储在内存中，而不进行对齐 */

static inline struct eth_hdr* eth_hdr(struct sk_buff* skb) {
    struct eth_hdr* hdr = (struct eth_hdr*) skb_head(skb);
    hdr->ethertype = ntohs(hdr->ethertype);
    return hdr;
}

#endif //MYTCPSTACK_ETHERNET_H
