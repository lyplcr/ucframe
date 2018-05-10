/**********************************************************
*name   : mc_diver.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "tim.h"
#include "mc_driver.h"
#include "param.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
char vtale[2][3]={{1,2,3},{3,4,5}};
uint8_t check_step;
uint8_t check_table[]={0,0,0};

/*  functions ----------------------------------------------------------------*/


/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/

/************************************************
* 函数名称: 
* 版本号:   v1.0
* 参数描述: 无
* 返回值:   无
* 描述:     
**************************************************/

void ChangeDuty(uint16_t pwm_value)
{
  uint8_t CCRH,CCRL;
  
  if(pwm_value>PWM_PERIOD) 
  {
    pwm_value=PWM_PERIOD;
  }
  CCRH=(uint8_t)(pwm_value >> 8);
  CCRL=(uint8_t)(pwm_value);
  //	
  TIM1->CCR1H = CCRH;
  TIM1->CCR1L = CCRL;
  TIM1->CCR2H = CCRH;
  TIM1->CCR2L = CCRL;
  TIM1->CCR3H = CCRH;
  TIM1->CCR3L = CCRL;

  pwm_value+=100;
  pwm_value=pwm_value>>1;
  CCRH=(uint8_t)(pwm_value >> 8);
  CCRL=(uint8_t)(pwm_value);
  TIM1->CCR4H = CCRH;
  TIM1->CCR4L = CCRL;
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
  TIM1->CCMR1=0x68;
  TIM1->CCMR2=0x68;        
  TIM1->CCMR3=0x68;
  TIM1->CCER2 &= 0xfb;  // TIM1_CCER2_CC3NE=0; 	
  TIM1->CCER1 &= 0xbb;  // TIM1_CCER1_CC2NE =0;// TIM1_CCER1_CC1NE =0;
    
  switch(Motordata.mstep)
  {
//=======================	
//==ac
  case 0x05:
    {
//      TIM1_CCMR1=0x68;
//      TIM1_CCMR2=0x68;
//      TIM1_CCMR3=0x68;
//      TIM1_CCER2_CC3NE=0; 	
//      TIM1_CCER1_CC2NE =0;
//      TIM1_CCER1_CC1NE =0;	
      TIM1->CCER2 &= 0xfe;      // TIM1_CCER2_CC3E=0;	
      TIM1->CCER1 &= 0xef;      // TIM1_CCER1_CC2E =0;
      TIM1->CCER1 |= TIM1_CCER1_CC1E;      // TIM1_CCER1_CC1E =1;
//--------------		
      GPIOC->ODR &= 0x1f;       // PC6_OUT=0; PC7_OUT=0;
      GPIOC->ODR |= 0x20;       // PC5_OUT=1;
    }break;
//=======================	
//===ab66
  case 0x01:
    {		
//			TIM1_CCMR1=0x68;
//			TIM1_CCMR2=0x68;
//			TIM1_CCMR3=0x68;
//			TIM1_CCER2_CC3NE=0;   						
//			TIM1_CCER1_CC2NE =0;
//			TIM1_CCER1_CC1NE =0;	
      TIM1->CCER2 &= 0xfe;      // TIM1_CCER2_CC3E=0;
      TIM1->CCER1 &= 0xef;      // TIM1_CCER1_CC2E =0;
      TIM1->CCER1 |= TIM1_CCER1_CC1E;      // TIM1_CCER1_CC1E =1;
 //---------------
      GPIOC->ODR &= 0x1f;       // PC5_OUT=0; PC7_OUT=0; 
      GPIOC->ODR |= 0x40;       // PC6_OUT=1;
    }break;
				 
//=======================				
//==ba		
  case 0x03:
    {		
//      TIM1_CCMR1=0x68;
//      TIM1_CCMR2=0x68;
//      TIM1_CCMR3=0x68;			
//      TIM1_CCER2_CC3NE=0;   									
//      TIM1_CCER1_CC2NE =0;
//      TIM1_CCER1_CC1NE =0;
      TIM1->CCER2 &= 0xfe;      // TIM1_CCER2_CC3E=0;
      TIM1->CCER1 &= 0xfe;      // TIM1_CCER1_CC1E =0;
      TIM1->CCER1 |= TIM1_CCER1_CC2E;      // TIM1_CCER1_CC2E =1;
//--------------
      GPIOC->ODR &= 0x1f;       // PC6_OUT=0; PC5_OUT=0;
      GPIOC->ODR |= 0x80;       // PC7_OUT=1;
    }break;
//=========================
//==ca
  case 0x02:
    {			
//      TIM1_CCMR1=0x68;
//      TIM1_CCMR2=0x68;
//      TIM1_CCMR3=0x68;
//      TIM1_CCER2_CC3NE=0;   						
//      TIM1_CCER1_CC2NE =0;
//      TIM1_CCER1_CC1NE =0;
      TIM1->CCER1 &= 0xee;      // TIM1_CCER1_CC1E =0; TIM1_CCER1_CC2E =0;
      TIM1->CCER2 |= TIM1_CCER2_CC3E;      // TIM1_CCER2_CC3E=1;
 //--------------
      GPIOC->ODR &= 0x1f;       // PC6_OUT=0; PC5_OUT=0;
      GPIOC->ODR |= 0x80;       // PC7_OUT=1;
    }break;
	 
//=========================
//==bc
  case 0x06:
    {		
//      TIM1_CCMR1=0x68;
//      TIM1_CCMR2=0x68;
//      TIM1_CCMR3=0x68;						
//      TIM1_CCER2_CC3NE=0;   									
//      TIM1_CCER1_CC2NE =0;			
//      TIM1_CCER1_CC1NE =0;
      TIM1->CCER2 &= 0xfe;      // TIM1_CCER2_CC3E=0;
      TIM1->CCER1 &= 0xfe;      // TIM1_CCER1_CC1E =0;
      TIM1->CCER1 |= TIM1_CCER1_CC2E;      // TIM1_CCER1_CC2E =1;
      //--------------
      GPIOC->ODR &= 0x1f; // PC6_OUT=0; PC7_OUT=0;
      GPIOC->ODR |= 0x20; // PC5_OUT=1;      
    }break;
//=========================
////1cb66
  case 0x04:
  {			
//    TIM1_CCMR1=0x68;
//    TIM1_CCMR2=0x68;
//    TIM1_CCMR3=0x68;	 			
//    TIM1_CCER2_CC3NE=0;   								
//    TIM1_CCER1_CC2NE =0;			
//    TIM1_CCER1_CC1NE =0;
    TIM1->CCER1 &= 0xee;        // TIM1_CCER1_CC1E =0; TIM1_CCER1_CC2E =0;
    TIM1->CCER2 |= TIM1_CCER2_CC3E;        // TIM1_CCER2_CC3E=1;
//---------------
    GPIOC->ODR &= 0x1f; // PC5_OUT=0; PC7_OUT=0;
    GPIOC->ODR |= 0x40; // PC6_OUT=1;   
  }break;
		
  default:
    {
      DisAllPwmOut();  
    }break;
  }
  TIM1->EGR |= TIM1_EGR_COMG;
}

