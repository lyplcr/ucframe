/* Copyright (c) 2018 pace ÍõÔª
 * 20180101
 * camera
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAMERA_H
#define __CAMERA_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
} camera_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CameraConfig(void);

#endif