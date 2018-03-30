/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * BUTTONÀà
 */

/* Includes ------------------------------------------------------------------*/
#include "button.h"

/* Exported define -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int8_t GetBottomState(void)
{
  return 0;
}

void ButtonThread(void const *argument)
{
//  while (1)
//  {
//    if (HAL_GPIO_ReadPin(BOTTOM_PORT, BOTTOM_PIN) == GPIO_PIN_SET)
//    {
//      rotarynum = 0;
//    }
//    if (HAL_GPIO_ReadPin(BOTTOM_Port, BOTTOM_Pin) == GPIO_PIN_RESET)
//    {
//      rotarynum = 0;
//    } 
//    osDelay(100);
//  }
}

void ButtonConfig(void)
{
  
}
#if 0
uint8_t KeyCallBack(void)
{
	
}
void KeyProc(void)
{
	key.stabletimecnt++;
	switch (key.state)
	{
		case KEYUP:
		if (key.KeyCallBack() == 1)
		{
			key.state = KEYDOWNWOBBLE;
			key.stabletimecnt = 0;
		}
		break;
		case KEYDOWNWOBBLE:
		if (key.KeyCallBack() == 0)
		{
			key.state = KEYUP;
		}
		if (key.stabletimecnt > 20)
		{
			key.state = KEYDOWN;
			key.stabletimecnt = 0;
		}
		break;
		case KEYDOWN:
		if (key.KeyCallBack() == 0)
		{
			key.state = KEYUPWOBBLE;
		}
		if (key.stabletimecnt > 1000)
		{
			key.state = KEYLONGDOWN;
		}
		break;
		case KEYLONGDOWN:
		if (key.KeyCallBack() == 0)
		{
			key.state = KEYUPWOBBLE;
		}
		break;
		case KEYUPWOBBLE:
		if (key.KeyCallBack() == 1)
		{
			key.state = KEYDOWN;
		}
		if (key.stabletimecnt > 20)
		{
			key.state = KEYUP;
		}
		break;
		case DOUBLECLKICKWOBBLE:
		break;
		case DOUBLECLKICK:
		break;
	}
}
void KeyInit(void)
{
	key.state = KEYUP;
	key.stabletimcnt = 0;
	key.KeyCallBack = KeyCallBack;
	key.KeyProc = KeyProc;
}
#endif