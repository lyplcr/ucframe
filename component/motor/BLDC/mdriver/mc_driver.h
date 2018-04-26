/**********************************************************
*name:      gpio.h
*version:   v1.0
*mcu:       903k3
*sdk:       stvd
*detail:    gpio 
*author:    hongwei luo
*date:      2016-4-6
***********************************************************/
#ifndef _MC_DRIVER_H_
#define _MC_DRIVER_H_
#endif

 
/**************************************************************************************************
* 函数声明：
* 参数描述: 无
* 日期:     
**************************************************************************************************/
#include "public.h"
void ChangeDuty(u16 pwm_value);
void change_ph(void);
u8 GetHall(void);
u8 Get_pa_vhl(void);
void bskill_run(void);