// 
uint8_t GetHall()
{
  uint8_t Now_Hall,loop,hall_temp;
  uint8_t Hallcheck_temp[7]={0,0,0,0,0,0};
  
  for(loop=0;loop<6;loop++)
  {
    Now_Hall = GPIOA->IDR >>1;    // Now_Hall=PA_IDR; Now_Hall>>=1;
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
  
  bufx = GPIOA->IDR>>1;         // bufx=PA_IDR>>1;
  return(bufx);
}

//============================================================


void bskill_run()
{
  static unsigned short	BreakCnt = 0;
  
  Motordata.UI.bkcount += 1;
  DisAllPwmOut();
	
#ifdef	FUNC_BREAK_EN
  if( Motordata.UI.bkcount < 116)
  {
    //PC6_OUT=0;
    //PC5_OUT=0;
    //PC7_OUT=0;
    GPIOC->ODR |= 0xe0; // PC6_OUT=1;  PC5_OUT=1;  PC7_OUT=1;
  }

  if( Motordata.UI.bkcount<190 && Motordata.UI.bkcount>116)
  {
    GPIOC->ODR |= 0xe0; //  PC6_OUT=1; PC5_OUT=1; PC7_OUT=1;
  }

  if( Motordata.UI.bkcount>=190)
  {
    Motordata.UI.bkcount=0;
  }
#else
  PC6_OUT=0;
  PC5_OUT=0;
  PC7_OUT=0;
#endif
}