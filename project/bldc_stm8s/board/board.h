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
#define LED_PORT        GPIOH
#define LED_PIN         GPIO_Pin_13
#define LED_ON()        GPIOC->BRR =LED_PIN
#define LED_OFF()       GPIOC->BSRR=LED_PIN

/*  typedef ------------------------------------------------------------------*/
//typedef struct
//{
//  
//} board_t;
/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/
void BoardInit(void);


#endif