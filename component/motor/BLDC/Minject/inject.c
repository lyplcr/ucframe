/*******************************coptright(c)***************************************
*
* --------------------  ShenZhen  pace  electronics  co.LTD  -------------------
*
*                             BLDC  energy  Team
*
*---file info----------------------------------------------------------------------
*
*  文件名称:	  inject.c
*  修改日期：     v1.0
*
**********************************************************************************/


#include "public.h"
#include "param.h"
#include "mc_driver.h"
#include "mc_control.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "inject.h"

///*
s16 inject_table[][]={ {0,0,0},
                       {0,0,0},
                       {0,0,0},
											 {0,0,0},
											 {0,0,0},
										 	 {0,0,0}
										 };
										 
u16  tb[]={0,0,0,0,0,0,0,0,0,0,0};
////////////////////////////////////////////////
//ac
void InJect_AC_Task(void)
{
	u8 count;
	u8 pccount=0;//------------------------------
	u16 collectf[]={0,0,0,0,0,0,0,0,0};
	u16 collectb[]={0,0,0,0,0,0,0,0,0};
 	s16 colee[]={0,0,0,0,0,0,0,0,0,0};
 
	//Adc_SetUp_ch2();
	Adc_SetUp_ch(BEMFB_ADC_CH);
	 //Adc_SetUp_ch(CURR_ADC_CH);
	 
//========================	 
//送相位-----
//CA
	PrcTask_Ph(2);//==
	dlay(WAIT_US_PULSE_ON_TIME);//====
	Adc_Start();	
	//------------------------------------------	 
	for(pccount=1;pccount<8;)
	{
		if( ADC_CSR_EOC==1)	
		{
			dlay(WAIT_ADC_SAMPLE_TIME);
			collectf[pccount]=ADC_DR;
			tb[pccount]=ADC_DR;
			pccount++;
			ADC_CSR_EOC=0;
			//PD7_OUT=~PD7_OUT;
			Adc_Start();	
		}
	 
	}
	
//-- ------------------------	 
	//PC_ODR=0x00;
	//dlay(WAIT_US_STEP_OFF_TIME);
//----------------------------


//========================
//AC
	PrcTask_Ph(1);
	dlay(WAIT_US_PULSE_ON_TIME);
	Adc_Start();	
	for(pccount=1;pccount<8;)
	{
		if( ADC_CSR_EOC==1)	
		{
			dlay(WAIT_ADC_SAMPLE_TIME);
			collectb[pccount]=ADC_DR;
			tb[pccount]=ADC_DR;
			pccount++;
			ADC_CSR_EOC=0;
			PD7_OUT=~PD7_OUT;
			Adc_Start();	
		}
	 
	}
//----------------------------------------	
	PC_ODR=0x00;
	Injection.ADC_inj_o = 0;
	Injection.ADC_inj_n = 0;
	Injection.ADC_inj_l = 0;
	Injection.ADC_inj_ne = 0;	
//----------------------------------------
	for(count=1;count<7;count++)
	{
		Injection.ADC_inj_o+=collectf[count];
		colee[count]=collectf[count]-collectf[count+1];
		Injection.ADC_inj_n+= colee[count];
	}
	Injection.ADC_inj_o=Injection.ADC_inj_o/6;
	Injection.ADC_inj_n=Injection.ADC_inj_n/6;
	inject_table[2][0]=Injection.ADC_inj_o;
	inject_table[2][1]=	Injection.ADC_inj_n;
				
  //------------------------------------------
	for(count=1;count<7;count++)
	{
		Injection.ADC_inj_l+=collectb[count];
		colee[count]=collectb[count]-collectb[count+1];
		Injection.ADC_inj_ne+= colee[count];
	}
	Injection.ADC_inj_l=Injection.ADC_inj_l/6;
	Injection.ADC_inj_ne=Injection.ADC_inj_ne/6;
	inject_table[3][0]=Injection.ADC_inj_l;
	inject_table[3][1]=Injection.ADC_inj_ne;
		
	dlay(WAIT_US_PULSE_OFF_TIME);
}
///////////////////////////////////////////////////////////////////////////








