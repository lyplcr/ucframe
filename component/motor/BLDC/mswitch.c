/**********************************************************
*name   : mswitch.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "gpio.h"
//#include "adc.h"
#include "mswitch.h"
#include "mc_control.h"
#include "param.h"
#include "mdisply.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
u16 sw_count=0;
uint8_t adc_sflg=0;
const unsigned short EVERY_GRADE_PWM_MAX_TAB[] =
{
	0,
	GRADE1_PWM_MAX,
	GRADE2_PWM_MAX,
	GRADE3_PWM_MAX,
	GRADE4_PWM_MAX,
	GRADE5_PWM_MAX,
	GRADE6_PWM_MAX,
	GRADE7_PWM_MAX,
	GRADE8_PWM_MAX

};

const unsigned short EVERY_GRADE_PWM_REVS_MAX_TAB[] =
{
	0,
	GRADE1_PWM_REVS_MAX,
	GRADE2_PWM_REVS_MAX,
	GRADE3_PWM_REVS_MAX,
	GRADE4_PWM_REVS_MAX,
	GRADE5_PWM_REVS_MAX,
	GRADE6_PWM_REVS_MAX,
	GRADE7_PWM_REVS_MAX,
	GRADE8_PWM_REVS_MAX

};

const unsigned short EVERY_GRADE_LIMIT_CURR_TAB[] =
{
	0,
	LIMIT_CURR1_VOLT_ADC,
	LIMIT_CURR2_VOLT_ADC,
	LIMIT_CURR3_VOLT_ADC
};

/*  functions ----------------------------------------------------------------*/


/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


void MC_Swbut_Check()
{
	uint8_t readkey=0;
	uint8_t *padr_rrstop;	
	uint8_t kxc;
//===getadc switch======
	sw_count++;
	if(sw_count>=100)
	{
		sw_count=0;
//===========================================================
//REV KEY PRESS  
#ifdef	PROJ_SST16_195
		Motordata.SWhkey.FRstop = 0xaa;
#else
		 //if(Motordata.SWhkey.readkey==1)
		 if(Motordata.SWhkey.readkey==2)	
		{
			if(Motordata.SWhkey.SWkey<20)
			{
				Motordata.SWhkey.SWkey+=1;									 													 
			}	
			if(Motordata.SWhkey.SWkey==18)	
			{							
				Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;									 
				if(Motordata.MFR==DIR_REVS  )		//CCW
				{ 
					Motordata.SWhkey.FRstop=~Motordata.SWhkey.FRstop;
					//Motordata.SWhkey.FRstop = 0xaa;
//														 							   
					eeprom_openlock();
					padr_rrstop=(uint8_t *)0x4022;
					*padr_rrstop=Motordata.SWhkey.FRstop;
                                        FLASH->IAPSR &= (uint8_t)0xf7;  // FLASH_IAPSR &= (uint8_t)0xF7;
					
				}		
			}																				
		}
//=====================											
		if(Motordata.SWhkey.readkey==0)
		{
			Motordata.SWhkey.SWkey=0;						 									 
		}
#endif
//---------------------------------------------------					 
//SPEED KEY PRESS	
		
		if(Motordata.SWhkey.spkey==1)
		//if(Motordata.SWhkey.spkey==2)	
		{
			if(Motordata.SWhkey.SSkey<20)
			{
				Motordata.SWhkey.SSkey+=1;
			}	
                    	if(Motordata.SWhkey.SSkey==18)	
			{		
				Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
#ifdef	PROJ_SST16_195

#else
				if(Motordata.MFR==DIR_POS)		//CW
#endif					
				{	 
					//Motordata.SWhkey.Mgear=~Motordata.SWhkey.Mgear;	
///////////////////////modify by goldjun//////////////////////////					
					Motordata.SWhkey.Mgear++;
					if(Motordata.SWhkey.Mgear > SPEED_GRADE_MAX)
					{
						Motordata.SWhkey.Mgear = SPEED_GRADE_MIN;
					}
					
					Motordata.UI.Gduty = EVERY_GRADE_PWM_MAX_TAB[Motordata.SWhkey.Mgear];
///////////////////////modify by goldjun//////////////////////////					
					/*
					if( Motordata.SWhkey.Mgear==0xdd)
					{
						Motordata.UI.Gduty=1270;
					}
					if( Motordata.SWhkey.Mgear==0x22)
					{ 
						Motordata.UI.Gduty=700;
					}
					*/
					eeprom_openlock();
                              	padr_rrstop=(uint8_t *)0x4028;
                             	*padr_rrstop=Motordata.SWhkey.Mgear;
                                FLASH->IAPSR &= (uint8_t)0xf7;  // FLASH_IAPSR &= (uint8_t)0xF7;
					
				}	
//one key two function
#ifdef	PROJ_SST16_195
				Motordata.SWhkey.FRstop = 0xaa;
#else
				if(Motordata.MFR==DIR_REVS)		//CCW
				{ 
					Motordata.SWhkey.FRstop=~Motordata.SWhkey.FRstop;
//														 							   
					eeprom_openlock();
					padr_rrstop=(uint8_t *)0x4022;
					*padr_rrstop=Motordata.SWhkey.FRstop;
                                        FLASH->IAPSR &= (uint8_t)0xf7;  // FLASH_IAPSR &= (uint8_t)0xF7;
					
				}

#endif				
			}
		}		 
//=====================		
		if(Motordata.SWhkey.spkey==0)
		{
			Motordata.SWhkey.SSkey=0;						 
		}
	}

	
}//func--end--------------------------
//=====================================

