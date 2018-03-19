/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * BOTTOMÀà
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOTTOM_H
#define __BOTTOM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*config)(void);
} bottom_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void BottomConfig(void);

#endif