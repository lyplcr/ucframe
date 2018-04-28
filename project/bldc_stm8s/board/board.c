/**********************************************************
*name   : main.c
*detail : 入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
#if 0
//#define DATA_ROM _Pragma("location=\".rom_data\"") 
//DATA_ROM const PRODUCTINFO productinfo =
//const PRODUCTINFO productinfo @".MYSEG1" = 同上两种放在固定地址的办法
const mcu_t mcu =
{
  {'S','T','M','3','2','F','1','0'},
  0x12345678,
  72000000
};
#else
mcu_t mcu;
#endif

/*  functions ----------------------------------------------------------------*/
// 
void CLKInit(void)
{
  CLK_DeInit();
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

// 
void GPIOInit(void)
{
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_RISE_FALL);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
//  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);// 最高级别中断?

  GPIO_Init(GPIOA, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOE, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(GPIOF, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
}

//
void TimerInit(void)
{
  
}

//
void BoardInit(void)
{
  GPIOInit();
  TimerInit();
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/