//
//bc
void InJect_BC_Task(void)
{u8 count;
 u8 pccount=0;//-------
 u16 collectf[]={0,0,0,0,0,0,0,0,0};
 u16 collectb[]={0,0,0,0,0,0,0,0,0};
 s16 colee[]= {0,0,0,0,0,0,0,0,0,0};
 
	//Adc_SetUp_ch3();
	Adc_SetUp_ch(BEMFA_ADC_CH);
	//Adc_SetUp_ch(CURR_ADC_CH);

	 
//========================	
//BC
	 //送相位-----
	   PrcTask_Ph(5);
	  dlay(WAIT_US_PULSE_ON_TIME);
	   Adc_Start();	
	//-------------------------	 
	for(pccount=1;pccount<8;)
	 {if( ADC_CSR_EOC==1)	
	   {
		   dlay(WAIT_ADC_SAMPLE_TIME);
			 collectf[pccount]=ADC_DR;
	  	 tb[pccount]=ADC_DR;
		   pccount++;
	     ADC_CSR_EOC=0;
	     Adc_Start();	
			}
	 
	 }
//-- ------------------------	 
	//PC_ODR=0x00;
	//dlay(WAIT_US_STEP_OFF_TIME);
//----------------------------


//========================
//CB
	 PrcTask_Ph(6);
	  dlay(WAIT_US_PULSE_ON_TIME);
	 Adc_Start();	
	for(pccount=1;pccount<8;)
	 {if( ADC_CSR_EOC==1)	
	   {
		   dlay(WAIT_ADC_SAMPLE_TIME);
			 collectb[pccount]=ADC_DR;
	  	 tb[pccount]=ADC_DR;
		   pccount++;
	     ADC_CSR_EOC=0;
	     Adc_Start();	
			}
	 
	 }
 //--------------------------	
	PC_ODR=0x00;
	Injection.ADC_inj_o = 0;
	Injection.ADC_inj_n = 0;
	Injection.ADC_inj_l = 0;
	Injection.ADC_inj_ne = 0;	
//----------------------------------------
	 for(count=1;count<7;count++)
    {Injection.ADC_inj_o+=collectf[count];
		 colee[count]=collectf[count]-collectf[count+1];
		 Injection.ADC_inj_n+= colee[count];
		}
      Injection.ADC_inj_o=Injection.ADC_inj_o/6;
	  	Injection.ADC_inj_n=Injection.ADC_inj_n/6;
			inject_table[4][0]=Injection.ADC_inj_o;
			inject_table[4][1]=	Injection.ADC_inj_n;
  //------------------------------------------
   for(count=1;count<7;count++)
    { Injection.ADC_inj_l+=collectb[count];
		  colee[count]=collectb[count]-collectb[count+1];
		  Injection.ADC_inj_ne+= colee[count];
		}
      Injection.ADC_inj_l=Injection.ADC_inj_l/6;
      Injection.ADC_inj_ne=Injection.ADC_inj_ne/6;
			inject_table[5][0]=Injection.ADC_inj_l;
			inject_table[5][1]=Injection.ADC_inj_ne;
      dlay(WAIT_US_PULSE_OFF_TIME);
}
/////////////////////////////////////////////////////////////////






