/**********************************************************
*name   : motor.c
*detail : motor入口主函数
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
param_t Motordata;
collect_t Injection;
/*  functions ----------------------------------------------------------------*/
//
void UIInit(void)
{
  Motordata.SWhkey.sakeyflg = 0;
  Motordata.SWhkey.sskey = 0;
  Motordata.SWhkey.swkey = 0;
  Adc_Scan_timetrig_init();
  TIM5_Ready_StartCount();
  Adc_Start();
	 
  Motordata.SWhkey.ONbuf = 0;
  Motordata.SWhkey.OFbuf = 0;
  GPIOD->ODR &= 0xeb;   // PD4_OUT=0; PD2_OUT=0;
  
  //Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
  dlay(50000);
  Motordata.UI.bkcount = 0;
  Motordata.UI.adspeedt = 3;
  Motordata.UI.blink = 0;	
  // 
  if(Get_sw_fr()==0) Motordata.MFR = SW_POS;	//CW	
  else Motordata.MFR = SW_REVS;			//CCW
                                              
  Motordata.UI.MFRch = Motordata.MFR;
  GPIOD->ODR |= 0x04;   // PD2_OUT=1;
  Motordata.SWhkey.TRdelay = PWR_DELAY_TIME;
  Motordata.prct.clcount = 0;
  Motordata.Disstatus = 6;
  Motordata.prct. DIStp = 0;
  Motordata.prct.DISvsm = 0;
  Motordata.prct.DISism = 0;
  Motordata.prct.DISois = 0;	 
  Motordata.UI.roller = 450;
  read_eeprom_vla();
#ifdef PROJ_SST16_195
  Motordata.SWhkey.FRstop=0xaa;
#endif
}

//
void MotorInit(void)
{
  Motordata.station= Ready;
  Adc_SetUp_Init();
  EnIRQ();      rim();
  UIInit();
  Motordata.Dswitch = MOTOR_OFF;
}

//void FScan_disply(void)
//{}
/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/