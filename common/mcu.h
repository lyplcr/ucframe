/* Copyright (c) 2018 王元
 * 20180101
 * LED
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCU_H
#define __MCU_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  char company[8];
  uint32_t chipid;
  uint32_t clock;
  uint32_t ramsize;
  uint32_t romsize;
  uint32_t appaddr;
  void (*CloseISR);	// 这两个用宏定义表示好点
  void (*TaskSwitch);
  void (*OpenISR);
#if 0
  uint32_t externram;
  uint32_t externrom;
  uint32_t externflash;
#endif
} mcu_t;

typedef struct
{
  uint8_t *configreg;
  uint8_t *controlreg;
  uint8_t *statusreg;
  uint8_t *datareg;
  uint8_t *inbuf;
  uint8_t *outbuf;
} register_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

