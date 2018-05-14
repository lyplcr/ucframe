/**********************************************************
*name   : platform.h
*detail : ƽ̨�������ʼ��������
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_H
#define __PLATFORM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "stm8s.h"
#include "time.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/
typedef struct
{
  uint32_t chipid;
  uint32_t clock;
  uint32_t ramaddr;
  uint32_t ramsize;
  uint32_t romaddr;
  uint32_t romsize;
#if 0
  void (*EnIRQ)(void);  // 这个怎么实现替代？不然不可以mcu调用
  void (*DisIRQ)(void);
#else
#define EnIRQ() __enable_interrupt()
#define DisIRQ() __disable_interrupt()
#endif
#if 0
  uint32_t appaddr;
  uint32_t appsize;
  uint32_t paramaddr;   // 参数地址即本身地址，可放在固定地址
  uint32_t paramsize;
  uint32_t externram;
  uint32_t externrom;
  
  void (*GetChipID);
  void (*TaskSwitch);
  
  char company[8];
#endif
} mcu_t;
extern const mcu_t mcu;

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/
extern void PlatfrmInit(void);

#endif

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/