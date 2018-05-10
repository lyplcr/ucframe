/**********************************************************
*name   : board.h
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOARD_H
#define __BOARD_H


/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"

/*  defines&macro ------------------------------------------------------------*/
// BUTTON/KEY SWIM
#define KEY_PORT        GPIOD
#define KEY_PIN         GPIO_PIN_1

// LED
// LED1:PB7; LED2:PB6; SW2:PB5; SW1:PB4; LED4:PE5
#define LED_PORT        GPIOB
#define LED_PIN         GPIO_Pin_7
#define LED_ON()        GPIOC->BRR =LED_PIN
#define LED_OFF()       GPIOC->BSRR=LED_PIN

// PA1\PA2\PA3:U\V\W 
#define UVW_PORT        GPIOA
#define U_PIN           GPIO_Pin_1
#define V_PIN           GPIO_Pin_2
#define W_PIN           GPIO_Pin_3

// PC1\PC2\PC3\PC5\PC6\PC7:R\S\T L\H    // 

// PD7:DIR 
#define DIR_PORT        GPIOD
#define DIR_PIN         GPIO_Pin_7

// SPEED:PB3 AD
#define SPEED_PORT      GPIOB
#define SPEED_PIN       GPIO_Pin_3

// ISENSE:PB2
#define ISENSE_PORT     GPIOB
#define ISENSE_PIN      GPIO_Pin_2

// PD0:OCP; 
#define OCP_PORT        GPIOD
#define OCP_PIN         GPIO_Pin_0

// VDETEC:PB1
#define VDETEC_PORT     GPIOB
#define VDETEC_PIN      GPIO_Pin_1

// T_MOS:PB0
#define T_MOS_PORT      GPIOB
#define T_MOS_PIN       GPIO_Pin_0

// PD3:EBMFR; PD5:EBMFS; PD6:EBMFT
#define EBMF_PORT       GPIOD
#define EBMFR_PIN       GPIO_Pin_3
#define EBMFS_PIN       GPIO_Pin_5
#define EBMFT_PIN       GPIO_Pin_6

// PD2:DELAY; 
#define DELAY_PORT      GPIOD
#define DELAY_PIN       GPIO_Pin_2

// TIM
#define PWM_PERIOD  (0x0500-1)  // (0x0200-1)

// ADC
#define	CURR_ADC_CH	2       // µçÁ÷ PB2
#define	BEMFA_ADC_CH    4
#define	BEMFB_ADC_CH	5
#define	BEMFC_ADC_CH	6
#define	CURR_CHANEL	2
#define	BEMFA_CHANEL	4
#define	BEMFB_CHANEL	5
#define	BEMFC_CHANEL	6

/*  typedef ------------------------------------------------------------------*/

//typedef struct
//{
//  
//} board_t;

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/
void BoardInit(void);
void LedOn(void);
void LedOff(void);

#endif