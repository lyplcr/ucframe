/* Copyright (c) 王元
 * 20180101
 * 基于时间触发的混合式调度器
 */

/* Includes ------------------------------------------------------------------*/
#include "scheduler.h"

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
scheduler_t scheduler;
task_t task[MAXTASKS];

/* static functions ------------------------------------------------------- */
void SchUpdata(void);
uint8_t AddTask(void (* pFunction)(void), uint16_t delay, uint16_t  period, uint16_t type);
uint8_t DeleteTask(uint8_t taskindex);
void DispatchTasks(void);

void ReportStatus(void);
void GotoSleep(void);

/* Exported functions ------------------------------------------------------- */
void SchInit(void)
{
  scheduler.SchUpdata = SchUpdata;
  scheduler.AddTask = AddTask;
  scheduler.DeleteTask = DeleteTask;
  scheduler.DispatchTasks = DispatchTasks;
  
  for (uint8_t id=0; id<MAXTASKS; id++)
  {
    scheduler.DeleteTask(id);
  }
}

void SchUpdata(void)    // 放时间调度定时器里面
{
  for (uint8_t index=0; index<MAXTASKS; index++)
  {
    if (task[index].pTask)
    {
      if (task[index].delay == 0)
      {
        if (task[index].type)
        {
          task[index].runme += 1;
        }
        else
        {
          (*task[index].pTask)();       // 运行任务
          task[index].runme -= 1;
          if (task[index].period == 0)
          {
            task[index].pTask = 0;
          }
        }
        if (task[index].period)
        {
          task[index].delay = task[index].period;
        }
      }
      else
      {
        task[index].delay -= 1;
      }
    }
  }
}

uint8_t AddTask(void (* pFunction)(void), uint16_t delay, uint16_t  period, uint16_t type)
{
  uint8_t index = 0;
  
  while ((task[index].pTask != 0) && (index<MAXTASKS))
  {
    index++;
  }
  
  if (index == MAXTASKS)
  {
    // Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
  }
  else
  {
    task[index].pTask = pFunction;
    task[index].delay = delay;
    task[index].period = period;
    task[index].type = type;
    task[index].runme = 0;
  }

  return index;
}

uint8_t DeleteTask(uint8_t index) 
{
  int8_t returncode;
  
  if (task[index].pTask == 0)
  {
//    Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
    returncode = 0;
  }
  else
  {
    returncode = 1;
  }
  
  task[index].pTask = 0;
  task[index].delay = 0;
  task[index].period = 0;
  task[index].type = 0;
  task[index].runme = 0;

  return returncode;
}

void DispatchTasks(void)        // 放在主循环内
{
  for (uint8_t index=0; index<MAXTASKS; index++)
  {
    if ((task[index].type) && (task[index].runme>0))
    {
      (*task[index].pTask)();
      task[index].runme -= 1;
      
      if (task[index].period == 0)      // 一次性的
      {
        task[index].pTask = 0;
      }
    }
  }
   
   ReportStatus();
   GotoSleep();
}

void ReportStatus(void)
{
}

void GotoSleep(void)    // 低功耗休眠需要
{
}