//
//ab
void InJect_AB_Task(void)
{u8 count;
u8 pccount=0;//-------
 u16 collectf[]={0,0,0,0,0,0,0,0,0};
 u16 collectb[]={0,0,0,0,0,0,0,0,0};
 s16 colee[]= {0,0,0,0,0,0,0,0,0,0};
 
     //Adc_SetUp_ch1();
	 Adc_SetUp_ch(BEMFC_ADC_CH);
	 //Adc_SetUp_ch(CURR_ADC_CH);

	 
//========================	 
	//送相位------------------
//AB	
	PrcTask_Ph(3);
	dlay(WAIT_US_PULSE_ON_TIME);
	Adc_Start();	
	//-------------------------	 
	for(pccount=1;pccount<8;)
	 {if( ADC_CSR_EOC==1)	
	   {
		  dlay(WAIT_ADC_SAMPLE_TIME);
			 collectf[pccount]=ADC_DR;
	  	 tb[pccount]=ADC_DR;
		   pccount++;
	     ADC_CSR_EOC=0;
	     Adc_Start();	
			}
	 
	 }
//-- ------------------------	 
	//PC_ODR=0x00;
	//dlay(WAIT_US_STEP_OFF_TIME);
//----------------------------



//========================
//BA
	 PrcTask_Ph(4);
	 dlay(WAIT_US_PULSE_ON_TIME);
	 Adc_Start();	
	for(pccount=1;pccount<8;)
	 {if( ADC_CSR_EOC==1)	
	   {
		   dlay(WAIT_ADC_SAMPLE_TIME);
			 collectb[pccount]=ADC_DR;
	  	 tb[pccount]=ADC_DR;
				
		   pccount++;
	     ADC_CSR_EOC=0;
	     Adc_Start();	
			}
	 
	 }
 //--------------------------	
	PC_ODR=0x00;
	Injection.ADC_inj_o = 0;
	Injection.ADC_inj_n = 0;	
	Injection.ADC_inj_l = 0;
	Injection.ADC_inj_ne = 0;
//----------------------------------------
	 for(count=1;count<7;count++)
    {Injection.ADC_inj_o+=collectf[count];
		 colee[count]=collectf[count]-collectf[count+1];
		 Injection.ADC_inj_n+= colee[count];
		}
    Injection.ADC_inj_o=Injection.ADC_inj_o/6;
		Injection.ADC_inj_n=Injection.ADC_inj_n/6;
		
		 inject_table[0][0]=Injection.ADC_inj_o;
		 inject_table[0][1]=Injection.ADC_inj_n;	
  //------------------------------------------
   for(count=1;count<7;count++)
    {Injection.ADC_inj_l+=collectb[count];
		  colee[count]=collectb[count]-collectb[count+1];
		 Injection.ADC_inj_ne+= colee[count];
		}
    Injection.ADC_inj_l=Injection.ADC_inj_l/6;
    Injection.ADC_inj_ne=Injection.ADC_inj_ne/6;
		 inject_table[1][0]= Injection.ADC_inj_l;
		 inject_table[1][1]=Injection.ADC_inj_ne;
     dlay(WAIT_US_PULSE_OFF_TIME);
}








//
void InJect_ST_Prc(void)
{  u8 hps;
   u16 ab,ca,bc,min; 
//=============================================
//---------------识别-------------------------
 if(inject_table[0][0]>inject_table[1][0])
    {
		 ab=inject_table[0][0]-inject_table[1][0];
	  inject_table[0][2]=6;
		 
	 }
 else
   {
     ab=inject_table[1][0]-inject_table[0][0];
		  inject_table[0][2]=4;
		 
   }
	//============================================== 
if(inject_table[2][0]>inject_table[3][0])
   {
		 ca=inject_table[2][0]-inject_table[3][0];
	  inject_table[2][2]=6;
}
 else
   {
     ca=inject_table[3][0]-inject_table[2][0];
		inject_table[2][2]=4;
   }	 
//================================================	 
if(inject_table[4][0]>inject_table[5][0])
   {
		 bc=inject_table[4][0]-inject_table[5][0];
		  inject_table[4][2]=6;
	 }
 else
   {
    bc=inject_table[5][0]-inject_table[4][0];
		 inject_table[4][2]=4;
   }
//===============================================
//--------------一段识别-------------------------
hps=0;


//====================================================
if(inject_table[0][2]==6)
{
 hps=hps|0x01;
}
if(inject_table[2][2]==6)
{
 hps=hps|0x02;
}
if(inject_table[4][2]==6)
{
 hps=hps|0x04;
}

//=================================
switch(hps)
{
case 0x01:{ 
             Motordata.INJGPH=1;
						
	}break;

case 0x02:{  
              Motordata.INJGPH=2;
           
					 
					 }break;

case 0x04:{ 
            Motordata.INJGPH=3;



            }break;
//===================================

case 0x03:{
              Motordata.INJGPH=4;

            }break;//ACSUN

case 0x05:{
            Motordata.INJGPH=5;
						
					}break;//ABSHUN

case 0x06:{
           
					 Motordata.INJGPH=6;
					 }break;//BCSUN
							 
							 
							 
		default:{
	           Motordata.INJGPH=0;
						  
	              
			        }	break;				 
							 
							 
							 
}

//====================================================	
//--------------二段识别------------------------------	

 
 
 

 
         
}

