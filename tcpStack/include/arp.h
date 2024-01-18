#ifndef MYTCPSTACK_ARP_H
#define MYTCPSTACK_ARP_H

#include "ethernet.h"
#include "netdev.h"
#include "skbuff.h"

#include <linux/if_arp.h>
/*!
 *  \brief ARP：Address Resolution Protocol, 地址解析协议
 *  \details
 *  是一个通过解析网络层地址来找寻数据链路层地址的网络传输协议，它在IPv4中极其重要
 *  对于TCP/IP的实际实现来说，arp属于网络层协议，建立在数据链路层之上
 *  在IPv6中邻居发现协议（NDP）用于代替地址解析协议（ARP）
 *  */
struct arp_hdr {
    __be16 ar_hrd;        /* format of hardware address	*/
    __be16 ar_pro;        /* format of protocol address	*/
    unsigned char ar_hln;        /* length of hardware address	*/
    unsigned char ar_pln;        /* length of protocol address	*/
    __be16 ar_op;        /* ARP opcode (command)		*/
};



void arp_init();
void free_arp();
void arp_rcv(struct sk_buff* skb);
void arp_reply(struct sk_buff* skb, struct netdev* dev);
void arp_request(uint32_t sip, uint32_t dip, struct netdev* dev);
uint8_t* arp_get_hardware_addr(uint32_t sip);

static inline struct arp_hdr* arp_hdr(struct sk_buff* skb) {
    return (struct arp_hdr*)(skb->head +ETH_HDR_LEN);
}

#endif //MYTCPSTACK_ARP_H
