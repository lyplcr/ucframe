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


typedef struct
{
  uint8_t *data;
} vbi_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

