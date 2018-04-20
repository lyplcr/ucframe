/* Copyright (c) 王元
 * 20180101
 * MCU
 */

/* Includes ------------------------------------------------------------------*/
#include "mcu.h"

/* Exported define -----------------------------------------------------------*/
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

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MCUInit(void)
{
  
}
