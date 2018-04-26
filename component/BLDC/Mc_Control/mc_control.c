
/*******************************copyright(c)***************************************
*
*                       ShenZhen  pace  electronics  co.LTD
*
*                             BLDC  energy  Team
*
*---file info----------------------------------------------------------------------
*
*  ÎÄ¼þÃû³Æ:	    mc_control.c
*  ÐÞ¸ÄÈÕÆÚ£º     v1.0
*  ×îÖÕ°æ±¾£º     v2.0 
*  ¼òÒªÃèÊö:      TIME  module init
*
*----------------------------------------------------------------------------------
*  ´´½¨×÷Õß:       roger luo
*  ´´½¨ÈÕÆÚ:       2016.04.16
*  ´´½¨°æ±¾£º      V1.0
*  ´´½¨ÃèÊö:       TIME  module init
*
*----------------------------------------------------------------------------------
*  ÐÞ¸ÄÈËÔ±£º     NO
*  ÐÞ¸ÄÈÕÆÚ£º     NO
*  ÐÞ¸Ä°æ±¾£º     NO
*  ÐÞ¸ÄÃèÊö£º     NO
*
**********************************************************************************/












/**************************************************************/
#include "public.h"
#include "param.h"
#include "mc_driver.h"
#include "mc_control.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "inject.h"
#include "mswitch.h"
#include "mc_config.h"
#include "mdisply.h"


/***************************************************************
* ²ÎÊýÃèÊö : ÎÞ
* ÀàÐÍ     : ÎÞ
* ÃèÊö     :     
***************************************************************/

//-----------------------------------------
//=========================================
const halltable[]={0,1,5,4,6,2,3,0};
//-------------------------------------------
//»»ÏàË³Ðò±í---------------------------------
const phtable[]={0,1,6,5,2,4,3,0};


//==========================================
//ÕýÏòÔËÐÐ»»Ïà------------------------------
//  ab,ba,cb,bc,ca,ac
const Fphtable[]={0,1,6,5,2,4,3,0};//Õý»»Ïà
//==========================================
//·´ÏòÔËÐÐ»»Ïà------------------------------
const Rphtable[]={0,5,4,1,3,6,2,0};//·´»»Ïà
//******************************************






//******************************************
//------------------------------------------
const poztable[]={0,1,2,4,5,6,3,0};//Í£³µÎ»ÖÃ
//Êµ¼ÊµÄÍ£³µÎ»ÖÃ±íÊé·¨======================




//{0,1,2,4,5,0,3,0};//Í£³µÎ»


//------------------------------------------
const phztable[]={0,1,3,5,5,6,3,0};//Õý¼ÓËÙ
//{0,6,1,5,5,6,3,0}
//------------------------------------------

const prztable[]={0,6,3,5,5,6,3,0};//·´¼ÓËÙ

const unsigned short EVERY_GRADE_PWM_MAX_TAB1[] =
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


const unsigned short EVERY_GRADE_PWM_REVS_MAX_TAB1[] =
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


/******************************************************************
*
*ËµÃ÷  £º¹«¹²²¿·Ö³ÌÐò¶Î£¬²¢ÐÐÔËÐÐÓë×´Ì¬»ú
*
******************************************************************/



//
void Revs_Stop_Handle(void)
{
#ifdef	FUNC_REVS_STOP_EN


	static unsigned char RevStop_State = 0;
	static unsigned char RevStop_Cnt1 = 0;

#ifdef	PROJ_SST16_195	
	if(Motordata.MFR==DIR_REVS)		//ccw
	{
//	
		if(
			(Motordata.SWhkey.FRstop==0xaa)
			&&(Motordata.SWhkey.Mgear == 2)
			)
		{   
			//RevStop_State = 1;
			if(Motordata.prct.Anp>300)
			{
				RevStop_Cnt1 ++;
				if(RevStop_Cnt1 > 100)
				{
					RevStop_State = 1;

				}
			}
			
			if(RevStop_State == 1)
			{
		
			if(Motordata.UI.Mroller>1&&Motordata.prct.Anp<240)
			{ 
				Motordata.UI.Mroller-=1;
			}
		
			if( Motordata.prct.Anp>=240)
			{
				Motordata.UI.Mroller=400;		//450
			}
			
			if(Motordata.UI.Mroller<=2)	
			{
				Motordata.UI.Blink=0;
				Motordata.UI.Mroller=450;
				Motordata.station=Stop;
				RevStop_State = 0;
				RevStop_Cnt1 = 0;
			}
			}
		}
		else
		{
			RevStop_State = 0;
			RevStop_Cnt1 = 0;
		}
	}
	else
	{
		RevStop_State = 0;
		RevStop_Cnt1 = 0;
	}

#else
	if(Motordata.MFR==DIR_REVS)		//ccw
	{
//	
		if(Motordata.SWhkey.FRstop==0xaa)
		{   
			if(Motordata.UI.Mroller>1&&Motordata.prct.Anp<240)
			{ 
				Motordata.UI.Mroller-=1;
			}
		
			if( Motordata.prct.Anp>=240)
			{
				Motordata.UI.Mroller=450;
			}
			
			if(Motordata.UI.Mroller<=2)	
			{
				Motordata.UI.Blink=0;
				Motordata.UI.Mroller=450;
				Motordata.station=Stop;
			}
		}
	}
#endif

	
#endif
}





