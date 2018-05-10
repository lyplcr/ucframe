/**********************************************************
*name   : main.c
*detail : 入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

//#define  LED1   PB7_OUT
#define LED1L() GPIOB->ODR &= 0x7f
#define LED1H() GPIOB->ODR |= 0x80

//#define  LED2   PB6_OUT
#define LED2L() GPIOB->ODR &= 0xbf
#define LED2H() GPIOB->ODR |= 0x40

//#define  LED3   PF4_OUT
#define LED3L() GPIOF->ODR &= 0xef
#define LED3H() GPIOF->ODR |= 0x10

//#define  LED4   PE5_OUT
#define LED4L() GPIOF->ODR &= 0xdf
#define LED4H() GPIOE->ODR |= 0x20

//#define  SW1    PB4_OUT
#define SW1L() GPIOB->ODR &= 0xef
#define SW1H() GPIOB->ODR |= 0x10

//#define  SW2    PB5_OUT
#define SW2L() GPIOB->ODR &= 0xdf
#define SW2H() GPIOB->ODR |= 0x20

extern  const  uint8_t  showsp[];

/*  functions ----------------------------------------------------------------*/
void  DIS_mode_scan_status(void);
void  eeprom_openlock(void);
void  eeprom_w_char(void);
void  Disp_error_on(void);
void  Disp_error_of(void);
void  POWER_dis_prc(void);
void  FScan_disply(void);
void  FScan_fof(void);
void  FScan_fon(void);
void  FScan_led4(void);
void  FScan_sw1(void);
void  FScan_sw2(void);

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/