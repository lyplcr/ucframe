/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * LEDÀà
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"


/* Exported define -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
osThreadId LEDThreadHandle;

void LEDThread(void const *argument)
{
  while (1)
  {
    HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
    osDelay(1000);
  }
  
//  osThreadResume(LEDThreadHandle);
//  osThreadSuspend(NULL);
}

void LEDConfig(void)
{
  osThreadDef(LED, LEDThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  LEDThreadHandle = osThreadCreate(osThread(LED), NULL);
}