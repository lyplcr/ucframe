/**
 * @file  cs8900if.c
 * @brief Ethernet network driver for CS8900A
 */

#include "cs8900if.h"
#include "netif/etharp.h"
#include <stdbool.h>
#include <stdint.h>

/* Define these to match your hardware setup */
#define MEM_BASE 0x64000000

#define RXTXREG  *((volatile u16_t *)(MEM_BASE))
#define TXCMD    *((volatile u16_t *)(MEM_BASE + 0x04))
#define TXLENGTH *((volatile u16_t *)(MEM_BASE + 0x06))
#define ISQ      *((volatile u16_t *)(MEM_BASE + 0x08))
#define PACKETPP *((volatile u16_t *)(MEM_BASE + 0x0A))
#define PPDATA   *((volatile u16_t *)(MEM_BASE + 0x0C))

/* CS8900 PacketPage register offsets */
#define  CS_PP_INTNUM      0x0022       /* Interrupt number (0,1,2, or 3) */
#define  CS_PP_RXCFG       0x0102       /* Receiver Configuration         */
#define  CS_PP_RXCTL       0x0104       /* Receiver Control               */
#define  CS_PP_LINECTL     0x0112       /* Line Control Register offset   */
#define  CS_PP_BUSCTL      0x0116       /* Bus Control                    */
#define  CS_PP_LINESTATUS  0x0134       /* Line Status                    */
#define  CS_PP_SELFTEST    0x0136       /* Self Status                    */
#define  CS_PP_BUSSTATUS   0x0138       /* Bus Status                     */
#define  CS_PP_IA1         0x0158       /* Individual Address (IA)        */
#define  CS_PP_IA2         0x015A       /* Individual Address (IA)        */
#define  CS_PP_IA3         0x015C       /* Individual Address (IA)        */

/**
 * Number of attempts to try when sending a packet.
 * Must be big enough to last while previous packet is being sent,
 * yet small enough to not freeze the program when transmission is impossible.
 */
#define CS8900_TXTRIES    100000
/** Size of FIFO for incoming data, in 16-bit words */
#define FIFO_WORDS        2048

static struct netif *mynetif;
static uint16_t fifo[FIFO_WORDS];
static uint16_t head, tail;
static bool act = false;

/**
 * Transfer data from CS8900A into rx FIFO
 */
static void
pull_data(int_fast16_t len)
{
        uint16_t* ptr;
        /* Write length of packet as first word */
        fifo[head & (FIFO_WORDS - 1)] = len;
        head++;
        /* Loop unrolling optimization */
        ptr = &fifo[head & (FIFO_WORDS - 1)];
        while (len > 14)
        {       /* Got at least 8 words of data to write */
                if ((head & (FIFO_WORDS - 1)) < (FIFO_WORDS - 8))
                {       /* Got at leat 8 words in a row in FIFO */
                        *ptr++ = RXTXREG; *ptr++ = RXTXREG;
                        *ptr++ = RXTXREG; *ptr++ = RXTXREG;
                        *ptr++ = RXTXREG; *ptr++ = RXTXREG;
                        *ptr++ = RXTXREG; *ptr++ = RXTXREG;
                        len -= 16;
                        head += 8;
                }
                else
                {
                        /* Roll over FIFO boundary */
                        while ((head & (FIFO_WORDS - 1)) != 0)
                        {
                                fifo[head++ & (FIFO_WORDS - 1)] = RXTXREG;
                                len -= 2;
                        }
                        ptr = fifo;
                }
        }
        /* Write the rest word-by-word */
        while (len > 0)
        {
                fifo[head++ & (FIFO_WORDS - 1)] = RXTXREG;
                len -= 2;
        }
}

/**
 * CS8900A interrupt handler, pulls incoming data from chip into FIFO
 */
static void
irq_handler(void)
{
        while (ISQ != 0)
        {
                /* (ISQ & 0x3F) will always be 4 here (RX event) */
                int16_t len;
                /* Discard first word: status */
                len = RXTXREG;
                len = RXTXREG;
                if ((head - tail) < (FIFO_WORDS - 1 - ((len + 1) / 2)))
                {       /* Got space for packet in FIFO */
                        pull_data(len);
                }
                else
                {
                        /* Drop packet */
                        PACKETPP = CS_PP_RXCFG;
                        PPDATA = (0x0003U | 0x0100U/*RxOKiE*/ | 0x0040U/*Skip_1*/);
                }
        }
}

/**
 * Chip initialization
 *
 * @return Always ERR_OK
 */
