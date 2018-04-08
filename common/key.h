/* Copyright (c) 2017 pace 王元
 * 
 * fingerprint identification
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* KEY */
typedef enum
{
  KEYUP, KEYDOWNWOBBLE, KEYDOWN, KEYLONGDOWN, KEYUPWOBBLE, DOUBLECLKICKWOBBLE, DOUBLECLKICK, IDLESTATE
} keystate_t;

typedef struct
{
  keystate_t keystate;
  keystate_t laststate;         // 最后有效状态，过时清零IDLE，双击判断用
  keystate_t keycallbackflag;
  uint16_t stabletimecnt;	
//  void (*CreatKey)(void);
  uint8_t (*GetKey)(void);      // 获取按键状态，需要加入对应的IO状态判断
  void (*RefreshKey)(void);	// 放在1ms定时器
} key_t;
extern key_t key;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void CreatKey(void);
#endif