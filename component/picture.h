/* Copyright (c) 2018 pace ÍõÔª
 * 20180101
 * picture
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PICTURE_H
#define __PICTURE_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
} picture_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CIConfig(void);

#endif