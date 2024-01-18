

#ifndef MYTCPSTACK_SKBUFF_H
#define MYTCPSTACK_SKBUFF_H

#include "list.h"
#include "netdev.h"
#include "route.h"

/*!
 * \brief sk_buff，串联IP层、TCP层
 * --------------------------------------------------------------------
 * sk_buff
 * head  ---------------->  |
 * data                     |
 * tail
 * end
 *
 * */
struct sk_buff {
    struct list_head    list;
    struct rtentry*     rt;             /** TODO: 释义 */
    struct netdev*      dev;
    int                 refcnt;         /** TODO: 代表什么？ */
    uint16_t            protocol;       /** 来自驱动程序（数据链路层）的包协议 */
    uint32_t            len;            /** 缓冲区长度 */
    uint32_t            dlen;
    uint32_t            seq;            /** 第一个seq序号 */
    uint32_t            end_seq;        /** 最后一个seq序号 */
    uint8_t*            end;            /** 指向缓冲区末端 */
    uint8_t*            head;           /** 指向skb缓冲区的头部 */
    uint8_t*            data;           /** 指向数据头部的指针，在L2 ~ L4时移动 */
    uint8_t*            payload;        /** 负载 */
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

static inline uint32_t skb_queue_len(const struct sk_buff_head* list) {
    return list->qlen;
}

static inline void skb_queue_init(struct sk_buff_head* list) {
    INIT_LIST_HEAD(&list->head);
    list->qlen = 0;
}
/*!
 * \brief 在next前插入一个sk_buff节点（new）
 * */
static inline void skb_queue_add(struct sk_buff_head* list, struct sk_buff* new, struct sk_buff* next){
    list_add_tail(&new->list, &next->list);
    list->qlen += 1;

}
/*!
 * \brief 在list前插入一个sk_buff节点（new）
 * */
static inline void skb_queue_add2(struct sk_buff_head* list, struct sk_buff* new){
    list_add(&new->list, &list->head);
    list->qlen += 1;

}
/*!
 * \brief  在list后添加一个sk_buff节点（new）
 * */
static inline void skb_queue_tail(struct sk_buff_head* list, struct sk_buff* new) {
    list_add_tail(&new->list, &list->head);
    list->qlen += 1;
}

/*!
 * \brief 从链表中取出一个节点对应的sk_buff结构体，并且从链表中删除该节点
 * \details
 *      注意，此时节点只是不在链表上了，但还在内存中，如果之前拿到了该节点的指针，那就还可以访问
 *      如果要在外面使用，记得free
 * */
static inline struct sk_buff* skb_dequeue(struct sk_buff_head* list) {
    struct sk_buff* skb = list_first_entry(&list->head, struct sk_buff, list);  /** 取出链表头节点对应的sk_buff结构体 */
    list_del(&skb->list);
    list->qlen -= 1;
    return skb;
}

/*!
 * \brief 判空
 * */
static inline int skb_queue_empty(const struct sk_buff_head* list) {
    return skb_queue_len(list) < 1;
}

/*!
 * \brief 从链表中取出一个节点对应的sk_buff结构体， 但不从链表中删除该节点
 * */
static inline struct sk_buff* skb_peek(struct sk_buff_head* list) {
    if (skb_queue_empty(list)) {
        return NULL;
    }
    return list_first_entry(&list->head, struct sk_buff, list);
}

/*!
 * \brief 删除并释放所有链表中挂载的sk_buff结构体
 * \details
 *      1. 从链表中取出头节点
 *      2. 从链表中移除头节点
 *      3. free取出的节点
 * */
static inline void skb_queue_free(struct sk_buff_head* list) {
    struct sk_buff* skb = NULL;
    while ((skb = skb_peek(list)) != NULL) {
        skb_dequeue(list);  /** 这里实际也取出了头结点 */
        skb->refcnt--;      /** FIXME:  作用是什么？ alloc节点的时候，给赋值为0 */
        free_skb(skb);
    }
}

#endif //MYTCPSTACK_SKBUFF_H
