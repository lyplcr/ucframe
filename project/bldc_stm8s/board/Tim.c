
#include "platform.h"
//#include "stm8s_type.h" 
//#include "stm8s903k.h"
//#include "stm8s_type.h"
#include "tim.h"
//#include "stm8_bit.h"

#include "param.h"

/******************************************************************
*  Description    : It initializes PWM and ADC peripherals
*  TRG0 for TIM6 COUNT CLK
*  TIMI1 DO not stop 
*******************************************************************/
void PWM_INIT(void)
{
  TIM1->SR1=0x00;// clear int flag
  TIM1->CR1=0x05;//0x81;//TIM1_CR1_CEN=1 //
	//start count  UDIS =1 
  TIM1->CR2=0x71;// 0x21 ccpc=1; TRGO=UPDATE
  TIM1->SMCR=0x00;
  /* Time Base configuration */
	/*
	TIM1_Period = 1024
  TIM1_Prescaler = 0
  TIM1_CounterMode = TIM1_COUNTERMODE_UP
  TIM1_RepetitionCounter = 0
  16m /1024=15.625k
  DEADTIME :250NS
	*/
  //TIM1_RCR=;
  TIM1->PSCRH=0;
  TIM1->PSCRL=0;
  //TIM1_DCR=;
  TIM1->ARRH=(u8)(PWM_PERIOD>>8);
  TIM1->ARRL=(u8)PWM_PERIOD;
  TIM1->IER=0;//0x80;// only brk int
/***********************************************************
Channel 1, 2,3 and 4 Configuration in PWM mode 
000：冻结。输出比较寄存器TIM1_CCR1与计数器TIM1_CNT间的比较?
設C1REF不起作用；
001：匹配时设置通道1的输出为有效电平。当计数器TIM1_CNT的值?
氩痘?比较寄存器1 (TIM1_CCR1)相同时，强制OC1REF为高。
010：匹配时设置通道1的输出为无效电平。当计数器TIM1_CNT的值?
氩痘?比较寄存器1 (TIM1_CCR1)相同时，强制OC1REF为低。
011：翻转。当TIM1_CCR1=TIM1_CNT时，翻转OC1REF的电平。
100：强制为无效电平。强制OC1REF为低。
101：强制为有效电平。强制OC1REF为高。
110：PWM模式1－ 在向上计数时，一旦TIM1_CNT<TIM1_CCR1时通道1?
有效电平，否则为无效电平；在向下计数时，一旦TIM1_CNT>TIM1_CCR1
时通道1为无效电平(OC1REF=0)，否则为有效电平(OC1REF=1)。
111：PWM模式2?        在向上计数时，一旦TIM1_CNT<TIM1_CCR1时
通道1为无效电平
，否则为有效电平；在向下计数时
，一旦TIM1_CNT>TIM1_CCR1时通道1为有效电平，否则为无效电平。 
*************************************************************/
  TIM1->CCMR1=0X60;
  TIM1->CCMR2=0X60;
  TIM1->CCMR3=0X60;
  TIM1->CCMR4=0X00;
  TIM1->CCER1=0x00;
  TIM1->CCER2=0x00;
  TIM1->OISR=0x00;
  TIM1->DTR=0x00;//0X4a;//0x32;//0X0a;//死区时间，4*62NS
#ifdef	FUNC_HOC_PROTECT_EN
//  
  TIM1->BKR|=0X90;// 同OSSI，OSSR 状态  unable tim brk
#else
//
  TIM1->BKR|=0X80;// 同OSSI，OSSR 状态  unable tim brk
#endif
  
  // Resynch to have the Update evend during Undeflow
  //TIM1_EGR_UG=1;
  //TIM1_CR1_CEN=1;
	TIM1->EGR|=0x01;
	TIM1->CR1|=0x01;
  // Clear Update Flag
  /*TIM1_IER_UIE=1;*/
  DisAllPwmOut();
  /*
 	//default to 0% duty cycle
	ToCMPxH( TIM1->CCR1H, 0 );
	ToCMPxL( TIM1->CCR1L, 0 );
   */
}

/***************************************************************/
void pwm_reset()
{

  TIM1->SR1=0x00;// 
  TIM1->CR1=0x00;//
  TIM1->CR2=0x00;// 
  TIM1->SMCR=0x00;

  TIM1->PSCRH=0;
  TIM1->PSCRL=0;
  //TIM1_DCR=;
  TIM1->ARRH=0;
  TIM1->ARRL=0;
  TIM1->IER=0;//0x80;// only brk int


 TIM1->CCMR1=0X00;
  TIM1->CCMR2=0X00;
  TIM1->CCMR3=0X00;
  TIM1->CCMR4=0X00;
  TIM1->CCER1=0x00;
  TIM1->CCER2=0x00;
  TIM1->OISR=0x00;
  TIM1->DTR=0x00;//0X4a;//0x32;//0X0a;//死区时间，4*62NS
  TIM1->BKR=0X00;// 同OSSI，OSSR 状态  unable tim brk
  // Resynch to have the Update evend during Undeflow
  //TIM1_EGR_UG=1;
  //TIM1_CR1_CEN=1;
	//TIM1_EGR|=0x01;
	TIM1->CR1|=0x01;
  // Clear Update Flag
  /*TIM1_IER_UIE=1;*/
  DisAllPwmOut();
}
/******************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
*******************************************************************/
void TIM1_BRK_EVENT(void)
{

  DisAllPwmOut();
//  ChangeDuty(0x00);
  
}
//==================================================================
/*******************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
********************************************************************/


