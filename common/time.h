/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * LED
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIME_H
#define __TIME_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
/* DATATIME */
typedef struct
{
  uint8_t year;
  uint8_t month;
  uint8_t week;
  uint8_t date;
} date_t;

typedef struct
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t timer;
} time_t;

typedef struct
{
  date_t data;
  time_t time;
  uint16_t ms;
  uint16_t us;
//  void (*CreatDataTime)(void);
  void (*Delay)(uint16_t ms);
  void (*DatatimeSet)(date_t *d, time_t *t);  
  void (*RefreshDate)(void);
  void (*RefreshTime)(void);
} datatime_t;
extern datatime_t datatime;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

