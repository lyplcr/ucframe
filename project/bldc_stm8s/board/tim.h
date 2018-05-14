/**********************************************************
*name:     tim.h
*version:   v1.0
*mcu:       903k3
*sdk:       stvd
*detail:    gpio 
*author:    hongwei luo
*date:      2016-4-6
***********************************************************/

#ifndef __TIM_H_
#define __TIM_H_


/************************************************************
*
*************************************************************/
//#include"public.h"
#include "platform.h"


/************************************************************
*
*************************************************************/



#define PWM_PERIOD  (0x0500-1)//(0x0200-1)// 

/**************************************************************************************************
* 函数声明：
* 参数描述: 无
* 日期:     
**************************************************************************************************/
//---------------------------------------16m /1024=15.625k-----------------------------------------
void TIM5_Ready_StartCount(void);

void PWM_INIT(void);
void TIM1_BRK_EVENT(void);
void Tim6Init(void);
void TIM5_StartCount(void);
void TIM5_StopCount(void);
void DisAllPwmOut(void);
void TIM5_Conf(void);
void ChangeDuty(u16 pwm_value);
void ReadHallGetStep(void);
void NorChangePhase(void);
void TIM5_Star(void);
void TIM5_Start(uint16_t arr);
void pwm_reset(void);     
/*===================================================================================================*/

#endif