//*/

/*

	INSERT_DATA gInsert;

#define	FUNC_INSERT_ADC_SAMPLE_FOR_BEMF_EN
//#define	FUNC_INSERT_ADC_SAMPLE_FOR_CURR_EN

extern	const unsigned char Detect_ADC_Chanel_Tab[6]=
{
#ifdef	FUNC_INSERT_ADC_SAMPLE_FOR_CURR_EN
//电流检测AB\BC\AC\BA\CB\CA	
	CURR_CHANEL,	
	CURR_CHANEL,	
	CURR_CHANEL,	
	CURR_CHANEL,	
	CURR_CHANEL,	
	CURR_CHANEL,	
#endif

#ifdef	FUNC_INSERT_ADC_SAMPLE_FOR_BEMF_EN
//反电势检测AB\AC\BC\BA\CA\CB
	BEMFC_CHANEL,	
	BEMFB_CHANEL,	
	BEMFA_CHANEL,	
	BEMFC_CHANEL,	
	BEMFB_CHANEL,	
	BEMFA_CHANEL,
#endif

};


//求平均值
unsigned short Get_AvgValue(unsigned short *buff,unsigned char length)
{
	unsigned char i;
	unsigned short sum = 0;
	unsigned short max = 0;
	unsigned short min = 65535;
	for(i = 0;i < length;i ++)
	{
		if(max < buff[i])
		{
			max = buff[i];
		}
		if(min > buff[i])
		{
			min = buff[i];
		}
		sum += buff[i];
	}
	sum = (sum -max - min)/(length-2);
	return(sum);
}






//
//换相步序值0-5分别对应AB\AC\BC\BA\CA\CB
//
void Get_Curr_For_Insert_Pulse(unsigned char step)	
{
//#ifdef	INJECT_DEBUG_EN
	unsigned char  i;
	static unsigned char  StepAdcCh = 0;
//set adc sample chanel
	StepAdcCh = Detect_ADC_Chanel_Tab[step];
	Adc_SetUp_ch(StepAdcCh);
	//Adc_Start();	
	//ADC_Single_Mode_Init(StepAdcCh);
//insert pulse
	switch(step)
	{
//AB	
		case	0:
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//A->B
			PHASE_BL_ON();
			PHASE_AH_ON();	
#else
			PC_ODR=0x42;
#endif

		}break;
//AC		
		case	1:
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//A->C	
			PHASE_CL_ON();
			PHASE_AH_ON();		
#else
			PC_ODR=0x22;
#endif
		}break;	
//BC		
		case	2:
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//B->C
			PHASE_CL_ON();
			PHASE_BH_ON();		
#else
			PC_ODR=0x24;
#endif
		}break;
//BA		
		case	3:
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//B->A
			PHASE_AL_ON();
			PHASE_BH_ON();		
#else
			PC_ODR=0x84;
#endif
		}break;
//CA
		case	4:
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//C->A
			PHASE_AL_ON();
			PHASE_CH_ON();		
#else
			PC_ODR=0x88;
#endif
		}break;	
//CB		
		case	5:
		default:			
		{
			
#ifdef	FUNC_INSERT_1TOP2BOT_PULSE_EN
		//A->BC	
			PHASE_BL_ON();
			PHASE_CL_ON();
			PHASE_AH_ON();
#endif	
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
		//C->B
			PHASE_BL_ON();
			PHASE_CH_ON();		
#else
			PC_ODR=0x48;
#endif
		}break;
	}
//delay	
	//WaitUs(TIME_DELAY_FOR_PHASE_ON);

//read adc	
#ifdef	FUNC_INSERT_ADC_SAMPLE_CONT_MODE_EN
	ADC_Cont_Mode_Init(StepAdcCh);
	ADC_Scan_Start(StepAdcCh);
	ADC_Cont_Get_Value(StepAdcCh,gInsert.AdcCurrSam[step]);
#ifdef	FUNC_INSERT_PULSE_ADC_DEBUG_EN
	ADC_Cont_Get_Value(StepAdcCh,gInsert.AdcCurrSample[step]);
#endif
#endif	
#ifdef	FUNC_INSERT_ADC_SAMPLE_SINGLE_MODE_EN	
	//ADC_Single_Mode_Init(StepAdcCh);
	for(i = 0; i < INSERT_PULSE_ADC_SAMPLE_CNT; i ++)
	{
		gInsert.AdcCurrSam[step][i] = ADC_Single_Get_Value(StepAdcCh);
#ifdef	FUNC_INSERT_PULSE_ADC_DEBUG_EN		
		gInsert.AdcCurrSample[step][i] = ADC_Single_Get_Value(StepAdcCh);
#endif
	}
#else
	dlay(16);
	//dlay(50);
	Adc_Start();	
	for(i = 0; i < INSERT_PULSE_ADC_SAMPLE_CNT; i ++)
	{
		if( ADC_CSR_EOC==1)	
		{
			dlay(2);
			gInsert.AdcCurrSam[step][i]=ADC_DR;
			ADC_CSR_EOC=0;
			Adc_Start();	
		}
	}

#endif	

//all phase off
#ifdef	FUNC_INSERT_1TOP1BOT_PULSE_EN	
//	
	PHASE_AH_OFF();
	PHASE_BH_OFF();
	PHASE_CH_OFF();
//close down phase	
	PHASE_AL_OFF();
	PHASE_BL_OFF();
	PHASE_CL_OFF();
#else
	//PC_ODR=0x00;
	//dlay(100);
	

	//dlay(100);
#endif
	//WaitUs(TIME_DELAY_FOR_PHASE_OFF);
//#endif	
}









//
unsigned char   Get_Step_ForInsertPulse(void)
{
	unsigned char i,j;
	static unsigned char	StepSn = 0;
	static unsigned char	StepSnTemp = 0;	
//#ifdef	INJECT_DEBUG_EN	
//
	//gMotor.AdcSampleFast = 1;
	//disableInterrupts();
//ADC SAMPLE SINGLE INIT	
	//ADC_Single_Mode_Init(ADC_CURR_CHANEL);
//
	for(i =0;i< 6;i++)
	{
		for(j = 0;j < INSERT_PULSE_ADC_SAMPLE_CNT;j++)
		{
			gInsert.AdcCurrSam[i][j] = 0;
		}
		gInsert.AdcCurrAvg[i] = 0;
	}

	//dlay(200);
	PC_ODR=0x00;
	//dlay(200);	
//inset pulse get curr	
	for(i =0;i< 3;i++)
	{
//	
		Get_Curr_For_Insert_Pulse(i);	
//
		Get_Curr_For_Insert_Pulse(i+3);
		PC_ODR=0x00;
		//dlay(400);
		dlay(800);
	}
//from curr crc step
	StepSn = 0;
	StepSnTemp = 0;
	for(i =0;i< 3;i++)
	{	
	 	gInsert.AdcCurrAvg[i] = Get_AvgValue((gInsert.AdcCurrSam[i]),INSERT_PULSE_ADC_SAMPLE_CNT);
		gInsert.AdcCurrAvg[i+3] = Get_AvgValue((gInsert.AdcCurrSam[i+3]),INSERT_PULSE_ADC_SAMPLE_CNT);     

		if(gInsert.AdcCurrAvg[i] > gInsert.AdcCurrAvg[i+3])
		{
			StepSnTemp |= (1<<i);
		}
	}	
	switch(StepSnTemp)
	{
//
		case	0:
		{
			StepSn = 2;		
		}break;
//		
		case	1:
		{
			StepSn = 4;		
		}break;
//
		case	4:
		{
			StepSn = 6;		
		}break;
//		
		case	3:
		{
			StepSn = 1;
		}break;		
//		
		case	6:
		{
			StepSn = 3;
		}break;
//		
		case	7:
		{
			StepSn = 5;
		}break;	
//err		
		case	2:
		{
			StepSn = 0;//ERR
		}break;	
//			
		case	5:
		{
			StepSn = 0;//ERR
		}break;
//		
		default:
		{
			StepSn = 0;//ERR	
		}break;
		
	}
//	
	//enableInterrupts();	
	//gMotor.AdcSampleFast = 0;
//ADC SCAN SAMPLE INIT	
	//ADC_Scan_Mode_Init();
//#endif
//return step
	return(StepSn);
}

*/