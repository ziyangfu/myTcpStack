#include "arp.h"
#include <pthread.h>
#include <arpa/inet.h>

/** 广播mac地址 */
static uint8_t broadcast_hw[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static struct sk_buff* arp_alloc_skb() {
    struct sk_buff* skb = alloc_skb(ETH_HDR_LEN + ARP_HDR_LEN + ARP_DATA_LEN);
    skb_reserve(skb, ETH_HDR_LEN + ARP_HDR_LEN + ARP_DATA_LEN);
    skb->protocol = htons(ETH_P_ARP);
    return skb;
}



void arp_init() {

}
void free_arp() {

}
void arp_rcv(struct sk_buff* skb) {

}
void arp_reply(struct sk_buff* skb, struct netdev* dev) {

}
void arp_request(uint32_t sip, uint32_t dip, struct netdev* dev) {

}
uint8_t* arp_get_hardware_addr(uint32_t sip) {

}
