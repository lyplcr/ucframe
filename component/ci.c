/* Copyright (c) 2018 pace 王元
 * 20180101
 * 通信接口
 */

/* Includes ------------------------------------------------------------------*/
#include "ci.h"
#include "main.h"
#include "stm32f0xx_hal.h"

/* Exported define -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
osThreadId CIThreadHandle;

void CIThread(void const *argument)
{
  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(1000);
  }
  
//  osThreadResume(LEDThreadHandle);
//  osThreadSuspend(NULL);
}

void CIConfig(void)
{
  osThreadDef(CI, CIThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  CIThreadHandle = osThreadCreate(osThread(CI), NULL);
}
