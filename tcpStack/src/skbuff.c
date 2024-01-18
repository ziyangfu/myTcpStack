//
// Created by fzy on 23-12-25.
//
#include "skbuff.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>
struct sk_buff* alloc_skb(uint32_t size) {
    struct sk_buff* skb = malloc(sizeof(struct sk_buff));
    skb->data = malloc(size);
    memset(skb->data, 0, sizeof(struct sk_buff));

    skb->refcnt = 0;
    skb->head = skb->data;
    skb->end = skb->data + size;

    INIT_LIST_HEAD(&skb->list);
    return skb;
}
void free_skb(struct sk_buff* skb) {
    if (skb->refcnt < 1) {
        free(skb->head);
        free(skb);
    }
}

uint8_t* skb_push(struct sk_buff* skb, uint32_t len) {
    skb->data -= len;
    skb->len += len;
    return skb->data;
}
uint8_t* skb_head(struct sk_buff* skb) {
    return skb->head;
}

void* skb_reserve(struct sk_buff* skb, uint32_t len) {
    skb->data += len;
    return skb->data;
}
void skb_reset_header(struct sk_buff* skb) {
    skb->data = skb->end - skb->dlen;
    skb->len = skb->dlen;
}