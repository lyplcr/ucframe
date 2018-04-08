/* Copyright (c) 2018 pace ÍõÔª
 * 20180101
 * power
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POWER_H
#define __POWER_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
} power_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PowerConfig(void);

#endif