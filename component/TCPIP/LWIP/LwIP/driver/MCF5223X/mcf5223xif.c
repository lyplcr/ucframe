/**
 * @file  mcf5223xif.c
 * @brief Ethernet driver for MCF5223x
 *
 * Implements zero-copy receive, and a separate send buffer, no tx queue.
 * MEM_ALIGNMENT must be a multiple of 16 (needed for DMA)
 */

#include <stdint.h>
#include "mcf5223xif.h"
#include "netif/etharp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"

#if (MEM_ALIGNMENT & 15) != 0
#error MEM_ALIGNMENT must be a multiple of 16
#endif

#define SYS_CLOCK       60000000ul
#define IPSBASE         0x40000000

#define MCF_REG8(offset)  (*(uint8_t  volatile*)(IPSBASE+(offset)))
#define MCF_REG32(offset) (*(uint32_t volatile*)(IPSBASE+(offset)))

/* FEC registers */
#define FEC_EIR         MCF_REG32(0x1004)
#define FEC_RDAR        MCF_REG32(0x1010)
#define FEC_TDAR        MCF_REG32(0x1014)
#define FEC_ECR         MCF_REG32(0x1024)
#define FEC_MMFR        MCF_REG32(0x1040)
#define FEC_MSCR        MCF_REG32(0x1044)
#define FEC_RCR         MCF_REG32(0x1084)
#define FEC_PALR        MCF_REG32(0x10E4)
#define FEC_PAUR        MCF_REG32(0x10E8)
#define FEC_IAUR        MCF_REG32(0x1118)
#define FEC_IALR        MCF_REG32(0x111C)
#define FEC_GAUR        MCF_REG32(0x1120)
#define FEC_GALR        MCF_REG32(0x1124)
#define FEC_ERDSR       MCF_REG32(0x1180)
#define FEC_ETDSR       MCF_REG32(0x1184)
#define FEC_EMRBR       MCF_REG32(0x1188)

/* EPHY registers */
#define PHY_EPHYCTL0    MCF_REG8(0x1E0000)
#define PHY_EPHYCTL1    MCF_REG8(0x1E0001)

/* FEC register fields */
#define MMFR_ST         (1 << 30)
#define MMFR_OP_WR      (1 << 28)
#define MMFR_OP_RD      (2 << 28)
#define MMFR_TA         (2 << 16)
#define MMFR_RA_CONTROL (0 << 18)
#define MMFR_RA_STATUS  (1 << 18)

/* EPHY MII control register bits */
#define EPHY_DATARATE   (1 << 13)
#define EPHY_DPLX       (1 << 8)

/* EPHY MII status register bits */
#define EPHY_LNKSTST    (1 << 2)

#define EIR_MII         (1 << 23)
#define EIR_TXF         (1 << 27)
#define RCR_MII_MODE    (1 << 2)
#define ECR_ETHER_EN    (1 << 1)

/* EPHY register fields */
#define EPHYCTL0_EPHYEN (1u << 7)
#define EPHYCTL0_LEDEN  (1 << 3)
#define EPHYCTL0_DIS100 (1 << 5)
#define EPHYCTL0_DIS10  (1 << 4)

/* Tx BD fields */
#define TXBD_R          (1 << 15)
#define TXBD_W          (1 << 13)
#define TXBD_L          (1 << 11)
#define TXBD_TC         (1 << 10)

/* Rx BD fields */
#define RXBD_E          (1 << 15)
#define RXBD_RO1        (1 << 14)
#define RXBD_W          (1 << 13)
#define RXBD_L          (1 << 11)
#define RXBD_LG         (1 << 5)
#define RXBD_NO         (1 << 4)
#define RXBD_CR         (1 << 2)
#define RXBD_OV         (1 << 1)
#define RXBD_TR         (1 << 0)

#define MSCR_MII_SPEED  (((SYS_CLOCK-1)/5000000+1)<<1)
#define MAX_FRAME_LEN   1518

/**
 * Rx buffer descriptor ring size. Each buffer is PBUF_POOL_BUFSIZE bytes.
 * The number of buffers available for allocation is PBUF_POOL_SIZE.
 * RX_RING_SIZE is how many buffers the driver tries to allocate
 * for reception. Adjust this to fit your needs.
 */
#define RX_RING_SIZE    20
/**
 * This must be 2. It could be 1 if there was not a need to
 * overcome a hardware limitation (see chip errata).
 */
#define TX_RING_SIZE    2

