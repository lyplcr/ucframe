/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * LED
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"


/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
  void (*CreatLed)(void);
  void (*LedOn)(void);
  void (*LedOff)(void);
  void (*LedFlow)(uint16_t on, uint16_t off);
} led_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LEDConfig(void);

#endif