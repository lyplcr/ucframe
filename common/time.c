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
time_t time;

/*  functions ----------------------------------------------------------------*/
// 
void Delayms(uint16_t ms)
{
//  uint32_t tickstart = 0U;
  
//  tickstart = HAL_GetTick();
//  while((HAL_GetTick() - tickstart) < delay)
  {
  }
}

// 创建注册日期时间
void RefreshTime(void)
{
  
}

// 
void SetTime(date_t *d, clock_t *c)
{
  time.date.year = d->year;
  time.date.month = d->month;
  time.date.day = d->day;
  time.clock.hour = c->hour;
}

void TimeInit(void)
{
  time.Delayms = Delayms;  
  time.RefreshTime = RefreshTime;
  time.SetTime = SetTime;
}
/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