static err_t
cs8900_init()
{
        /*
         * Initialize MCU external bus...
         */

        /* Dummy read to switch to 16-bit mode */
        (void)PPDATA;
        // { after full initialization of the cs8900a
        //   the INITD bit will be set }
        PACKETPP = CS_PP_SELFTEST;
        while ((PPDATA & 0x0080U) == 0);
        // { INITD bit is set }
        /* Set MAC address */
        PACKETPP = CS_PP_IA1;
        PPDATA = (u16_t)(mynetif->hwaddr[0]) | (u16_t)(mynetif->hwaddr[1] << 8);
        PACKETPP = CS_PP_IA2;
        PPDATA = (u16_t)(mynetif->hwaddr[2]) | (u16_t)(mynetif->hwaddr[3] << 8);
        PACKETPP = CS_PP_IA3;
        PPDATA = (u16_t)(mynetif->hwaddr[4]) | (u16_t)(mynetif->hwaddr[5] << 8);
        /* accept valid unicast or broadcast frames */
        PACKETPP = CS_PP_RXCTL;
        PPDATA = (0x0005U | 0x0800U/*broadcast*/
                          | 0x0400U/*individual*/
                          | 0x0100U/*RxOK*/);
        /* enable receive interrupt */
        PACKETPP = CS_PP_RXCFG;
        PPDATA = (0x0003U | 0x0100U/*RXIRQ*/);
        /* use interrupt number 0 */
        PACKETPP = CS_PP_INTNUM;
        PPDATA = (0x0000U);
        /* enable interrupt generation */
        PACKETPP = CS_PP_BUSCTL;
        PPDATA = (0x0017U | 0x8000U/*EnableIRQ*/);
        /* enable receiver, transmitter */
        PACKETPP = CS_PP_LINECTL;
        PPDATA = (0x0013U | 0x0080U/*SerTxOn*/ | 0x0040U/*SerRxOn*/);

        /*
         * Set up external interrupt for CS8900A with irq_handler() as ISR...
         */

        return ERR_OK;
}

/**
 * Push data to chip. Splice chunks with odd number of bytes properly.
 */
static void
push_data(void* src, uint_fast16_t len)
{
        /*
         * Variable word is used to splice chunks with odd number of bytes.
         * word == 0xFF00: even number of bytes in previous chunk
         * (word & 0xFF00) == 0: odd number of bytes in previous chunk,
         *                       last byte of that chunk is in variable word
         */
        static uint16_t word = 0xFF00;
        /* Using RealView feature: unaligned pointer */
        __packed uint16_t* ptr;

        if ((word & 0xFF00) == 0)
        {
                word |= *(uint8_t*)src << 8;
                RXTXREG = word;
                src = (void*)(1 + (uintptr_t)src);
                len--;
                word = 0xFF00;
        }
        for (ptr = src; len >= 2; len -= 2)
        {
                RXTXREG = *ptr;
                ptr++;
        }
        if (len > 0)
        {
                word = *(uint8_t*)ptr;
        }
}

/**
 *
 *
 * @return error code
 * - ERR_OK: packet transferred to hardware
 * - ERR_CONN: no link or link failure
 * - ERR_IF: could not transfer to link (hardware buffer full?)
 */
static err_t
cs8900_output(struct netif *netif, struct pbuf *p)
{
        u16_t tries = 0;
        err_t result;

        // exit if link has failed
        PACKETPP = CS_PP_LINESTATUS;
        if ((PPDATA & 0x0080U/*LinkOK*/) == 0)
        {
                return ERR_CONN; // no Ethernet link
        }

        result = ERR_OK;
        /* TODO: should this occur AFTER setting TXLENGTH??? */
        /* drop the padding word */
        /* issue 'transmit' command to CS8900 */
        TXCMD = 0x00C9U;
        /* send length (in bytes) of packet to send, but at least minimum frame length */
        TXLENGTH = p->tot_len;

        PACKETPP = CS_PP_BUSSTATUS;
        // not ready for transmission and still within 100 retries?
        while (((PPDATA & 0x0100U/*Rdy4TxNOW*/) == 0) &&
               (tries++ < CS8900_TXTRIES))
        {
                /* Wait */
        }
        // ready to transmit?
        if ((PPDATA & 0x0100U/*Rdy4TxNOW*/) != 0)
        {
                /* q traverses through linked list of pbuf's
                 * This list MUST consist of a single packet ONLY */
                struct pbuf *q;
                for (q = p; q != 0; q = q->next)
                {
                        push_data(q->payload, q->len);
                }
                if ((p->tot_len & 1) != 0)
                {
                        push_data("", 1);
                }
                /* { the packet has been sent } */
        }
        else
        {
                // { not ready to transmit!? }
                result = ERR_IF;
        }
        act = true;
        return result;
}

