/* Copyright (c) 2018 王元
 * 20180101
 * LED
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEMORY_H
#define __MEMORY_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/



typedef struct
{
  uint32_t stackadd;
  uint32_t atacksize;
  uint32_t stackpagesize;
  uint32_t bootadd;
  uint32_t appadd;
  uint32_t paramadd;
} address_t;

typedef struct
{
  uint8_t *pdata;
  uint8_t datatype;	// 数据类型怎么表示？	
  uint32_t datasize;
  void (*procfuction)(void);
  uint8_t *pre;
} data_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