void DisAllPwmOut(void)
{
  TIM1->CCER1 &= (~TIM1_CCER1_CC1E);     // =0;//TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE);
  TIM1->CCER1 &= (~TIM1_CCER1_CC1NE);    //  TIM1_CCER1_CC1NE=0;//TIM1_CCxNCmd(TIM1, TIM1_CHANNEL_1, DISABLE);
  TIM1->CCER1 &= (~TIM1_CCER1_CC2E);    // TIM1_CCER1_CC2E=0;//TIM1_CCxCmd(TIM1, TIM1_CHANNEL_2, DISABLE);
  TIM1->CCER1 &= (~TIM1_CCER1_CC2NE);    // TIM1_CCER1_CC2NE=0;//TIM1_CCxNCmd(TIM1, TIM1_CHANNEL_2, DISABLE);
  TIM1->CCER2 &= (~TIM1_CCER2_CC3E);    // TIM1_CCER2_CC3E=0;//TIM1_CCxCmd(TIM1, TIM1_CHANNEL_3, DISABLE);
  TIM1->CCER2 &= (~TIM1_CCER2_CC3NE);    // TIM1_CCER2_CC3NE=0;//TIM1_CCxNCmd(TIM1, TIM1_CHANNEL_3, DISABLE);
  TIM1->EGR |= TIM1_EGR_UG;     // TIM1_EGR_UG=1;//COMG=1;//TIM1_GenerateEvent(TIM1_EVENTSOURCE_COM);
}

//====================================================================
/*********************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
*********************************************************************/
//void TIM1_UP_IRQHandler(void)
// just like systick scale:64us; max:17ms(8bit);
//void PWM_UpdateEvent(void)
//{//TIM1_SR1_UIF=0;
 
//}


//====================================================================
/*********************************************************************
* 函数名称: time5  setup   stege
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
**********************************************************************/
//scale 4ns  maxcount 262ms   TIM5_PSCR_PSC=0x08;// psc=256

void TIM5_Conf(void)
{   
  TIM5->IER=0x00;
  TIM5->EGR |= TIM5_EGR_UG;
  TIM5->PSCR=0x03;//0xfc;// psc=64分频2的n次方  psr=7 2^7  8us  b`128
  TIM5->ARRH=0x00;
  TIM5->ARRL=0x01;
  TIM5->SR1=0x00;// clear int flag
  TIM5->CR1=0x01;//0x84;//URS 只有计数器溢出 产生中断。
  TIM5->CR2=0x00;
  TIM5->SMCR=0x00;
  TIM5->IER=0x01;// only update event
 }


//=================================================================
/******************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
******************************************************************/
void TIM5_Start(void)
{
  TIM5->ARRH=0x00;//00
  TIM5->ARRL=0x6c;//B6		//6c
  TIM5->CR1 |= TIM5_CR1_CEN;
}
//===========================================
void TIM5_StartCount(void)
{
  TIM5->ARRH=0x00;//00
  TIM5->ARRL=0x6c;//B6---6c	//6c
  TIM5->CR1 |= TIM5_CR1_CEN;    // =1;
}
//================================================================
// set compare value is max avld unexpect int
//16bit =65535  分频8us   最大定时65535*8=524280us 约524ms
//================================================================
void TIM5_StopCount(void)
{
  TIM5->CR1 &= (~TIM5_CR1_CEN);     // TIM5_CR1_CEN=0;
  TIM5->CNTRH=0x00;
  TIM5->CNTRL=0x00;
}


void TIM5_Getbemf_StartCount(void)
{
  TIM5->ARRH=0x00;//00
  TIM5->ARRL=0x50;//B6---6c
  TIM5->CR1 |= TIM5_CR1_CEN;      // TIM5_CR1_CEN=1;
}


void TIM5_Ready_StartCount(void)
{ 
  TIM5->ARRH=0x00;//00
  TIM5->ARRL=0x50;//B6---6c
  TIM5->CR1 |= TIM5_CR1_CEN;    // TIM5_CR1_CEN=1;
}


/**********************************************************************
* 函数名称: time6  setup  stege---
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
**********************************************************************/
//generat 16.3MS inttruput 
void Tim6Init(void)
{
  TIM6->SR1=0x00;
  TIM6->SMCR=0x00;// 从模式 计数时钟来自TIM 更新事件
  TIM6->CR1=0x04;// only ov event 
  TIM6->IER |= TIM6_IER_UIE;    // TIM6_IER_UIE=1;
  // TIM6_IER_TIE=1;////---------
  TIM6->PSCR=0x07;//
  TIM6->ARR=0xff;
  TIM6->EGR |= TIM6_EGR_UG;     // TIM6_EGR_UG=1;
  TIM6->CR1 |= TIM6_CR1_CEN;    // TIM6_CR1_CEN=1;
  TIM6->IER=0x01;
}
//================================================================
/*****************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
******************************************************************/
void TIM5_Star(void)
{
  TIM5->ARRH=0x22;//48
  TIM5->ARRL=0x22;//00
  TIM5->CR1 |= TIM5_CR1_CEN;    // TIM5_CR1_CEN=1;
}