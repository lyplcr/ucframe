/**********************************************************
*name   : board.h
*detail : 包含板设相关头文件
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOARD_H
#define __BOARD_H


/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/*  defines&macro ------------------------------------------------------------*/
// BUTTON
#define BUTTON_PORT             GPIOC
#define BUTTON_PIN              GPIO_PIN_0

// LED:PC13
// LED1:PB7; LED2:PB6; SW2:PB5; SW1:PB4; LED4:PE5
#define LED_PORT        GPIOH
#define LED_PIN         GPIO_Pin_13
#define LED_ON()        GPIOC->BRR =LED_PIN
#define LED_OFF()       GPIOC->BSRR=LED_PIN

// SPEED:PB3 AD按键调速

// PD7:DIR 正反转

// ISENSE:PB2; VDETEC:PB1; T_MOS:PB0

// PC1\PC2\PC3\PC5\PC6\PC7:R\S\T L\H
// PD3:EBMFR; PD5:EBMFS; PD6:EBMFT
// PA1\PA2\PA3:U\V\W

// PD0:OCP; 

// PD2:DELAY; 电钻按键，电源开关？




/*  typedef ------------------------------------------------------------------*/
typedef struct
{
  char company[8];
  uint32_t chipid;
  uint32_t clock;
//  uint32_t ramsize;
//  uint32_t ramaddr;
//  uint32_t romsize;
//  uint32_t romaddr;
//  void (*EnISR);
//  void (*DisISR);	// 这两个用宏定义表示好点
//  void (*GetChipID);
//  void (*TaskSwitch);
#if 0
  uint32_t appaddr;
  uint32_t paramaddr;   // 参数地址即本身地址，可放在固定地址
  uint32_t externram;
  uint32_t externrom;
#endif
} mcu_t;
extern mcu_t mcu;

//typedef struct
//{
//  
//} board_t;

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/
void BoardInit(void);


#endif