/***********************************************************
* º¯ÊýÃû³Æ: ¿ª¹Ø¼ì²â
* °æ±¾ºÅ:   v1.0
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
***********************************************************/
void TS_ch_ph(u8 ky)
{ 
	u8 tsk;
	ChangeDuty(Motordata.outduty);
	tsk=halltable[ky];
	Motordata.test=tsk;
	Motordata.mstep=Fphtable[tsk];
	change_ph();
	Revs_Stop_Handle();
}
//==========================================================








/***********************************************************
* º¯ÊýÃû³Æ: ¿ª¹Ø¼ì²â
* °æ±¾ºÅ:   v1.0
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
***********************************************************/
void TSR_ch_ph(u8 ky)
{ 
	u8 tsk;
	ChangeDuty(Motordata.outduty);
	tsk=halltable[ky];
	Motordata.mstep=Rphtable[tsk];
	change_ph();
	Revs_Stop_Handle();
	
//
/*
	if(Motordata.SWhkey.FRstop==0xaa)
	{   
		if(Motordata.UI.Mroller>1&&Motordata.prct.Anp<240)
		{ 
			Motordata.UI.Mroller-=1;
		}
	
		if( Motordata.prct.Anp>=240)
		{
			Motordata.UI.Mroller=450;
		}
		
		if(Motordata.UI.Mroller<=2)	
		{
			Motordata.UI.Blink=0;
			Motordata.UI.Mroller=450;
			Motordata.station=Stop;
		}
	}
*/		

}
//====================================================




//*****************************************************
void TS_lpv()
{
//
	if(Motordata.TRcount>40)			//40
	{
		Motordata.TRcount=40;		//40
	}
							
	if(Motordata.TVcount<	Motordata.TRcount>>1)
	{
		Motordata.TVcount+=1; 
	}
	
	if(Motordata.TVcount>	Motordata.TRcount>>1&&Motordata.TVcount>1)
	{
		Motordata.TVcount-=1; 	
	}
	
	Motordata.TQcount=Motordata.TVcount;//PSNLV;
}


/***************************************************************************
* ËµÃ÷  : ×´Ì¬»ú²¿·ÖµÄÔËÐÐ ³ÌÐò¶Î
***************************************************************************/

/*******************************************************
* º¯ÊýÃû³Æ: ÑÓÊ±³ÌÐò 
* °æ±¾ºÅ:   v1.0
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
*********************************************************/
void	dlay (u16 d)
{  
	u16 u,y;
	u=d;      //1.5us
	for(y=0;y<u;y++); 
		  
}
		
//=========================================================		
		
		
		
		
		
		
		
		
		

/***********************************************************
* º¯ÊýÃû³Æ  : void MCTask_Ready()
* ²ÎÊýÃèÊö  : ÎÞ
* ·µ»ØÖµ    : ÎÞ
* ÃèÊö      :     
***********************************************************/
void MCTask_Ready()
{   
 //
	if( Motordata.Dswitch==MOTOR_ON)
	{
		Motordata.UI.Mroller=700;
		PD2_OUT=1;
		Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
		Motordata.station=Startup;
		dlay(30);
			 
		Motordata.prct.DISv= Motordata.prct.Volt;

		Motordata.prct. DIStp=Motordata.prct.Tempr;//ÎÂ¶È

		//Motordata.prct. DIStp = Motordata.prct.MosTemp;
		//Motordata.prct. DIStp = Motordata.prct.MosAddBatTemp;


//   Motordata.prct.DISvsm;//¹ýÑ¹
//   Motordata.prct.DISism;//¹ýÁ÷
//   Motordata.prct.DISois;//
//============================================
			 
		check_erorr();
	}
	DisAllPwmOut();
}
//========================================================