/* Tx packet buffer aligned to 16-byte boundary */
#define TX_BUF_PTR      ((u8_t*)((u32_t)&txbuf[15] & ~15))

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/**
 * EPHY turn-on delay. Assuming here 1 CPU cycle per delay loop cycle.
 * Actual delay time will be several times longer, but still
 * short enough to not be noticeable.
 * At least 360 us is required according to datasheet.
 */
#define PHY_DELAY       ((uint32_t)(360e-6 * SYS_CLOCK))

/* Obtain pointer to pbuf from pointer to payload */
#define PAYLOAD2PBUF(p) \
        (struct pbuf*)((u8_t*)(p) - LWIP_MEM_ALIGN_SIZE(sizeof(struct pbuf)))

struct txrx_desc {
        u16_t ctl;
        u16_t len;
        void* ptr;
};

static struct txrx_desc rxbd_ring[RX_RING_SIZE];
/** Index of first Rx buffer descriptor (BD) to receive packet data */
static u8_t rxbd_index = 0;
/** Number of initialized Rx buffer descriptors */
static u8_t rxbd_inuse = 0;

static struct txrx_desc txbd_ring[TX_RING_SIZE];
/* Points to the first free Tx BD, can be either 0 or 1 */
static u32_t txbd_index = 0;
/* This is Tx packet buffer, allow for alignment (16) */
static u8_t txbuf[MAX_FRAME_LEN + 15];

static struct netif *mynetif;

static bool act = false;

/**
 * This function does the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 *       ... And we do wait for the previous transmission to complete.
 */
        static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
        struct pbuf *q;
        u8_t *ptr;
        u16_t control;

        /* Suppress 'argument not used' warning */
        netif = netif;

        if (p->tot_len > MAX_FRAME_LEN)
                /* Frame too long, drop it */
                return ERR_MEM;

        /* Wait for previous transmission to complete */
        while (FEC_TDAR != 0) { }

        txbd_ring[txbd_index].len = p->tot_len;
        control = TXBD_R | TXBD_L | TXBD_TC;

        /* Walk the pbuf chain, fill the Tx packet buffer */
        ptr = TX_BUF_PTR;
        q = p;
        while (q != NULL) {
                memcpy(ptr, q->payload, q->len);
                ptr += q->len;
                q = q->next;
        }

        /* Set up Tx BD */
        if (txbd_index == (TX_RING_SIZE - 1)) {
                control |= TXBD_W;
                txbd_ring[txbd_index].ctl = control;
                txbd_index = 0;
        } else {
                txbd_ring[txbd_index].ctl = control;
                txbd_index++;
        }
        txbd_ring[txbd_index].ctl = 0;

        /* Start transmission */
        FEC_TDAR = 0;
        act = true;
        return ERR_OK;
}

/**
 * Initialize the Rx buffer descriptor ring by allocating buffers
 * and assigning them to descriptors
 */
        static void
rx_setup(void)
{
        struct pbuf *p;
        u8_t i;

        /* All buffer descriptors initialized? Then nothing to do. */
        if (rxbd_inuse == RX_RING_SIZE)
                return;

        /* Index of first uninitialized Rx buffer descriptor */
        i = (u8_t)((rxbd_index + rxbd_inuse) % RX_RING_SIZE);

        do {
                /* Allocate a single element from the PBUF_POOL mempool */
                p = pbuf_alloc(PBUF_RAW, PBUF_POOL_BUFSIZE, PBUF_POOL);
                if (p == NULL) {
                        /* In case of buffer allocation failure, mark the descriptor as such */
                        rxbd_ring[i].ctl = RXBD_RO1;
                        break;
                }
                rxbd_ring[i].ptr = p->payload;
                if (i == (RX_RING_SIZE - 1)) {
                        rxbd_ring[i].ctl = RXBD_E | RXBD_W;
                        i = 0;
                } else {
                        rxbd_ring[i].ctl = RXBD_E;
                        i++;
                }
                rxbd_inuse++;
        } while (rxbd_inuse < RX_RING_SIZE);
        /* Start reception, if it's not started already */
        FEC_RDAR = 0;
}

/**
 * Discard frame in case of reception error by deallocating buffers
 *
 * @param first Index of first buffer descriptor to discard
 * @param last Index of last buffer descriptor to discard
 */
        static void
discard_frame(u8_t first, u8_t last)
{
        u8_t i, done = 0;

        i = first;
        do {
                if (i == last)
                        done = 1;
                memp_free(MEMP_PBUF_POOL, PAYLOAD2PBUF(rxbd_ring[i].ptr));
                i = (i + 1) % RX_RING_SIZE;
        } while (done == 0);
        /* Keep index in sync with Rx DMA */
        rxbd_index = (last + 1) % RX_RING_SIZE;
}

