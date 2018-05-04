/**********************************************************
*name   : gpio.c
*detail : 鍏ュ彛涓诲嚱鏁?
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

#include "platform.h"

//=======================

#define  gpio

// 
void Gpio_Init(void);
void Gpio_interruput_Init(void);

// 
void Gpio_Init(void)
{
  GPIOA->DDR = 0x00;
  GPIOA->CR1 = 0xff;
  
  GPIOB->DDR = 0xf0;
  GPIOB->CR1 = 0xf0;
  GPIOB->CR2 = 0x00;
  
  GPIOC->DDR = 0xff;
  GPIOC->CR1 = 0xff;
  GPIOC->CR2 = 0x00;
  
  GPIOD->DDR = 0x14;
  GPIOD->CR1 = 0x96;
  GPIOD->CR2 = 0x00;
  GPIOD->ODR &= 0xef;
  
  GPIOE->DDR = 0xff;
  GPIOE->CR1 = 0xff;
  GPIOE->CR2 = 0x00;
  GPIOE->ODR = 0xf0;
  
  GPIOF->DDR = 0xff;
  GPIOF->CR1 = 0xff;
  GPIOF->CR2 = 0x00;
  GPIOF->ODR = 0x00;
}

// 
void Gpio_interruput_Init(void)
{
  EXTI->CR1 = 0x83;     // EXTI_CR1=0x83;
}

//
void Gpio_pulse(u8 phz)
{
  u8 sph;
  
  sph=phz;
}

// 
void PrcTask_Ph(u8 phx)
{
  u8 phk;
  phk=phx;
  //AC	
  if(phk==1)
  {
    GPIOC->ODR=0x22;  
  }//22==82
  //CA		
  else if(phk==2)
  {
    GPIOC->ODR=0x88;
  }//88===28
  //AB		
  else if(phk==3)
  { 
    GPIOC->ODR=0x42;		
  }//42===42
  //BA	
  else if(phk==4)
  {  
    GPIOC->ODR=0x84;		
  }//84====24
  //BC	
  else if(phk==5)
  {
    GPIOC->ODR=0x24; 
  }//24====84
  //CB	
  else if(phk==6)
  {  
    GPIOC->ODR=0x48;
  } //48====48
  else
  {

  }
}


		