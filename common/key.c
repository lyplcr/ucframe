/* Copyright (c) 2017 pace 王元
 * 
 * fingerprint identification
 */

/* Includes ------------------------------------------------------------------*/
#include "key.h"
/* Exported define -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* KEY */
key_t key;

// 获取按键状态，需要加入对应的IO状态判断
uint8_t GetKey(void)
{
  return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

// 放在1ms定时器
void RefreshKey(void)
{
  key.stabletimecnt++;
  if (key.stabletimecnt > 1000)
  {
    key.laststate = IDLESTATE;
  }
  
  switch (key.keystate)
  {
  case KEYUP:
    if (key.GetKey() == 1)
    {
      key.keystate = KEYDOWNWOBBLE;
      key.stabletimecnt = 0;
    }
    break;
  case KEYDOWNWOBBLE:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUP;
    }
    if (key.stabletimecnt > 20)
    {
      key.keystate = KEYDOWN;
      key.keycallbackflag = KEYDOWN;
      key.stabletimecnt = 0;
    }
    break;
  case KEYDOWN:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUPWOBBLE;
    }
    if (key.stabletimecnt > 1000)
    {
      key.keystate = KEYLONGDOWN;
    }
    break;
  case KEYLONGDOWN:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUPWOBBLE;
    }
    break;
  case KEYUPWOBBLE:
    if (key.GetKey() == 1)
    {
      key.keystate = KEYDOWN;
    }
    if (key.stabletimecnt > 20)
    {
      key.keystate = KEYUP;
      key.stabletimecnt = 0;
      key.keycallbackflag = KEYUP;
    }
    break;
  case DOUBLECLKICKWOBBLE:
    break;
  case DOUBLECLKICK:
    break;
  }
}
// 创建注册按键
void CreatKey(void)
{
  key.keystate = KEYUP;
  key.laststate = IDLESTATE;
  key.stabletimecnt = 0;
  key.GetKey = GetKey;
  key.RefreshKey = RefreshKey;
}