/**********************************************************
*name   : gpio.c
*detail : éãƒ¥å½›æ¶“è¯²åš±é?
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
  // ÖÐ¶ÏÊäÈë UVWÈýÏà»»Ïà×´Ì¬
  GPIOA->DDR = 0x00;
  GPIOA->CR1 = 0xff;
  // µÍËÄÎ»Ä£ÄâÊäÈë£¬¼ì²âµçÁ÷µçÑ¹ºÍËÙ¶È£¬¸ßËÄÎ»LED
  GPIOB->DDR = 0xf0;
  GPIOB->CR1 = 0xf0;
  GPIOB->CR2 = 0x00;
  // mos¹Ü¿ª¹Ø£¬ÈýÏàÊä³ö
  GPIOC->DDR = 0xff;
  GPIOC->CR1 = 0xff;
  GPIOC->CR2 = 0x00;
  // PD2 DELAYÊä³ö£¬ÆäËûÊäÈë£¬PD1 ledÉÏÀ­ÊäÈë£¬PD7 dir ÉÏÀ­ÊäÈë
  GPIOD->DDR = 0x14;
  GPIOD->CR1 = 0x96;
  GPIOD->CR2 = 0x00;
  GPIOD->ODR &= 0xef;
  // LED4
  GPIOE->DDR = 0xff;
  GPIOE->CR1 = 0xff;
  GPIOE->CR2 = 0x00;
  GPIOE->ODR = 0xf0;
  // LED3
  GPIOF->DDR = 0xff;
  GPIOF->CR1 = 0xff;
  GPIOF->CR2 = 0x00;
  GPIOF->ODR = 0x00;
}

// 
void Gpio_interruput_Init(void)
{
  EXTI->CR1 = 0x83;     // PDÏÂ½µÑØ¡¢PAÉÏÏÂ½µÑØÖÐ¶Ï£¨UVW£©
}

//
void Gpio_pulse(uint8_t phz)
{
  uint8_t sph;
  
  sph=phz;
}

// 
void PrcTask_Ph(uint8_t phx)
{
  uint8_t phk;
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


		