/**
 * Collect frame by chaining the corresponding pbufs
 *
 * @param first Index of first buffer descriptor to collect
 * @param last Index of last buffer descriptor to collect
 * @param lastlen Length of last buffer in chain
 */
        static struct pbuf*
collect_frame(u8_t first, u8_t last, u16_t lastlen)
{
        u8_t i, prev;
        struct pbuf *head, *tail;

        tail = PAYLOAD2PBUF(rxbd_ring[last].ptr);
        /* Trim last buffer, so that complete frame length is correct */
        pbuf_realloc(tail, lastlen);
        /* Walk the buffers from last to first */
        for (i = last; i != first; i = prev) {
                prev = (u8_t)((i + RX_RING_SIZE - 1) % RX_RING_SIZE);
                head = PAYLOAD2PBUF(rxbd_ring[prev].ptr);
                /* Grow the chain */
                pbuf_cat(head, tail);
                tail = head;
        }
        /* Keep index in sync with Rx DMA */
        rxbd_index = (last + 1) % RX_RING_SIZE;
        return tail;
}

/**
 * Zero-copy reception. Collect DMA'ed data and return frame as pbuf chain.
 *
 * @return a pbuf filled with the received packet (including MAC header),
 *         NULL if no received frames
 */
        static struct pbuf*
low_level_input(void)
{
        u8_t  i, n;
        u16_t len;

        /* No initialized Rx buffer descriptors? Then quit. */
        if (rxbd_inuse == 0)
                return NULL;

        i = rxbd_index;
        len = 0;
        n = 0;
        /* Scan the Rx buffer rescriptor ring */
        for (;;) {
                if ((rxbd_ring[i].ctl & RXBD_RO1) != 0)
                        /* Descriptor uninitialized due to buffer allocation failure, quit */
                        return NULL;
                if ((rxbd_ring[i].ctl & RXBD_E) != 0)
                        /* Buffer empty, quit */
                        return NULL;
                /* Buffer contains frame data, continue */
                n++;
                if ((rxbd_ring[i].ctl & RXBD_L) != 0) {
                        /* Last buffer in frame, finalize */
                        break;
                }
                len += rxbd_ring[i].len;
                i = (u8_t)((i + 1) % RX_RING_SIZE);
                /* Move on to next buffer in frame */
        }
        /* Mark processed descriptors as uninitialized */
        rxbd_inuse -= n;
        if ((rxbd_ring[i].ctl & (RXBD_LG|RXBD_NO|RXBD_CR|RXBD_OV|RXBD_TR)) != 0) {
                /* Reception error */
                discard_frame(rxbd_index, i);
                return NULL;
        }
        return collect_frame(rxbd_index, i, (u16_t)(rxbd_ring[i].len - len));
}

/**
 * Initialize the on-chip EPHY
 */
        static void
phy_init(void)
{
        u32_t i;

        /* Configure EMDC clock, frequency = 2.50 MHz */
        FEC_MSCR = MSCR_MII_SPEED;

        PHY_EPHYCTL0 &= ~(EPHYCTL0_DIS10 | EPHYCTL0_DIS100);
        PHY_EPHYCTL0 |= EPHYCTL0_LEDEN;
        /* Enable EPHY */
        PHY_EPHYCTL0 |= EPHYCTL0_EPHYEN;

        /* Delay for startup time */
        for (i = PHY_DELAY; i != 0; i--) {
                /*
                 * Put something here to make sure
                 * the compiler doesn't optimize the loop away
                 */
        }

        /* Link speed = 100 Mbps, full-duplex */
        FEC_MMFR = MMFR_ST | MMFR_OP_WR | MMFR_TA | MMFR_RA_CONTROL |
                EPHY_DATARATE | EPHY_DPLX;
        /* Poll for MII Write Frame completion */
        while ((FEC_EIR & EIR_MII) == 0) { }
        /* Request status register read (link status polling) */
        FEC_MMFR = MMFR_ST | MMFR_OP_RD | MMFR_TA | MMFR_RA_STATUS;
}

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
        static void
