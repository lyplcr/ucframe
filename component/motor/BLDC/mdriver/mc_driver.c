

/*******************************coptright(c)***************************************
*
* --------------------  ShenZhen  pace  electronics  co.LTD  -------------------
*
*                             BLDC  energy  Team
*
*---file info----------------------------------------------------------------------
*
*  文件名称:	    ADC.c
*  修改日期：     v1.0
*  最终版本：     v2.0 
*  简要描述:      TIME  module init
*
*----------------------------------------------------------------------------------
*  创建作者:       roger luo
*  创建日期:       2016.04.16
*  创建版本：      V1.0
*  创建描述:       TIME  module init
*
*----------------------------------------------------------------------------------
*  修改人员：     NO
*  修改日期：     NO
*  修改版本：     NO
*  修改描述：     NO
*
**********************************************************************************/












#include "mc_driver.h"
#include "tim.h"
#include "param.h"

/***********************************************
*#didine
***********************************************/
char vtale[][]={{1,2,3},{3,4,5}};
u8 check_step;
u8 check_table[]={0,0,0};


/************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
**************************************************/

void ChangeDuty(u16 pwm_value)
{
	u8 CCRH,CCRL;
	if(pwm_value>PWM_PERIOD) 
	{
		pwm_value=PWM_PERIOD;
	}
	CCRH=(u8)(pwm_value >> 8);
	CCRL=(u8)(pwm_value);
//	
	TIM1_CCR1H =CCRH;
	TIM1_CCR1L =CCRL;
	TIM1_CCR2H =CCRH;
	TIM1_CCR2L =CCRL;
	TIM1_CCR3H =CCRH;
	TIM1_CCR3L =CCRL;
	
	pwm_value+=100;
	pwm_value=pwm_value>>1;
	CCRH=(u8)(pwm_value >> 8);
	CCRL=(u8)(pwm_value);
	TIM1_CCR4H =CCRH;
	TIM1_CCR4L =CCRL;
}

    
  
	
/*****************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 
* 返回值:  
* 描述:  
   TIM1_CCER2_CC3NE=0;   
   TIM1_CCER2_CC3E=0;   
   TIM1_CCER2_CC4E=1;  
   TIM1_CCER1_CC2NE=0;  
   TIM1_CCER1_CC2E =0;   
   TIM1_CCER1_CC1NE=0;  
   TIM1_CCER1_CC1E =0;   
*****************************************************/ 
void change_ph()
{
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;
			TIM1_CCER2_CC3NE=0; 	
			TIM1_CCER1_CC2NE =0;
			TIM1_CCER1_CC1NE =0;


	switch(Motordata.mstep)
	{
//=======================	
//==ac
		case 0x05:
		{
/*
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;
			TIM1_CCER2_CC3NE=0; 	
			TIM1_CCER1_CC2NE =0;
			TIM1_CCER1_CC1NE =0;
*/
			
			TIM1_CCER2_CC3E=0;	
			TIM1_CCER1_CC2E =0;
			TIM1_CCER1_CC1E =1;
//--------------		
			PC6_OUT=0;
			PC7_OUT=0;
			PC5_OUT=1;

		}break;
//=======================	
//===ab66
		case 0x01:
		{
/*			
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;
			TIM1_CCER2_CC3NE=0;   						
			TIM1_CCER1_CC2NE =0;
			TIM1_CCER1_CC1NE =0;
*/			
			TIM1_CCER2_CC3E=0;
			TIM1_CCER1_CC2E =0;
			TIM1_CCER1_CC1E =1;
 //---------------
			
			PC5_OUT=0;
			PC7_OUT=0; 
			PC6_OUT=1;
    	   	}break;
				 
//=======================				
//==ba				 				 
		case 0x03:
		{
/*			
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;			
			TIM1_CCER2_CC3NE=0;   									
			TIM1_CCER1_CC2NE =0;
			TIM1_CCER1_CC1NE =0;
*/
			TIM1_CCER2_CC3E=0;
			TIM1_CCER1_CC1E =0;
			TIM1_CCER1_CC2E =1;
//--------------
			
			PC6_OUT=0;
			PC5_OUT=0;	
			PC7_OUT=1;
		}break;
//=========================
//==ca
		case 0x02:
		{	
/*			
         	 	TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;
			TIM1_CCER2_CC3NE=0;   						
			TIM1_CCER1_CC2NE =0;
			TIM1_CCER1_CC1NE =0;
*/
			TIM1_CCER1_CC1E =0;
			TIM1_CCER1_CC2E =0;
			TIM1_CCER2_CC3E=1;
 //--------------
			
			PC6_OUT=0;
			PC5_OUT=0;
			PC7_OUT=1;
    	    }break;
	 
//=========================
//==bc
		case 0x06:
		{
/*			
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;						
			TIM1_CCER2_CC3NE=0;   									
			TIM1_CCER1_CC2NE =0;			
			TIM1_CCER1_CC1NE =0;
*/
			TIM1_CCER2_CC3E=0;
			TIM1_CCER1_CC1E =0;
			TIM1_CCER1_CC2E =1;
//--------------
			
			PC6_OUT=0;
			PC7_OUT=0;
			PC5_OUT=1;
		}break;
//=========================
////1cb66
		case 0x04:
		{
/*			
			TIM1_CCMR1=0x68;
			TIM1_CCMR2=0x68;
			TIM1_CCMR3=0x68;	 			
			TIM1_CCER2_CC3NE=0;   								
			TIM1_CCER1_CC2NE =0;			
			TIM1_CCER1_CC1NE =0;
*/
			TIM1_CCER1_CC1E =0;
			TIM1_CCER1_CC2E =0;
			TIM1_CCER2_CC3E=1;
//---------------
			
			PC5_OUT=0;
			PC7_OUT=0;
			PC6_OUT=1;
		}break;
		
     		default:
	 	{
			DisAllPwmOut();  
		}break;
	}
	TIM1_EGR_COMG=1;
}

