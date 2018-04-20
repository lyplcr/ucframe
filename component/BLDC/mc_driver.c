/**********************************************************
*name:  public.h
*version: v1.0 (2018-4-1)
*detail:  include public head file
*author:  王元
***********************************************************/


#include "mc_driver.h"
#include "param.h"
#include "common.h"
//#include "tim.h"
//#include "param.h"

/***********************************************
*#didine
***********************************************/
char vtale[2][3]={{1,2,3},{3,4,5}};
uint8_t check_step;
uint8_t check_table[]={0,0,0};


/************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
**************************************************/

void ChangeDuty(uint16_t pwm_value)
{
#if 0
	uint8_t CCRH,CCRL;
        
	if(pwm_value>PWM_PERIOD) 
	{
		pwm_value=PWM_PERIOD;
	}
	CCRH=(uint8_t)(pwm_value >> 8);
	CCRL=(uint8_t)(pwm_value);
//	
	TIM1_CCR1H =CCRH;
	TIM1_CCR1L =CCRL;
	TIM1_CCR2H =CCRH;
	TIM1_CCR2L =CCRL;
	TIM1_CCR3H =CCRH;
	TIM1_CCR3L =CCRL;
	
	pwm_value+=100;
	pwm_value=pwm_value>>1;
	CCRH=(uint8_t)(pwm_value >> 8);
	CCRL=(uint8_t)(pwm_value);
	TIM1_CCR4H =CCRH;
	TIM1_CCR4L =CCRL;
#endif
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
#if 0
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
#endif
}

/*************************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
*************************************************************/ 

uint8_t GetHall()
{
  uint8_t Now_Hall,loop,hall_temp;
  uint8_t Hallcheck_temp[7]={0,0,0,0,0,0};

  for(loop=0;loop<6;loop++)
  { 
#if 0
    Now_Hall=PA_IDR;
#endif
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
uint8_t Get_pa_vhl(void)
{
	uint8_t bufx;
//	bufx=PA_IDR>>1;
	return(bufx);
}

//============================================================


void bskill_run()
{
#if 0
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
#endif
}


