uint8_t Get_sw_fr(void)
{
  uint8_t buf;
  
  buf = GPIOD->IDR & 0x80;      // buf=PD_IDR&0x80;
        
  if (buf==0)
  {
    return(0);
  }
  else
  {
    return(1);
  }	
}


//=============================================
void Get_adc_sw(void)
{

}

void Get_adc_vl(void)
{
  Motordata.hopeduty = (ADC1->DRH<<8)+ADC1->DRL;        // Motordata.hopeduty=ADC_DR;
}

/************************************************/
void Check_switch_onff()
{
//--------------------------------------
	if(Motordata.hopeduty>SDSWITCH_MIN_ON)
	{
		Motordata.SWhkey.OFbuf=0;
		Motordata.SWhkey.ONbuf+=1;
		if( Motordata.SWhkey.ONbuf>1000)	//10	
		{	
	      		Motordata.Dswitch=MOTOR_ON;
			Motordata.SWhkey.ONbuf=0;		
		}
	}
//--------------------------------------
	if(Motordata.hopeduty<SDSWITCH_MIN_OFF )
	{
		Motordata.SWhkey.ONbuf=0;
		Motordata.SWhkey.OFbuf+=1;
		if( Motordata.SWhkey.OFbuf>1000)	//10
		{	 
			Motordata.Dswitch=MOTOR_OFF;
			Motordata.SWhkey.OFbuf=0;
		}
    	}

}

/*******************************************************/

///////////////////////modify by goldjun//////////////////////////
//#define	FUNC_TEMP_DETECT_MODE_EN

#define	MOS_TEMP_85_PROTECT		130
#define	MOS_TEMP_90_PROTECT		115
#define	MOS_TEMP_95_PROTECT		102
#define	MOS_TEMP_100_PROTECT		91

#ifdef	FUNC_TEMP_DETECT_MODE_EN
//	

const unsigned short MOS_TEMP_TAB[] =
{
//0
		749, 
		740, 
		731, 
		722, 
		713, 
		704, 
		695, 
		685, 
		676, 
		667, 
		657, 
		648, 
		638, 
		628, 
		618, 
		609, 
		599, 
		589, 
		579, 
		570, 
		560, 
		550, 
		540, 
		531, 
		521, 
		512, 
		502, 
		492, 
		483, 
		474, 
		464, 
		455, 
		446, 
		437, 
		428, 
		419, 
		410, 
		402, 
		393, 
		385, 
		377, 
		368, 
		360, 
		352, 
		345, 
		337, 
		329, 
		322, 
		315, 
		308, 
		301, 
		294, 
		287, 
		280, 
		274, 
		267, 
		261, 
		255, 
		249, 
		243, 
		237, 
		232, 
		226, 
		221, 
		216, 
		210, 
		205, 
		200, 
		196, 
		191, 
		186, 
		182, 
		178, 
		173, 
		169, 
		165, 
		161, 
		157, 
		153, 
		150, 
		146, 
		143, 
		139, 
		136, 
		133, 
//85		
		130, 
		126, 
		124, 
		121, 
		118, 
//90		
		115, 
		112, 
		110, 
		107, 
		104, 
//95		
		102, 
		100, 
		97,
		95,
		93,
//100		
		91,
		89,
		87,
		85,
		83,
		81,
		79,
		77,
		75,
		74,
		72,
		70,
		69,
		67,
		66,
		64,
};

