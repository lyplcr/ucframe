/**********************************************************
*name   : motor.c
*detail : motor入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
param Motordata;
collect Injection;
/*  functions ----------------------------------------------------------------*/

// 
void MotorReset(void)
{
  
}

//
void MotorInit(void)
{
  MotorReset();
  Motordata.station= Ready;
//  Adc_SetUp_Init();
  EnIRQ();
}

//void FScan_disply(void)
//{}
/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/