/**
 * Move a received packet from the cs8900 into a new pbuf.
 */
static struct pbuf*
cs8900_input(void)
{
        if (head != tail)
        {       /* Got packet in FIFO */
                struct pbuf* p;
                uint16_t len;

                len = fifo[tail & (FIFO_WORDS - 1)];
                tail++;
                p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
                if (p != 0)
                {
                        struct pbuf* q;
                        for (q = p; q != 0; q = q->next)
                        {
                                uint16_t* ptr;
                                uint16_t i;

                                ptr = q->payload;
                                i = (q->len + 1) / 2;
                                while (i > 0)
                                {
                                        *ptr = fifo[tail & (FIFO_WORDS - 1)];
                                        tail++;
                                        ptr++;
                                        i--;
                                }
                        }
                }
                else
                {
                        /* Could not allocate buffer for packet, discard it */
                        tail += (len + 1) / 2;
                }
                return p;
        }
        else
        {
                return 0;
        }
}

/**
 * Read a received packet from the CS8900.
 *
 * This function should be called when a packet is received by the CS8900
 * and is fully available to read. It moves the received packet to a pbuf
 * which is forwarded to the IP network layer or ARP module. It transmits
 * a resulting ARP reply or queued packet.
 *
 * @param netif The lwIP network interface to read from.
 *
 * @internal Uses cs8900_input() to move the packet from the CS8900 to a
 * newly allocated pbuf.
 *
 */
static void
cs8900if_input(void)
{
        struct eth_hdr *ethhdr = NULL;
        struct pbuf *p = NULL;

        /* move received packet into a new pbuf */
        p = cs8900_input();
        /* no packet could be read */
        if (p == NULL)
        {
                /* silently ignore this */
                return;
        }
        /* points to packet payload, which starts with an Ethernet header */
        ethhdr = p->payload;

        switch (htons(ethhdr->type)) {
        /* IP packet? */
        case ETHTYPE_IP:
                /* CSi disabled ARP table update on ingress IP packets.
                   This seems to work but needs thorough testing. */
                /* update ARP table */
                etharp_ip_input(mynetif, p);
                /* skip Ethernet header */
                pbuf_header(p, -(s16_t)sizeof(struct eth_hdr));
                /* pass to network layer */
                mynetif->input(p, mynetif);
                break;
        /* ARP packet? */
        case ETHTYPE_ARP:
                /* pass p to ARP module */
                etharp_arp_input(mynetif, (struct eth_addr *)&mynetif->hwaddr, p);
                break;
        /* unsupported Ethernet packet type */
        default:
                /* free pbuf */
                pbuf_free(p);
                p = NULL;
                break;
        }
}

/**
 * Service the CS8900.
 *
 * Can be called in a polling manner, or only after the CS8900 has raised
 * an interrupt request.
 */
void
cs8900if_poll(void)
{
        // see if link is up
        PACKETPP = CS_PP_LINESTATUS;
        if ((PPDATA & 0x0080U/*LinkOK*/) != 0)
        {
                if (netif_is_link_up(mynetif) == 0)
                {
                        netif_set_link_up(mynetif);
                }
        }
        else if (netif_is_link_up(mynetif) != 0)
        {
                netif_set_link_down(mynetif);
        }
        cs8900if_input();
}

/**
 * Initialize the CS8900 Ethernet MAC/PHY and its device driver.
 *
 * @param netif The lwIP network interface data structure belonging to this device.
 * MAY be NULL as we do not support multiple devices yet.
 */
err_t
cs8900if_init(struct netif *netif)
{
        mynetif = netif;
        /* administrative details */
        mynetif->name[0] = 'e';
        mynetif->name[1] = 'n';
        /* downward functions */
        mynetif->output = etharp_output;
        mynetif->linkoutput = cs8900_output;
        /* maximum transfer unit */
        mynetif->mtu = 1500;
        /* broadcast capability */
        mynetif->flags = NETIF_FLAG_BROADCAST;
        /* hardware address length */
        mynetif->hwaddr_len = 6;
        /*
         * Initialize device MAC address:
         * memcpy(mynetif->hwaddr, my_mac_address, 6);
         */
        /* intialize the cs8900a chip */
        return cs8900_init();
}

/**
 * See if a link is established (cable plugged)
 *
 * @return true if linked, false otherwise
 */
bool
cs8900if_link(void)
{
        return (netif_is_link_up(mynetif)) == 0 ? false : true;
}

/**
 * See if there has been activity since last call to this function.
 * Activitity is sending packets.
 *
 * @return true if linked, false otherwise
 */
bool
cs8900if_act(void)
{
        bool ret;
        ret = act;
        act = false;
        return ret;
}