//
const unsigned short MOSADDBAT_TEMP_TAB[] =
{
//0
		757, 
		749, 
		741, 
		732, 
		724, 
		715, 
		707, 
		698, 
		690, 
		681, 
		672, 
		663, 
		654, 
		646, 
		637, 
		628, 
		619, 
		610, 
		601, 
		592, 
		584, 
		575, 
		566, 
		557, 
		549, 
		540, 
		532, 
		523, 
		515, 
		507, 
		498, 
		490, 
		482, 
		474, 
		467, 
		459, 
		451, 
		444, 
		436, 
		429, 
		422, 
		415, 
		408, 
		401, 
		394, 
		388, 
		381, 
		375, 
		369, 
		363, 
		357, 
		351, 
		345, 
		339, 
		334, 
		328, 
		323, 
		318, 
		313, 
		308, 
		303, 
		298, 
		294, 
		289, 
		285, 
		281, 
		276, 
		272, 
		268, 
		264, 
		261, 
		257, 
		253, 
		250, 
		246, 
		243, 
		240, 
		237, 
		233, 
		230, 
		227, 
		225, 
		222, 
		219, 
		216, 
		214, 
		211, 
		209, 
		206, 
		204, 
		202, 
		200, 
		197, 
		195, 
		193, 
		191, 
		189, 
		187, 
		186, 
		184, 
		182, 
		180, 
		179, 
		177, 
		175, 
		174, 
		172, 
		171, 
		170, 
		168, 
		167, 
		165, 
		164, 
		163, 
		162, 
		161, 
};

#endif

///////////////////////modify by goldjun//////////////////////////


////////////////////////////////////////////////////////////////////////
void check_erorr()
{
	static unsigned char MosRealTemp= 0;
	unsigned short MosAddBatTempVal = 0;
//Motordata.prct.Anp 
//===============================
//ov
#ifdef	FUNC_OV_PROTECT_EN
	if(Motordata.prct.DISv>OVP_VOLT_ADC)
	{
		Motordata.fault=eOvp;
		Motordata.station=Stop;
		Motordata.UI.Blink=5;
	}
#endif

//===============================	
//uv	
#ifdef	FUNC_UV_PROTECT_EN
	if(Motordata.prct.DISv<UVP_VOLT_ADC)		//365
	{
		Motordata.fault=elvp;
		Motordata.station=Stop;
		Motordata.UI.Blink=7;
	}
#endif
//===============================		
//Motordata.prct.DIStp
#ifdef	FUNC_MOSOT_PROTECT_EN	
//ot
	if(Motordata.prct.DIStp<OTP_VOLT_ADC)
	{
		Motordata.fault=eOct;
		Motordata.station=Stop;
		Motordata.UI.Blink=1;
	}
#endif
///////////////////////modify by goldjun//////////////////////////

#ifdef	FUNC_TEMP_DETECT_MODE_EN

//===============================
//detect mos temp protect dot advalue
//85
	if(Motordata.prct.MosTemp < MOS_TEMP_85_PROTECT)
	{
		Motordata.fault=eOct;
		Motordata.station=Stop;
		Motordata.UI.Blink=4;
	}
//===============================	
//crc mos real temp
	for(MosRealTemp = 0;MosRealTemp < 115;MosRealTemp ++)
	{
		if(Motordata.prct.MosTemp > MOS_TEMP_TAB[MosRealTemp])
		{
			break;
		}
	}
//===============================	
//crc mos add bat protect dot advalue	
	MosAddBatTempVal = MOSADDBAT_TEMP_TAB[MosRealTemp];


//===============================
//70	
//detect mos add bat temp protect dot advalue
	if( Motordata.prct.MosAddBatTemp < MosAddBatTempVal)
	{
		Motordata.fault=eOct;
		Motordata.station=Stop;
		Motordata.UI.Blink=2;
	}
#endif	
///////////////////////modify by goldjun//////////////////////////
}


