/**
 * @file  cs8900if.h
 * @brief Ethernet network driver for CS8900A
 */

#ifndef CS8900IF_H
#define CS8900IF_H

#include "lwip/netif.h"
#include <stdbool.h>

extern err_t cs8900if_init(struct netif *);
extern void  cs8900if_poll(void);
extern bool  cs8900if_link(void);
extern bool  cs8900if_act(void);

#endif /* CS8900IF_H */

