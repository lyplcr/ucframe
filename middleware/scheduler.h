/* Copyright (c) 2018 王元
 * 20180101
 * 基于时间触发的混合式调度器
 http://www.51hei.com/bbs/dpj-41383-1.html
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/
#define MAXTASKS 2

/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  void (*pTask)(void);  
  uint16_t delay;       // 首次时间
  uint16_t period;      // 运行周期
  uint16_t runme;       // 
  uint16_t type;        // 任务类型，0为抢占式，  
} task_t; 

typedef struct
{
  char cmd[8];
  char parameter[8];
  uint8_t *data;
  
  void (*SchUpdata)(void);
  uint8_t (*AddTask)(void (* pFunction)(void), uint16_t delay, uint16_t  period, uint16_t type);
  void (*DispatchTasks)(void);
  uint8_t (*DeleteTask)(uint8_t taskindex);
} scheduler_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void SchInit(void);

#endif

