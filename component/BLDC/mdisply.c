/**********************************************************
*name:  public.h
*version: v1.0 (2018-4-1)
*detail:  include public head file
*author:  王元
***********************************************************/

#include "public.h"
#include "gpio.h"
#include "param.h"
#include "mc_control.h"
#include "mdisply.h"
#include "mswitch.h"
u8  rdkey;


/***************************************************
*代码段名称：
*使用范围  ：
*---------------------------------------------------
*描述：
****************************************************/
const  uint8_t  showsp[]={0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0};

//==================================
//all off
void FScan_fof()
{          
#if 0
	LED4=0;
	SW1=0;
	SW2=0;
	LED3=0;
	LED2=0;
	LED1=0;
#endif
}


//==================================
//all on
void FScan_fon()
{           
#if 0
	LED4=0;
	SW1=0;
	SW2=0;
	LED3=1;
	LED2=1;
	LED1=1;
#endif
}


//==========================================================
//
void FScan_led4()
{
#if 0
//led4 seg on
	LED4=0;
	SW1=1;
	SW2=1;
//com off
	LED1=0;
	LED2=0;
	LED3=0;
#endif
//-----------------------------
#ifdef	PROJ_SST16_194
//电量cap 3
	if(Motordata.batpower>=4)
	{
		LED3=1;
	}
#endif	

#ifdef	PROJ_SST17_1A4
//电量cap 3
	if(Motordata.batpower>=4)
	{
//		LED2=1;
	}
#endif

#ifdef	PROJ_SST17_DK
//电量cap 3
	if(Motordata.batpower>=4)
	{
		LED1=1;
	}
#endif


#ifdef	PROJ_SST17_1A1
//电量cap 3
	if(Motordata.batpower>=4)
	{
		LED2=1;
	}
#endif
#ifdef	PROJ_SST16_195
			if( Motordata.swhkey.mgear == 1)
			{	
				LED1=1;	
			}
#endif

//-----------------------------	
//speed grade display and rev display
	switch(Motordata.mfr)
	{
//--------------------------------
		case  DIR_POS:			//CW
		{
#ifdef	PROJ_SST16_194			
			if( Motordata.swhkey.mgear>=1)
			{	
				LED1=1;	
			}
			if( Motordata.swhkey.mgear>=4)
			{	 
				LED2=1;		
			}	
#endif



#ifdef	PROJ_SST17_1A4
			if( Motordata.swhkey.mgear==3)		////>=3////==2
			{	
//				LED1=1;			//H
			}
			
#endif		 

#ifdef	PROJ_SST17_DK
			if( Motordata.swhkey.mgear ==2)		////>=3////==2
			{	
				LED2=1;			//H
			}
#endif	

#ifdef	PROJ_SST17_1A1	
			if( Motordata.swhkey.mgear>=1)		
			{	
				LED1=1;			//L
			}


#endif

		}break;
//-------------------------------					 
		case  DIR_REVS:			//CCW
		{
			
#ifdef	PROJ_SST17_1A4
			if( Motordata.swhkey.frstop==0xAA)
			{  
//				LED3=1;
			}
#endif

#ifdef	PROJ_SST17_DK
			if( Motordata.swhkey.frstop==0xAA)
			{  
				LED3=1;
			}
#endif

#ifdef	PROJ_SST17_1A1	



#endif
		}break;
			
			
	}
		         
}


//====================================================
//
void FScan_sw1()
{
#if 0
//sw1 seg on
	LED4=1;
	SW1=0;
	
	SW2=1;
//com off
	LED1=0;
	LED2=0;
	LED3=0;
//scan key sw1			 
	rdkey=PD_IDR&0x02;
#endif
	if(rdkey==0)
	{
		Motordata.swhkey.spkey=1;
	}
	if(rdkey==0x02)
	{
		Motordata.swhkey.spkey=0;
	} 

	
//---------------------
#ifdef	PROJ_SST16_194
//电量cap2
	if(Motordata.batpower>=3)
	{
		LED3=1;
	}	
#endif	
//---------------------
#ifdef	PROJ_SST17_1A4
//电量cap2
	if(Motordata.batpower>=3)
	{
//		LED2=1;
	}	
#endif

#ifdef	PROJ_SST17_DK
//电量cap2
	if(Motordata.batpower>=3)
	{
		LED1=1;
	}	
#endif
//---------------------
#ifdef	PROJ_SST17_1A1
//电量cap2
	if(Motordata.batpower>=3)
	{
		LED2=1;
	}	
#endif
//-----------------

#ifdef	PROJ_SST16_195
			if( Motordata.swhkey.mgear == 2)
			{	
				LED1=1;	
			}
#endif

//-------------------------	
//speed grade display and rev display
	switch(Motordata.mfr)
	{
//-------------------------------		
		case  DIR_POS:			//CW
		{
#ifdef	PROJ_SST16_194			
			if( Motordata.swhkey.mgear>=2)
			{	 
				LED1=1;	
			}
			if( Motordata.swhkey.mgear>=5)
			{	 
				LED2=1;		
			}
#endif


#ifdef	PROJ_SST17_1A4
			if(Motordata.swhkey.mgear==2)		//>=////==
			{
//				LED1=1;		//M	//
			}	
#endif

#ifdef	PROJ_SST17_DK
			//if(Motordata.swhkey.mgear>=2)		//>=////==
			{
				//LED2=1;		//M	//
			}	
#endif

#ifdef	PROJ_SST17_1A1	
			if(Motordata.swhkey.mgear>=2)		
			{
				LED1=1;		//H	
			}	


#endif
		}break;
//-------------------------------					 
		case  DIR_REVS:		//CCW
		{ 
#ifdef	PROJ_SST17_1A4	



#endif

#ifdef	PROJ_SST17_1A4	



#endif

#ifdef	PROJ_SST17_DK	



#endif
		}break;		
	}//switch  end-----
		     				 

			 
}	


