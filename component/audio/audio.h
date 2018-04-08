/* Copyright (c) 2018 pace ÍõÔª
 * 20180101
 * audio
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_H
#define __AUDIO`_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
} audio_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LCDConfig(void);

#endif