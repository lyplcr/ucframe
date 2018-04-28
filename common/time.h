/**********************************************************
*name   : time.h
*detail : 时间相关函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

#ifndef __TIME_H
#define __TIME_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/
typedef enum
{
  YEAR, MONTH, WEEK, day, HOUR, INUTE, SECOND, MS, US
} datatime_t;

typedef struct
{
  uint8_t year;
  uint8_t month;
  uint8_t week;
  uint8_t day;
} date_t;

typedef struct
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t timer;
} clock_t;

typedef struct
{
  date_t date;
  clock_t clock;
  uint16_t ms;
  uint16_t us;
  void (*Delayms)(uint16_t ms);
  void (*RefreshTime)(void);
  void (*SetTime)(date_t *d, clock_t *c);
  void (*Alarm)(date_t *d, clock_t *c);
  void (*Timer)(clock_t c);
} time_t;
extern time_t time;

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/

#endif

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/

