/**********************************************************
*name   : main.c
*detail : 入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "board.h"
#include "motor.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
const mcu_t mcu =
{
  0x12345678,
  16000000,
  0x000000,
  1024*1,
  0X008080,
  1024*8,  
//  {'S','T','M','3','2','F','1','0'},    
};

/*  functions ----------------------------------------------------------------*/
//
void UIInit(void)
{
  Motordata.SWhkey.sakeyflg=0;
  Motordata.SWhkey.SSkey=0;
  Motordata.SWhkey.SWkey=0;
  Adc_Scan_timetrig_init();
  TIM5_Ready_StartCount();
  Adc_Start();
	 
  Motordata.SWhkey.ONbuf=0;
  Motordata.SWhkey.OFbuf=0;
  GPIOD->ODR &= 0xeb;   // PD4_OUT=0; PD2_OUT=0;
  
  //Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
//==============================
  dlay (50000);
  Motordata.UI.BKcount=0;
  Motordata.UI.adspeedt=3;
  Motordata.UI.Blink=0;	
	 
//========================
  if(Get_sw_fr()==0)	//=?ж??????==
  { 
    Motordata.MFR = SW_POS;			//CW		
  }
  if(Get_sw_fr()==1)
  { 
    Motordata.MFR = SW_REVS;			//CCW
  }//---------
                                              
  Motordata.UI.MFRch= Motordata.MFR;
  GPIOD->ODR |= 0x04;   // PD2_OUT=1;
  Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
  //?ж???????????============
  Motordata.prct.clcount=0;
  //===?????????????===========
  Motordata.Disstatus=6;
  //====================
  Motordata.prct. DIStp=0;
  Motordata.prct.DISvsm=0;
  Motordata.prct.DISism=0;
  Motordata.prct.DISois=0;
  //=============================	 
  //==??eeprom===================
  Motordata.UI.Mroller=450;
  read_eeprom_vla();
  #ifdef	PROJ_SST16_195
  Motordata.SWhkey.FRstop=0xaa;
  #endif   
}

// 
int main( void )
{
  uint8_t usx;
  
  BoardInit();
  LedOn();
  MotorInit();
  UIInit();
  Motordata.Dswitch = MOTOR_OFF;
  dlay(50000);
  LedOff();
  
  while (1)
  {
    //	MCTask_Start();
    Motor_ip();
    Check_switch_onff();

    if( Motordata.station==Stop&&Motordata.UI.Blink>0)   
    {     
      usx = showsp[Motordata.UI.showcount];
      if(usx==1)
      { 
        Disp_error_on();  
      }
      else
      { 
        Disp_error_of();  
      }	
    }

    Motor_Run();
  }
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/