//====================================================	
//
void FScan_sw2()
{
#if 0
//sw2 seg on
	LED4=1;
	SW1=1;
	SW2=0;
//com off	
	LED1=0;	
	LED2=0;	
	LED3=0;  
//scan key sw2	
			
	rdkey=PD_IDR&0x02;
#endif
	if(rdkey==0)
	{
		Motordata.swhkey.readkey=2;
	}
	if(rdkey==0x02)
	{
		Motordata.swhkey.readkey=0;
	} 
	
//------------------
#ifdef	PROJ_SST16_194	
//电量cap1
	if(Motordata.batpower>=2)
	{
		LED3=1;
	}
#endif

//------------------
#ifdef	PROJ_SST17_1A4	
//电量cap1
	if(Motordata.batpower>=2)
	{
//		LED2=1;
	}
#endif
//------------------
#ifdef	PROJ_SST17_DK	
//电量cap1
	if(Motordata.batpower>=2)
	{
		LED1=1;
	}
#endif
//------------------
#ifdef	PROJ_SST17_1A1	
//电量cap1
	if(Motordata.batpower>=2)
	{
		LED2=1;
	}
#endif
//-------------------------
//speed grade display and rev display
	switch(Motordata.mfr)
	{
//-------------------------------		
		case  DIR_POS:		//CW
		{
#ifdef	PROJ_SST16_194				
			if( Motordata.swhkey.mgear>=3)
			{	 
				LED1=1;	
			} 
#endif

#ifdef	PROJ_SST17_1A4	
			if( Motordata.swhkey.mgear==1)	//>=	////==
			{	 
//				LED1=1;			//L
			} 
#endif

#ifdef	PROJ_SST17_DK	
			if( Motordata.swhkey.mgear==1)	//>=	////==
			{	 
				LED2=1;			//L
			} 
#endif

#ifdef	PROJ_SST17_1A1	



#endif


		}break;
//-------------------------------					 
		case  DIR_REVS:			//CCW
		{ 
#ifdef	PROJ_SST16_194	
			if( Motordata.swhkey.frstop==0xAA)
			{  
				LED2=1;
			}
#endif
#ifdef	PROJ_SST17_1A4	



#endif
#ifdef	PROJ_SST17_1A1	
			if( Motordata.swhkey.frstop==0xAA)
			{  
				LED1=1;
			}


#endif			
		}break;		
	}//switch  end-----
				
}		 
		 
//====================================================
//
void FScan_disply()
{
	
	POWER_dis_prc();
	 
	switch(Motordata.disstatus)
	{
//==led4 	
       	case 1:
		{	
			FScan_led4();
		}break;
//			 
		case 2:
		{	
			FScan_fof();
		}break;
		
//sw1====				 
		case 3:
		{ 
			FScan_sw1();
			 
		}break;
//			 
		case 4:
		{	
			FScan_fof(); 
		}break;	 
//sw2====				 
		case 5:
		{	 
			FScan_sw2();
		}break;
//							
		case 6:
		{	
			FScan_fof(); 
		}break;			
	}
}












/***********************************************************
* 函数名称  : void MCTask_Ready()
* 参数描述  : 无
* 返回值    : 无
* 描述      :     
***********************************************************/
//
void  Disp_error_on()
{
//
	switch(Motordata.disstatus)
	{
		case 1:
		case 3:	
		case 5:	
		{
			FScan_fon();
		}break;
//
		case 2:
		case 4:	
		case 6:	
		{
         		FScan_fof();
		}break;
	}
}


/******************************************
*
*
******************************************/
void  Disp_error_of()
{

         FScan_fof();
				 
}



void eeprom_openlock()
{
#if 0
  do

  {
    FLASH_DUKR = 0xae; // 写入第一个密钥

    FLASH_DUKR = 0x56; // 写入第二个密钥

  } while((FLASH_IAPSR & 0x08) == 0); // 若解锁未成功，则重新再来

//*p = 0xaa; // 写入第一个字节
#endif
}
/*************************************************
*
*
*
**************************************************/

void eeprom_w_char()
{
  u8 *padr_swbut;

  u8 *padr_rrstop;
	
  padr_rrstop=(u8*)0x4011;
	
  *padr_rrstop=0x41;
}









/********************************************************
 Motordata.prct.Volt
**********************************/
void  POWER_dis_prc()
{
#if 0
  if( Motordata.prct.disv<=BAT_VOLT1_ADC)
  { Motordata.batpower=1;}
  if( Motordata.prct.disv>BAT_VOLT1_ADC&&Motordata.prct.disv<=BAT_VOLT2_ADC)
  {  Motordata.batpower=2;}
  if( Motordata.prct.disv>BAT_VOLT2_ADC&&Motordata.prct.disv<=BAT_VOLT3_ADC)
  { Motordata.batpower=3;}
  if( Motordata.prct.disv>BAT_VOLT3_ADC)
  {  Motordata.batpower=4;}
#endif
 //===============================
}






