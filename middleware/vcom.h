/* Copyright (c) 2018 王元
 * 20180101
 * 虚拟总线接口
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VBI_H
#define __VBI_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/

//typedef struct
//{
//  void bustype;
//  void datatype;
//  void *data;
//  uint32_t lenth;
//} interface_t;

typedef enum
{
  USBIN, USBOUT, USARTTX, USARTRX, SPIREAD, SPIWRITE
} interface_t;


/* circular queue */

typedef struct
{
  interface_t bustype;
  uint8_t size;
  uint8_t *data;
  uint8_t checkcode;
} circularqueue_t;      // fifo_t?
//extern circularqueue_t *circularqueue;

/* COMMON */
typedef struct
{
  uint8_t indata[64];
  uint8_t outdata[64];
  uint8_t *pbuf;
//  void (*CommonInit)(void);
//  void (*CommonDeInit)(void);
  void (*printf)(void);
  void (*TxData)(int8_t *pdata, uint16_t size);
  void (*RxData)(int8_t *pdata, uint16_t size);
} common_t;

/* IC proc */
typedef struct
{
  uint8_t cmd[2];
  uint8_t cmdsize;
  uint8_t addrsize; 
  uint8_t addr[4];
  uint8_t reg[4];
  uint16_t readsize;
  uint16_t writesize;
  uint8_t *data;
  void (*read)(void *pointhandle, ...);
  void (*write)(void *pointhandle, ...);
} cmdparam_t;   // 看能不能做成通用标准芯片读写结构
/* interface */
typedef struct
{
  uint8_t sfd;          // 帧开始符 #define 固定 0xA5
  uint8_t devid;        // 一般就一个只用0x01、0x00主机、0xff广播地址
  uint16_t length;      // 要不要拆分一个flag在前面？重发次数，
  uint8_t cmd;          // 指令
  uint8_t cmdplusl;     // 扩展指令
  uint8_t cmdplush;     // 扩展指令
  uint8_t checkcode;    // 用什么校验码好点
  uint8_t *pdata;       //
//  uint16_t eop;         // 0x0d 0x0a（即回车换行
} cmdpackets_t;         //comprotocol_t; datacom

typedef struct
{
  uint8_t cmd;
  uint8_t param;
  uint16_t checkcode;
  uint8_t data[64];
  void (*CheckPackets)(void);
  void (*PacketsParse)(void);
  void (*Handshake)(void);      // 握手指令
} vbi_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