/*************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
*************************************************************/ 

u8 GetHall()
{
	u8 Now_Hall,loop,hall_temp;
	u8 Hallcheck_temp[7]={0,0,0,0,0,0};
	for(loop=0;loop<6;loop++)
	{ 
		Now_Hall=PA_IDR;
       	Now_Hall>>=1;
		switch(Now_Hall)// chiose 
		{   
			case  0x01: 
                   	{
				Hallcheck_temp[0]+=1;
                   	}break;
			
           		case  0x02: 
                   	{
				Hallcheck_temp[1]+=1;
			}break;
				
           		case  0x03: 
                   	{
				Hallcheck_temp[2]+=1;
			}break;
						   
			case  0x04: 
                  	{
				Hallcheck_temp[3]+=1;
			}break;
			
			case  0x05: 
                  	{
				Hallcheck_temp[4]+=1;
                    	}break;
			
			case  0x06: 
                   	{
				Hallcheck_temp[5]+=1;
			}break;
		}          
	}
	 
//-----------------------------------------
	hall_temp= Hallcheck_temp[0];
	for(loop=0;loop<7;loop++)
	{
		if(hall_temp<= Hallcheck_temp[loop])
		{ 
			hall_temp= Hallcheck_temp[loop];
			Now_Hall=loop+1;
		}
       }   
	return(Now_Hall);
}



/***********************************************************/

//============================================================
u8 Get_pa_vhl(void)
{
	u8 bufx;
	bufx=PA_IDR>>1;
	return(bufx);
}

//============================================================


void bskill_run()
{
	static unsigned short	BreakCnt = 0;
	Motordata.UI.BKcount+=1;
	DisAllPwmOut();
	
#ifdef	FUNC_BREAK_EN
	if( Motordata.UI.BKcount<116)
	{
		//PC6_OUT=0;
		//PC5_OUT=0;
		//PC7_OUT=0;

		PC6_OUT=1;
		PC5_OUT=1;
		PC7_OUT=1;
	}
	
	if( Motordata.UI.BKcount<190&&Motordata.UI.BKcount>116)
	{
		PC6_OUT=1;
		PC5_OUT=1;
		PC7_OUT=1;
	}
 
	if( Motordata.UI.BKcount>=190)
	{
		Motordata.UI.BKcount=0;
	}
#else
		PC6_OUT=0;
		PC5_OUT=0;
		PC7_OUT=0;

#endif
}


