//
void read_eeprom_vla(void)
{
  uint8_t *padr_sstp;
		 
//		
	eeprom_openlock();
	padr_sstp=(uint8_t *)0x4022;

	Motordata.SWhkey.FRstop= *padr_sstp;
	if((Motordata.SWhkey.FRstop != 0XAA)&&(Motordata.SWhkey.FRstop != 0X55))
	{
		Motordata.SWhkey.FRstop = 0XAA;
	}
													 
	padr_sstp=(uint8_t *)0x4028;												 
															 
	Motordata.SWhkey.Mgear= *padr_sstp;
	
	/*	
	if( Motordata.SWhkey.Mgear==0xdd)
													       
		  { Motordata.UI.Gduty=1270;}
	if( Motordata.SWhkey.Mgear==0x22)
			{ Motordata.UI.Gduty=700;}
	*/
///////////////////////modify by goldjun//////////////////////////	
	if((Motordata.SWhkey.Mgear < SPEED_GRADE_MIN)||(Motordata.SWhkey.Mgear > SPEED_GRADE_MAX))
	{
		Motordata.SWhkey.Mgear = SPEED_GRADE_MAX;
	}
	Motordata.UI.Gduty= EVERY_GRADE_PWM_MAX_TAB[Motordata.SWhkey.Mgear];
///////////////////////modify by goldjun//////////////////////////
        FLASH->IAPSR &= (uint8_t)0xf7;  // FLASH_IAPSR &= (uint8_t)0xF7;
}

// 
void   Motor_ip(void)
{
//
#ifdef	FUNC_SOC_PROTEC_EN
	if (Motordata.prct.Anp>OCP_VOLT_ADC)
	{
		Motordata.prct.DISism++;
	}
	if (Motordata.prct.Anp<=OCP_VOLT_ADC)
	{ 	 
		Motordata.prct.DISism=0; 
	}
/****************************************
*500-2.5v=10a
*550-2.75=12
*
**************************************/
	if(Motordata.prct.DISism>200)
	{
		Motordata.fault=eOcp;
		Motordata.prct.DISism=0;
		Motordata.station=Stop;
		Motordata.UI.Blink=9;
	}

#endif
}


void   Motor_Limit_Curr(void)
{
#ifdef	FUNC_LIMIT_CURR_EN

	static unsigned short Limit_Curr_CntOn = 0;
	static unsigned short Limit_Curr_CntOff = 0;	
	static unsigned short Pwm_Max_Value = 0;
	static unsigned short Limit_Curr = 0;	
//set max pwm value	
	Pwm_Max_Value = EVERY_GRADE_PWM_MAX_TAB[Motordata.SWhkey.Mgear];
	if(Motordata.MFR==DIR_REVS)
	{
		Pwm_Max_Value = EVERY_GRADE_PWM_REVS_MAX_TAB[Motordata.SWhkey.Mgear];
	}

//
	//Limit_Curr = LIMIT_CURR_VOLT_ADC;

	Limit_Curr = EVERY_GRADE_LIMIT_CURR_TAB[Motordata.SWhkey.Mgear];

//	
	if(Motordata.MFR==DIR_REVS)
	{
		Limit_Curr = LIMIT_CURR_VOLT_ADC + 10;
	}
//限流功能
	if(Motordata.prct.Anp > Limit_Curr)
	{
		Limit_Curr_CntOff = 0;
		Limit_Curr_CntOn ++;
		if(Limit_Curr_CntOn > 10)	//10
		{
			Limit_Curr_CntOn = 0;			
			Motordata.UI.Gduty -= 3;			
		}

	}
//限流恢复	
	else if(Motordata.prct.Anp < (Limit_Curr-10))
	{
		Limit_Curr_CntOn = 0;
		Limit_Curr_CntOff ++;
		if(Limit_Curr_CntOff > 5)
		{
			Limit_Curr_CntOff = 0;
			if(Motordata.UI.Gduty < Pwm_Max_Value)
			{
				Motordata.UI.Gduty ++;

			}
		}

	}
	else
	{
		Limit_Curr_CntOn = 0;
		Limit_Curr_CntOff = 0;
	}
	
#endif

}