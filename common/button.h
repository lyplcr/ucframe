/* Copyright (c) 2018 王元
 * 20180101
 * BUTTON类
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  KEYUP, KEYDOWNWOBBLE, KEYDOWN, KEYLONGDOWN, KEYUPWOBBLE, DOUBLECLKICKWOBBLE, DOUBLECLKICK
} keystate_t;

typedef struct
{
  keystate_t keystate;
  uint16_t stabletimecnt;
  uint16_t lasttimecnt;		// 最后有效状态时间，或者记down次数 up清零，双击判断用
  void (*CreatKey)(void);
  uint8_t (*GetKey)(void);		// 
  void (*RefreshKey)(void);	// 放在1ms定时器
} key_t;

typedef struct
{
  uint32_t delay;
  void (*config)(void);
} button_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ButtonConfig(void);

#endif