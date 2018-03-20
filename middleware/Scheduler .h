/* Copyright (c) 2018 王元
 * 20180101
 * 基于时间触发的混合式调度器
 http://www.51hei.com/bbs/dpj-41383-1.html
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VSHELL_H
#define __VSHELL_H

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
  
} vshell_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

