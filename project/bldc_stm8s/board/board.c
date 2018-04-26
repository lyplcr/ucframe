/**********************************************************
*name   : main.c
*detail : 入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
#if 0
//#define DATA_ROM _Pragma("location=\".rom_data\"") 
//DATA_ROM const PRODUCTINFO productinfo =
//const PRODUCTINFO productinfo @".MYSEG1" = 同上两种放在固定地址的办法
const mcu_t mcu =
{
  {'S','T','M','3','2','F','1','0'},
  0x12345678,
  72000000
};
#else
mcu_t mcu;
#endif

/*  functions ----------------------------------------------------------------*/
void GPIOInit(void)
{
  
}

//
void TimeInit(void)
{
  
}

//
void BoardInit(void)
{
  GPIOInit();
  TimeInit();
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/