/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/


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
//  EXTI_CR1=0x83;
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_RISE_FALL);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
//  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);// 最高级别中断?
  //  GPIO_Init(GPIOA, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);        // 
  GPIOA->DDR = 0x00;
  GPIOA->CR1 = 0xff;
  
  GPIOB->DDR = 0xf0;
  GPIOB->CR1 = 0xf0;
  GPIOB->CR2 = 0x00;
  
  GPIOC->DDR = 0xff;
  GPIOC->CR1 = 0xff;
  GPIOC->CR2 = 0x00;
  
  GPIOD->DDR = 0x14;
  GPIOD->CR1 = 0x96;
  GPIOD->CR2 = 0x00;
  GPIOD->ODR = 0x00;
  
  GPIOE->DDR = 0xff;
  GPIOE->CR1 = 0xff;
  GPIOE->CR2 = 0x00;
  GPIOE->ODR = 0xf0;
  
  GPIOF->DDR = 0xff;
  GPIOF->CR1 = 0xff;
  GPIOF->CR2 = 0x00;
  GPIOF->ODR = 0x00;
}

//
void ADCInit(void)
{
  
}

//
void Timer1Init(void)
{
  TIM1->SR1 = 0x00;     // clear int flag
  TIM1->CR1 = 0x05;     
  TIM1->CR2 = 0x71;     
  TIM1->SMCR = 0x00;
  TIM1->PSCRH = 0;
  TIM1->PSCRL = 0;
  TIM1->ARRH = (uint8_t)(PWM_PERIOD>>8);
  TIM1->ARRL = (uint8_t)PWM_PERIOD;
  TIM1->IER = 0;        //0x80;// only brk int
  TIM1->CCMR1 = 0x60;
  TIM1->CCMR2 = 0x60;
  TIM1->CCMR3 = 0x60;
  TIM1->CCMR4 = 0x00;
  TIM1->CCER1 = 0x00;
  TIM1->CCER1 = 0x00;
  TIM1->OISR = 0x00;
  TIM1->DTR = 0X00;
#ifdef FUNC_HOC_PROTECT_EN      // 硬件死区保护
  TIM1->BKR |= 0x90;
#else
  TIM1->BKR |= 0x80;
#endif
  TIM1->EGR |= 0x01;
  TIM1->CR1 |= 0x01;
  
#if 0
/***********************************************************
Channel 1, 2,3 and 4 Configuration in PWM mode 
000：冻结。输出比较寄存器TIM1_CCR1与计数器TIM1_CNT间的比较?設C1REF不起作用；
001：匹配时设置通道1的输出为有效电平。当计数器TIM1_CNT的值?氩痘?比较寄存器1 (TIM1_CCR1)相同时，强制OC1REF为高。
010：匹配时设置通道1的输出为无效电平。当计数器TIM1_CNT的值?氩痘?比较寄存器1 (TIM1_CCR1)相同时，强制OC1REF为低。
011：翻转。当TIM1_CCR1=TIM1_CNT时，翻转OC1REF的电平。100：强制为无效电平。强制OC1REF为低。
101：强制为有效电平。强制OC1REF为高。
110：PWM模式1－ 在向上计数时，一旦TIM1_CNT<TIM1_CCR1时通道1?有效电平，否则为无效电平；在向下计数时，一旦TIM1_CNT>TIM1_CCR1时通道1为无效电平(OC1REF=0)，否则为有效电平(OC1REF=1)。
111：PWM模式2在向上计数时，一旦TIM1_CNT<TIM1_CCR1时通道1为无效电平，否则为有效电平；在向下计数时，一旦TIM1_CNT>TIM1_CCR1时通道1为有效电平，否则为无效电平。 
*************************************************************/
  // Clear Update Flag
  /*TIM1_IER_UIE=1;*/
  DisAllPwmOut();
  /*
  //default to 0% duty cycle
  ToCMPxH( TIM1->CCR1H, 0 );
  ToCMPxL( TIM1->CCR1L, 0 );
   */
#endif
}

//
void Timer5Init(void)
{
  TIM5->IER = 0x00;
  TIM5->EGR |= 1;       //  TIM5->EGR_UG=1; 
  TIM5->PSCR = 0x03;    //0xfc;// psc=64分频2的n次方  psr=7 2^7  8us  b`128
  TIM5->ARRH = 0x00;
  TIM5->ARRL = 0x01;
  TIM5->SR1 = 0x00;     // clear int flag
  TIM5->CR1 = 0x01;     //0x84;//URS 只有计数器溢出 产生中断。
  TIM5->CR2 = 0x00;
  TIM5->SMCR = 0x00;
  TIM5->IER = 0x01;     // only update event
}

//
void Timer6Init(void)
{
  TIM6->SR1 = 0x00;     // 状态标志位清零
  TIM6->SMCR = 0x00;    // 从模式 计数时钟来自TIM 更新事件
  TIM6->CR1 = 0x04;     // only ov event 
  TIM6->IER |= 0X01;    //  TIM6->IER_UIE=1;
  // TIM6->IER_TIE=1;   ////---------
  TIM6->PSCR = 0x07;    // 预分频寄存器
  TIM6->ARR = 0xff;
  TIM6->EGR |= 0x01;    // TIM6->EGR_UG=1;
  TIM6->CR1 |= 0x01;    // TIM6->CR1_CEN=1;
  TIM6->IER = 0x01;
}

void Timer5Start(uint16_t arr)
{
  TIM5->ARRH = (uint8_t)(arr<<8);
  TIM5->ARRL = (uint8_t)arr;
  TIM5->CR1 |= 0x01;
}
void Timer5Stop(void)
{
  TIM5->ARRH = 0;
  TIM5->ARRL = 0;
  TIM5->CR1 &= 0xfe;
}

//
void LedOn(void)
{
  GPIOB->ODR = 0xc0;
  GPIOE->ODR = 0x00;
}

//
void LedOff(void)
{
  GPIOB->ODR = 0x00;
}

//
void BoardInit(void)
{
  CLKInit();
  Gpio_interruput_Init();
  DisIRQ();     sim();
  Gpio_Init();
  GPIOB->ODR &= 0x3f;
  GPIOE->ODR &= 0xdf;
  GPIOF->ODR &= 0xef;
  PWM_INIT();
  TIM5_Conf();
  Tim6Init();
  TIM5_StartCount();
  EnIRQ();      rim();
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/