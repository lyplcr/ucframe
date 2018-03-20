/* Copyright (c) 2018 王元
 * 20180101
 * 有限状态机
 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSM_H
#define __FSM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  char cmd[8];
  char parameter[8];
  uint8_t *data;
  
  void (*ParseCMD);
  void (*Pipe);
  void (*Dup);
  
} fsm_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