low_level_init(struct netif *netif)
{
        /* set MAC hardware address length */
        netif->hwaddr_len = ETHARP_HWADDR_LEN;

        /*
         * Set MAC hardware address:
         * FEC_PALR = (u32_t)( (my_mac_address[0] << 24)
         *                   | (my_mac_address[1] << 16)
         *                   | (my_mac_address[2] << 8 )
         *                   | (my_mac_address[3] << 0 ) );
         * FEC_PAUR = (u32_t)( (my_mac_address[4] << 24)
         *                   | (my_mac_address[5] << 16) );
         * memcpy(netif->hwaddr, my_mac_address, ETHARP_HWADDR_LEN);
         */

        /* maximum transfer unit */
        netif->mtu = 1500;

        /* device capabilities */
        /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
        netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

        /* Do whatever else is needed to initialize interface. */  
        FEC_RCR = (MAX_FRAME_LEN << 16) | RCR_MII_MODE;
        FEC_GAUR = 0;
        FEC_GALR = 0;
        FEC_IAUR = 0;
        FEC_IALR = 0;
        FEC_ETDSR = (uint32_t)txbd_ring;
        FEC_ERDSR = (uint32_t)rxbd_ring;
        FEC_EMRBR = LWIP_MEM_ALIGN_SIZE(PBUF_POOL_BUFSIZE);
        FEC_ECR |= ECR_ETHER_EN;
        phy_init();
}

/**
 * Initialize Tx data buffer pointers in Tx buffer descriptors,
 * they all point to the same buffer
 */
        static void
init_txbdring(void)
{
        uint8_t i;
        for (i = 0; i < TX_RING_SIZE; i++) {
                txbd_ring[i].ptr = TX_BUF_PTR;
        }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error.
 *         We always return ERR_OK
 */
        err_t
mcf5223xif_init(struct netif *netif)
{
        mynetif = netif;
        netif->name[0] = IFNAME0;
        netif->name[1] = IFNAME1;
        /* We directly use etharp_output() here to save a function call.
         * You can instead declare your own function an call etharp_output()
         * from it if you have to do some checks before sending (e.g. if link
         * is available...) */
        netif->output = etharp_output;
        netif->linkoutput = low_level_output;

        /* initialize the hardware */
        low_level_init(netif);
        init_txbdring();
        rx_setup();

        return ERR_OK;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
        static void
mcf5223xif_input(void)
{
        struct eth_hdr *ethhdr;
        struct pbuf *p;

        /* move received packet into a new pbuf */
        p = low_level_input();
        /* no packet could be read, silently ignore this */
        if (p == NULL)
                return;
        /* points to packet payload, which starts with an Ethernet header */
        ethhdr = p->payload;

        switch (htons(ethhdr->type)) {
                /* IP or ARP packet? */
                case ETHTYPE_IP:
                        /* full packet send to tcpip_thread to process */
                        /* skip Ethernet header */
                        pbuf_header(p, -(s16_t)sizeof(struct eth_hdr));
                        if (mynetif->input(p, mynetif) != ERR_OK) {
                                pbuf_free(p);
                                p = NULL;
                        }
                        break;
                case ETHTYPE_ARP:
                        /* pass p to ARP module */
                        etharp_arp_input(mynetif, (struct eth_addr *)&mynetif->hwaddr, p);
                        break;
                default:
                        pbuf_free(p);
                        p = NULL;
                        break;
        }
}

/**
 * This function should be called from main loop.
 * It polls the interface for received frames and passes
 * them on to higher layers of the stack.
 */
        void
mcf5223xif_poll(void)
{
        /* Poll for MII Write Frame completion */
        while ((FEC_EIR & EIR_MII) == 0) { }
        /* Clear MII interrupt bit */
        FEC_EIR = EIR_MII;
        if ((FEC_MMFR & EPHY_LNKSTST) != 0) {
                if (netif_is_link_up(mynetif) == 0) {
                        netif_set_link_up(mynetif);
                }
        } else if (netif_is_link_up(mynetif) != 0) {
                netif_set_link_down(mynetif);
        }
        /* Request status register read (link status polling) */
        FEC_MMFR = MMFR_ST | MMFR_OP_RD | MMFR_TA | MMFR_RA_STATUS;

        mcf5223xif_input();
        rx_setup();
}

/**
 * See if a link is established (cable plugged)
 *
 * @return true if linked, false otherwise
 */
        bool
mcf5223xif_link(void)
{
        return netif_is_link_up(mynetif) == 0 ? false : true;
}

/**
 * See if there has been activity since last call to this function.
 * Activitity is sending packets.
 *
 * @return true if linked, false otherwise
 */
        bool
mcf5223xif_act(void)
{
        bool ret;
        ret = act;
        act = false;
        return ret;
}

