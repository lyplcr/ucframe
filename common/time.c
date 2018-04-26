/**********************************************************
*name   : time.c
*detail : 时间相关函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "time.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
datatime_t datatime;

/*  functions ----------------------------------------------------------------*/
// 
void Delay(uint16_t delay)
{
//  uint32_t tickstart = 0U;
  
//  tickstart = HAL_GetTick();
//  while((HAL_GetTick() - tickstart) < delay)
  {
  }
}

// 创建注册日期时间
void CreatDataTime(void)
{
//  datatime.DatatimeSet = DatatimeSet;
  
  datatime.Delay = Delay;
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


