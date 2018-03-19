/**
 * @file  mcf5223xif.h
 * @brief Ethernet driver for MCF5223x
 */

#ifndef FEC_H
#define FEC_H

#include "lwip/netif.h"
#include <stdbool.h>

extern err_t mcf5223xif_init(struct netif *netif);
extern void  mcf5223xif_poll(void);
extern bool  mcf5223xif_link(void);
extern bool  mcf5223xif_act(void);

#endif /* FEC_H */

