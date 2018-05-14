/**********************************************************
*name   : mdisply.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "public.h"
//#include "gpio.h"
#include "param.h"
#include "mc_control.h"
#include "mdisply.h"
#include "mswitch.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
uint8_t  rdkey;
const  uint8_t  showsp[]={0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0};

/*  functions ----------------------------------------------------------------*/

//all off
void FScan_fof(void)
{
  LED4L();      // LED4=0;
  SW1L();       // SW1=0;
  SW2L();       // SW2=0;
  LED3L();      // LED3=0;
  LED2L();      // LED2=0;
  LED1L();      // LED1=0;
}

//all on
void FScan_fon(void)
{
  LED4L();      // LED4=0;
  SW1L();       // SW1=0;
  SW2L();       // SW2=0;
  LED3H();      // LED3=1;
  LED2H();      // LED2=1;
  LED1H();      // LED1=1;
}

//==========================================================
//
void FScan_led4(void)
{
//led4 seg on
  LED4L();      // LED4=0;
  SW1H();       // SW1=1;
  SW2H();       // SW2=1;
//com off
  LED1L();      // LED1=0;
  LED2L();      // LED2=0;
  LED3L();      // LED3=0;

//电量cap 3
  if(Motordata.BatPower>=4)
  {
    LED2H();    // LED2=1;
  }

//speed grade display and rev display
  switch(Motordata.MFR)
  {
  case  DIR_POS:			//CW
  if( Motordata.SWhkey.gear==3)		////>=3////==2
    {	
      LED1H();        // LED1=1;			//H
    }	
    break;
  case  DIR_REVS:			//CCW
    if( Motordata.SWhkey.FRstop==0xAA)
    {  
      LED3H();        // LED3=1;
    }
    break;
  }		         
}

//
void FScan_sw1(void)
{
//sw1 seg on
  LED4H();      // LED4=1;
  SW1L();       // SW1=0;
  SW2H();       // SW2=1;
//com off
  LED1L();      // LED1=0;
  LED2L();      // LED2=0;
  LED3L();      // LED3=0;
//scan key sw1		
  rdkey = GPIOD->IDR&0x02;      // rdkey=PD_IDR&0x02;
  if(rdkey==0)
  {
    Motordata.SWhkey.spkey=1;
  }
  if(rdkey==0x02)
  {
    Motordata.SWhkey.spkey=0;
  } 

//电量cap2
  if(Motordata.BatPower>=3)
  {
    LED2H();      // LED2=1;
  }
  //speed grade display and rev display
  switch(Motordata.MFR)
  {
  case  DIR_POS:			//CW
    if(Motordata.SWhkey.gear==2)		//>=////==
    {
      LED1H();    // LED1=1;		//M	//
    }
    break;
  case  DIR_REVS:		//CCW
    break;
  }//switch  end-----
}	

//
void FScan_sw2(void)
{
  //sw2 seg on
  LED4H();      // LED4=1;
  SW1H();       // SW1=1;
  SW2L();       // SW2=0;
  //com off	
  LED1L();      // LED1=0;	
  LED2L();      // LED2=0;	
  LED3L();      // LED3=0;    	
  //scan key sw2	
  rdkey = GPIOD->IDR&0x02;      // rdkey=PD_IDR&0x02;
  if(rdkey==0)
  {
    Motordata.SWhkey.readkey=2;
  }
  if(rdkey==0x02)
  {
    Motordata.SWhkey.readkey=0;
  } 
  
//电量cap1
  if(Motordata.BatPower>=2)
  {
    LED2H();    // LED2=1;
  }
  
//speed grade display and rev display
  switch(Motordata.MFR)
  {	
  case  DIR_POS:		//CW
    if( Motordata.SWhkey.gear==1)	//>=
    {	 
      LED1H();      // LED1=1;			//L
    } 
    break;
  case  DIR_REVS:			//CCW
    break;
  }			
}		 

//
void FScan_disply(void)
{
  POWER_dis_prc();
  switch(Motordata.Disstatus)
  {
  case 1:
    FScan_led4();
    break;
  case 2:
    FScan_fof();
    break;
  case 3:
    FScan_sw1();
    break;
  case 4:
    FScan_fof(); 
    break;
  case 5:
    FScan_sw2();
    break;
  case 6:
    FScan_fof(); 
    break;
  }
}

//
void  Disp_error_on(void)
{
  switch(Motordata.Disstatus)
  {
    case 1:
    case 3:	
    case 5:
      FScan_fon();
      break;
    case 2:
    case 4:	
    case 6:	
      FScan_fof();
      break;
  }
}

//
void  Disp_error_of(void)
{
  FScan_fof();		 
}

void eeprom_openlock(void)
{
  do {
    FLASH->DUKR = 0xae; // FLASH_DUKR = 0xae; // 写入第一个密钥
    FLASH->DUKR = 0x56; // FLASH_DUKR = 0x56; // 写入第二个密钥  
  } while( (FLASH->IAPSR & 0X08) == 0 );//while((FLASH_IAPSR & 0x08) == 0); // 若解锁未成功，则重新再来
  //*p = 0xaa; // 写入第一个字节
}

// 
void eeprom_w_char(void)
{
//  uint8_t *padr_swbut;
  uint8_t *padr_rrstop;	
  
  padr_rrstop=(uint8_t*)0x4011;	
  *padr_rrstop=0x41;
}

/********************************************************
 Motordata.prct.Volt
**********************************/
void  POWER_dis_prc(void)
{
  if( Motordata.prct.DISv<=BAT_VOLT1_ADC)
  { 
    Motordata.BatPower=1;
  }
  if( Motordata.prct.DISv>BAT_VOLT1_ADC&&Motordata.prct.DISv<=BAT_VOLT2_ADC)
  {  
    Motordata.BatPower=2;
  }
  if( Motordata.prct.DISv>BAT_VOLT2_ADC&&Motordata.prct.DISv<=BAT_VOLT3_ADC)
  { 
    Motordata.BatPower=3;
  }
  if( Motordata.prct.DISv>BAT_VOLT3_ADC)
  {  
    Motordata.BatPower=4;
  }
}



/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


