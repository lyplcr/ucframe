/**********************************************************
*name   : motor.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "stm8s_type.h" 
//#include "stm8s903k.h" 
//#include "gpio.h"
//#include "uart.h"
//#include "stm8_bit.h"
//#include "tim.h"
//#include "adc.h"
#include "mc_config.h"
#include "param.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/


/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


void sys_clk_init()
     {
       CLK_CKDIVR=(0x00|0x00);
	  	}

/************************************************************
* ∫Ø ˝√˚≥∆: 
* ≤Œ ˝√Ë ˆ: Œﬁ
* ∑µªÿ÷µ:   Œﬁ
* √Ë ˆ:     
*************************************************************/
void interrapt_init(void)
{

}

void  RSET_io()
{
  Gpio_Init();
   PC5_OUT=1;
   PC6_OUT=1;
   PC7_OUT=1;
}

//
void delay(void)
     {int i;
		  for(i=0;i<10000;i++);
      
    }


//
void Sys_Init(void)
{   
	u8 i;
// ±÷”≥ı ºªØ-ƒ⁄≤øRC -16Mhz== 	
	sys_clk_init();
//==÷–∂œ”≈œ»º∂≥ı ºªØ========
	Gpio_interruput_Init();
		
//===πÿÀ˘”–÷–∂œπÿ..=========
	_asm("sim");
//==io∂Àø⁄≥ı ºªØ-===========
		
	Gpio_Init(); 
	PB7_OUT=0;
	PB6_OUT=0;
	PE5_OUT =0;
	PF4_OUT=0;
						
//===pwm∑Ω≤® ‰≥ˆ≥ı ºªØ======
//=≥ı ºªØ∂® ±∆˜1ŒªPWM∑Ω Ω===
	PWM_INIT();    
//==adc ≥ı ºªØ==============
//==∆Ù∂Ø ±∞¥◊¢»Î∑Ω Ω========
//	adc_init();     //adc≥ı ºªØ

//==tim5 16Œª∂® ±∆˜=========
	TIM5_Conf();	 
//==tim5 8Œª∂® ±∆˜==========
			
	Tim6Init();
		
		
  #if 0		//-------------------------------
	  POWER_SW_OF	   //ºÃµÁ∆˜≥ı ºªØ
    PER_LED_ON
  	GREEN_LED_ON
	  uart_init();   // ¥Æø⁄≥ı ºªØ--≤®Ãÿ¬ 9600
	//=======================================
	//≤Œ ˝≥ı ºªØ£-----------------------------
  //PC5_OUT =1;
	//PD6_OUT=0;
	//check_voltage();//ºÏ≤‚µÁ»›≥‰µÁπ˝≥Ã=====
//	for(i=0;i<200;i++)delay();//—” ±≥‰µÁ∑Ω Ω
//	PER_LED_OF
//	GREEN_LED_ON
//	duty=2;
	//--------------------------------------
// 	ioget =ch_sw();
#endif	//--------------------------------


//===∆Ù∂Ø∂® ±∆˜π§◊˜=======================
	TIM5_StartCount();
//  Motordata.station= Frun;
//	ADC_CR1_ADON = 1;  
//	ADC_CR1_ADON = 1;  
	_asm("rim");//÷–∂œø™.................
	//

}
//========================================

//
void Motor_Init(void)
{
	
	Motordata.station= Ready;
	Adc_SetUp_Init();
	_asm("rim");
}
