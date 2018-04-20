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


 
/* Includes ------------------------------------------------------------------*/
#include "common.h"

/*  defines ------------------------------------------------------------------*/
/*  typedef ------------------------------------------------------------------*/
/*  variables  ---------------------------------------------------------------*/
/*  functions ----------------------------------------------------------------*/
void ChangeDuty(uint16_t pwm_value);
void change_ph(void);
uint8_t GetHall(void);
uint8_t Get_pa_vhl(void);
void bskill_run(void);

#endif