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
* º¯ÊýÃû³Æ: 
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
*************************************************************/
void interrapt_init(void)
{

}

void  RSET_io()
{
  Gpio_Init();
  GPIOC->ODR |= 0x1f;        //PC5_OUT=1;PC6_OUT=1;PC7_OUT=1;
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
//Ê±ÖÓ³õÊ¼»¯-ÄÚ²¿RC -16Mhz== 	
	sys_clk_init();
//==ÖÐ¶ÏÓÅÏÈ¼¶³õÊ¼»¯========
	Gpio_interruput_Init();
		
//===¹ØËùÓÐÖÐ¶Ï¹Ø..=========
	_asm("sim");
//==io¶Ë¿Ú³õÊ¼»¯-===========
		
	Gpio_Init(); 
	PB7_OUT=0;
	PB6_OUT=0;
	PE5_OUT =0;
	PF4_OUT=0;
						
//===pwm·½²¨Êä³ö³õÊ¼»¯======
//=³õÊ¼»¯¶¨Ê±Æ÷1Î»PWM·½Ê½===
	PWM_INIT();    
//==adc ³õÊ¼»¯==============
//==Æô¶¯Ê±°´×¢Èë·½Ê½========
//	adc_init();     //adc³õÊ¼»¯

//==tim5 16Î»¶¨Ê±Æ÷=========
	TIM5_Conf();	 
//==tim5 8Î»¶¨Ê±Æ÷==========
			
	Tim6Init();
		
		
  #if 0		//-------------------------------
	  POWER_SW_OF	   //¼ÌµçÆ÷³õÊ¼»¯
    PER_LED_ON
  	GREEN_LED_ON
	  uart_init();   // ´®¿Ú³õÊ¼»¯--²¨ÌØÂÊ9600
	//=======================================
	//²ÎÊý³õÊ¼»¯£-----------------------------
  //PC5_OUT =1;
	//PD6_OUT=0;
	//check_voltage();//¼ì²âµçÈÝ³äµç¹ý³Ì=====
//	for(i=0;i<200;i++)delay();//ÑÓÊ±³äµç·½Ê½
//	PER_LED_OF
//	GREEN_LED_ON
//	duty=2;
	//--------------------------------------
// 	ioget =ch_sw();
#endif	//--------------------------------


//===Æô¶¯¶¨Ê±Æ÷¹¤×÷=======================
	TIM5_StartCount();
//  Motordata.station= Frun;
//	ADC_CR1_ADON = 1;  
//	ADC_CR1_ADON = 1;  
	_asm("rim");//ÖÐ¶Ï¿ª.................
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