/***********************************************************
* º¯ÊýÃû³Æ:  Injection.adstat=INject;  
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:      // Iject_Check();	
***********************************************************/

void MCTask_Start()
{
 //==ÂöÕí×¢Èë============
	if(Motordata.Flgsw==1)
	{
//=======================
///*
		dlay (3000);
		InJect_AB_Task();
		InJect_AC_Task();
		InJect_BC_Task();
//========================
		InJect_ST_Prc();
		Motordata.mstep=Motordata.INJGPH;
		dlay (3000);
		InJect_AB_Task();
		InJect_AC_Task();
		InJect_BC_Task();
//===================
//==½âÎö=============
		InJect_ST_Prc();
//---------------------
//*/
/*
		//dlay (3000);
		dlay (1000);
		Motordata.INJGPH = Get_Step_ForInsertPulse();
		//dlay (3000);
		dlay (1000);
		Motordata.mstep=Motordata.INJGPH;
		Motordata.INJGPH = Get_Step_ForInsertPulse();
*/
		Motordata.Flgsw=0;
		PC_ODR=0xf0;
		dlay(100);
	}
//-----------------------------
}
//======================================================








/*
void MCTask_NorRun()
{
	u8  bemf;
	u8 cbuf;
	bemf=Get_pa_vhl();
//--»ñµÃ¼ì²âÈ¨ÏÞ--Æô¶¯¼ì²â--
//====================================================
//PB7_OUT= ~PB7_OUT;
 	if(Motordata.MFR==CW)  
	{
		switch(Motordata.bstep.nwstep)
		{
			
//============
//001
//fbemfb//ab
			case  PSN1:
			{//
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x00)
				{
			          	Motordata.bstep.nwstep=PSN2;
					TS_ch_ph(PSN1);
					TS_lpv();
		             		Motordata.TRcount=0;
				}
		     	}break;
//============
//101
//rbemfc//cb
			case  PSN2:
		 	{
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x04)
				{ 
					Motordata.bstep.nwstep= PSN3;
					TS_ch_ph(PSN2);
					TS_lpv();
					Motordata.TRcount=0;
				}//4//4
		       
			}break;
			
//=============
//100
//fbemfa//ca
			case  PSN3:
			{
				Motordata.bstep.odstep= bemf&0x01;
				if(Motordata.bstep.odstep==0x00)		
				{	
					Motordata.bstep.nwstep= PSN4;
					TS_ch_ph(PSN3);
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
			
//=============
//110
//rbemfb//ba
			case  PSN4:
			{
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x02)
				{
			           
					Motordata.bstep.nwstep= PSN5;
					TS_ch_ph(PSN4);
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
			
//=============
//010
//fbemfc//bc
			case  PSN5:
			{ 
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep= PSN6;
					TS_ch_ph(PSN5);
					TS_lpv();
					Motordata.TRcount=0;
				}
		                   
			}break;
			
//=============
//011
//rbemfa//ac
			case  PSN6:
			{          

				Motordata.bstep.odstep= bemf&0x01;
				if(Motordata.bstep.odstep==0x01)
				{	  
					Motordata.bstep.nwstep= PSN1;
					TS_ch_ph(PSN6);
					TS_lpv();
					Motordata.TRcount=0;
				}
			 				
			}break;
		 
		}
	}
	
//====================================================
	if(Motordata.MFR==CCW)  
	{
		switch(Motordata.bstep.nwstep)
		{
		
//============
//001
//fbemfc//ac
			case  PSN1:
			{
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep=PSN2;
					TSR_ch_ph(PSN1);     //ac
					TS_lpv();
					Motordata.TRcount=0;
				}
		     	}break;
			
//============
//011
//rbemfb//bc
			case  PSN2:
			{
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x02)
				{ 
					Motordata.bstep.nwstep= PSN3;
					TSR_ch_ph(PSN2);//bc
					TS_lpv();
					Motordata.TRcount=0;
				}//4//4
		       
			}break;
			
//=============
//010
//fbemfa//ba
			case  PSN3:
		 	{
				Motordata.bstep.odstep= bemf&0x01;//a
				if(Motordata.bstep.odstep==0x00)		
				{	
					Motordata.bstep.nwstep= PSN4;
					TSR_ch_ph(PSN3);//ba
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//110
//rbemfc//ca
			case  PSN4:
		 	{
		              Motordata.bstep.odstep= bemf&0x04;//c
				if(Motordata.bstep.odstep==0x04)
				{  
			              Motordata.bstep.nwstep= PSN5;
					TSR_ch_ph(PSN4);//ca
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//100
//fbemfb//cb
			case  PSN5:
			{ 
				Motordata.bstep.odstep= bemf&0x02;//b
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep= PSN6;
					TSR_ch_ph(PSN5);//cb
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//101
//rbemfa//ab
			case  PSN6:
			{          

				Motordata.bstep.odstep= bemf&0x01;//a
				if(Motordata.bstep.odstep==0x01)
				{	  
					Motordata.bstep.nwstep= PSN1;
					TSR_ch_ph(PSN6);//ab
					TS_lpv();
					Motordata.TRcount=0;
				}
		 				
			}break;
		 
		}

	}

}
*/


//======================================================


/********************************************************
* º¯ÊýÃû³Æ: 
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
*********************************************************/
void MCTask_NorRun1()
{
	u8  bemf;
	u8 cbuf;
	bemf=Get_pa_vhl();
//--»ñµÃ¼ì²âÈ¨ÏÞ--Æô¶¯¼ì²â--
//====================================================
//PB7_OUT= ~PB7_OUT;
 	if(Motordata.MFR==CW)  
	{
		switch(Motordata.bstep.nwstep)
		{
			
//============
//001
//fbemfb//ab
			case  PSN1:
			{//
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x00)
				{
			          	Motordata.bstep.nwstep=PSN2;
					TS_ch_ph(PSN1);
					TS_lpv();
		             		Motordata.TRcount=0;
				}
		     	}break;
//============
//101
//rbemfc//cb
			case  PSN2:
		 	{
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x04)
				{ 
					Motordata.bstep.nwstep= PSN3;
					TS_ch_ph(PSN2);
					TS_lpv();
					Motordata.TRcount=0;
				}//4//4
		       
			}break;
			
//=============
//100
//fbemfa//ca
			case  PSN3:
			{
				Motordata.bstep.odstep= bemf&0x01;
				if(Motordata.bstep.odstep==0x00)		
				{	
					Motordata.bstep.nwstep= PSN4;
					TS_ch_ph(PSN3);
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
			
//=============
//110
//rbemfb//ba
			case  PSN4:
			{
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x02)
				{
			           
					Motordata.bstep.nwstep= PSN5;
					TS_ch_ph(PSN4);
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
			
//=============
//010
//fbemfc//bc
			case  PSN5:
			{ 
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep= PSN6;
					TS_ch_ph(PSN5);
					TS_lpv();
					Motordata.TRcount=0;
				}
		                   
			}break;
			
//=============
//011
//rbemfa//ac
			case  PSN6:
			{          

				Motordata.bstep.odstep= bemf&0x01;
				if(Motordata.bstep.odstep==0x01)
				{	  
					Motordata.bstep.nwstep= PSN1;
					TS_ch_ph(PSN6);
					TS_lpv();
					Motordata.TRcount=0;
				}
			 				
			}break;
		 
		}
	}
	
//====================================================
	if(Motordata.MFR==CCW)  
	{
		switch(Motordata.bstep.nwstep)
		{
		
//============
//001
//fbemfc//ac
			case  PSN1:
			{
				Motordata.bstep.odstep= bemf&0x04;
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep=PSN2;
					TSR_ch_ph(PSN1);     //ac
					TS_lpv();
					Motordata.TRcount=0;
				}
		     	}break;
			
//============
//011
//rbemfb//bc
			case  PSN2:
			{
				Motordata.bstep.odstep= bemf&0x02;
				if(Motordata.bstep.odstep==0x02)
				{ 
					Motordata.bstep.nwstep= PSN3;
					TSR_ch_ph(PSN2);//bc
					TS_lpv();
					Motordata.TRcount=0;
				}//4//4
		       
			}break;
			
//=============
//010
//fbemfa//ba
			case  PSN3:
		 	{
				Motordata.bstep.odstep= bemf&0x01;//a
				if(Motordata.bstep.odstep==0x00)		
				{	
					Motordata.bstep.nwstep= PSN4;
					TSR_ch_ph(PSN3);//ba
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//110
//rbemfc//ca
			case  PSN4:
		 	{
		              Motordata.bstep.odstep= bemf&0x04;//c
				if(Motordata.bstep.odstep==0x04)
				{  
			              Motordata.bstep.nwstep= PSN5;
					TSR_ch_ph(PSN4);//ca
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//100
//fbemfb//cb
			case  PSN5:
			{ 
				Motordata.bstep.odstep= bemf&0x02;//b
				if(Motordata.bstep.odstep==0x00)
				{
					Motordata.bstep.nwstep= PSN6;
					TSR_ch_ph(PSN5);//cb
					TS_lpv();
					Motordata.TRcount=0;
				}
			}break;
		 
//=============
//101
//rbemfa//ab
			case  PSN6:
			{          

				Motordata.bstep.odstep= bemf&0x01;//a
				if(Motordata.bstep.odstep==0x01)
				{	  
					Motordata.bstep.nwstep= PSN1;
					TSR_ch_ph(PSN6);//ab
					TS_lpv();
					Motordata.TRcount=0;
				}
		 				
			}break;
		 
		}

	}

}









/*****************************************************************
* º¯ÊýÃû³Æ: MCTask_Stop()      Í£Ö¹×´Ì¬
* °æ±¾ºÅ:   v1.0
* ²ÎÊýÃèÊö: ÎÞ
* ·µ»ØÖµ:   ÎÞ
* ÃèÊö:     
*****************************************************************/
void MCTask_Stop()
{
	DisAllPwmOut();
//switch()========
	if( Motordata.Dswitch==MOTOR_ON)
	{

	}
}
//===============================================================






/****************************************************************
* ËµÃ÷  : ×´Ì¬»ú²¿·ÖµÄÔËÐÐ³ÌÐò£¬Óë¹«ÓÃ³ÌÐò²¿·Ö²¢ÐÐ£
*****************************************************************/






/************************************************************
* º¯ÊýÃû³Æ  : Motor run
* °æ±¾ºÅ    : v2.0
* ²ÎÊýÃèÊö  : ÎÞ
* ·µ»ØÖµ    : ÎÞ
* ÃèÊö      : ×´Ì¬»ú     
************************************************************/
//========================================
void Motor_Run(void)
{ 
//
	switch(Motordata.station)
	{  
//=====================================
//==µÈ´ý×´Ì¬===============
		case Ready:
		{  //==¼ì²âÊÇ·ñÔËÐÐ======= 
//=ÅÐ¶ÏÕý·´×ª==    												 
			if(Get_sw_fr()==0)
			{ 
				Motordata.MFR=SW_POS;			//CW	
			}
			if(Get_sw_fr()==1)
			{ 
				Motordata.MFR=SW_REVS;			//CCW
			}
//---------
			if(Motordata.UI.MFRch!=Motordata.MFR)
			{
				Motordata.UI.MFRch=Motordata.MFR;
//update pwm
				Motordata.UI.Gduty = EVERY_GRADE_PWM_MAX_TAB1[Motordata.SWhkey.Mgear];
				if(Motordata.MFR==DIR_REVS)
				{
					Motordata.UI.Gduty = EVERY_GRADE_PWM_REVS_MAX_TAB1[Motordata.SWhkey.Mgear];
				}
				
				Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
			}
//				
			if( Motordata.Dswitch==MOTOR_OFF)
			{	 
				Motordata.Flgsw=1;
			}
						
//°´¼ü¿ª¹Ø						 
				MC_Swbut_Check();
										
								
				bskill_run();
						
//================================
				MCTask_Ready();
				
				DisAllPwmOut();	
//===============================
								  
		} break;
		
//==================================
//»ñµÃµÚÒ»²½µÄÎ»ÖÃÊ¶±ð
		case  Startup:
		{
//=»ñµÃµÚÒ»²½Î»ÖÃ==============
			PC6_OUT=0;
			PC5_OUT=0;
			PC7_OUT=0;
			pwm_reset();						 
			MCTask_Start();	
//==============================
			if( Motordata.mstep==Motordata.INJGPH)
			{
				Motordata.station=StartRun;		
			}
//==================================
			if( Motordata.mstep!=Motordata.INJGPH)	
			{
				Motordata.station=Ready;
				Motordata.Flgsw=1;
				TIM5_Ready_StartCount();
				Adc_Scan_timetrig_init();	
			}
//==================================
		} break;
		
//======================================	
//¼ÓËÙÍ¬²½Æô¶¯-----------
		case StartRun:
		{
 
			if( Motordata.INJGPH!=0)
			{   
				PWM_INIT();//==ÖØÐÂ³õÊ¼»¯======
									
				if(Motordata.MFR==CW)//=====
				{
					Motordata.bstep.nwstep= poztable[Motordata.INJGPH]; 
				}//ÕýÎ»ÖÃ==
				if(Motordata.MFR==CCW)//·´Æô¶¯
				{//Motordata.bstep.nwstep=1;  
					Motordata.bstep.nwstep= poztable[Motordata.INJGPH];
				}
								 
				if(Motordata.bstep.nwstep>=1&&Motordata.bstep.nwstep<=6)
				{
//TIM5_StartCount();				 
					Motordata.station= NorRun;
					Motordata.SWhkey.KILLrun=5;		 
 //setup ch4----------------
					TIM1_CCMR4=0x68;
					TIM1_CCER2_CC4P =1;
					TIM1_CCER2_CC4E =1;
//-----------------
					Motordata.outduty=50;
									//adc  pwm trig -----------
					Adc_Scan_pwmtrig_init();
					Adc_Start();
//======================
					Motordata.TRcount=50;
					Motordata.TVcount=PSNLV;
//--------------------------------------------------
//==================================================
					if(Motordata.MFR==CW)//ÕýÆô¶¯
					{
						TS_ch_ph(phztable[Motordata.INJGPH]);//
						Motordata.TQcount=Motordata.TVcount;
					}
					if(Motordata.MFR==CCW)//·´Æô¶¯
					{						 
						TSR_ch_ph( prztable[Motordata.INJGPH]);//==Î´Ë³ ==							 
						Motordata.TQcount=Motordata.TVcount;		 
					}   
				}
			}

			if( Motordata.INJGPH==0)
			{
				Motordata.station=Stop;
				Motordata.Flgsw=0;
				Adc_Scan_timetrig_init();
				TIM5_Ready_StartCount();			 				 
			}					
		} break;		
		
//--------------------------------
//=ÔËÐÐ  =ÐÅºÅÔËÐÐ=====
		case    NorRun:
		{
////////////////////////////////////////////			
			//MCTask_Ready();

		Motordata.prct.DISv= Motordata.prct.Volt;

		Motordata.prct. DIStp=Motordata.prct.Tempr;//ÎÂ¶È

		Motordata.prct. DIStp = Motordata.prct.MosTemp;
		Motordata.prct. DIStp = Motordata.prct.MosAddBatTemp;


//   Motordata.prct.DISvsm;//¹ýÑ¹
//   Motordata.prct.DISism;//¹ýÁ÷
//   Motordata.prct.DISois;//
//============================================
			 
		check_erorr();
////////////////////////////////////////////

			if( Motordata.Dswitch==MOTOR_ON)
			{	 
				Motordata.SWhkey.KILLrun=0;
			}
								 
			if( Motordata.Dswitch==MOTOR_OFF)		
			{ 
//Motordata.outduty=1;
				ChangeDuty(0);
				Motordata.SWhkey.KILLrun+=1;
							 
				if( Motordata.SWhkey.KILLrun==800)	//800
				{ 
					TIM1_CCER2_CC4E =0;
					ChangeDuty(1);
					DisAllPwmOut();
//===========================
//
#ifdef	FUNC_BREAK_EN
					PC6_OUT=1;
                  			PC5_OUT=1;
					PC7_OUT=1;
#else
					PC6_OUT=0;
                  			PC5_OUT=0;
					PC7_OUT=0;
#endif					
					//js170720 dlay (4000);

					dlay (4000);

					PC6_OUT=0;
                  			PC5_OUT=0;
					PC7_OUT=0;
					//dlay (30000);				
									
//===========================
					Motordata.station=Ready;
			         	Motordata.Flgsw=0;
					Motordata.outduty=1;
					Adc_Scan_timetrig_init();
					TIM5_Ready_StartCount();
				}
			}	
//==============================							
			ChangeDuty(Motordata.outduty);
				 
		} break;
		
//---------------------------------
//Òì³£Í£Ö¹=±¨´í×´Ì¬====
		case  Stop:
		{
//EBrake();//=MISTAKE;
			MCTask_Stop();	
//±¨´í===============							 
			ChangeDuty(0);	
//
/*
			if(Motordata.fault != 0)
			{
				PD2_OUT=0;
			}
			else
			{
				PD2_OUT=1;

			}
*/			
//

			if( Motordata.Dswitch==MOTOR_OFF)	
			{ 
				TIM1_CCER2_CC4E =0;
				ChangeDuty(0);
				Motordata.Flgsw=0;
				Motordata.outduty=1;
				DisAllPwmOut();
				Motordata.UI.Blink=0;
				Motordata.station=Ready;
				Adc_Scan_timetrig_init();
				TIM5_Ready_StartCount();
			}	
		} break;	
	}

}


