/**********************************************************
*name:  public.h
*version: v1.0 (2018-4-1)
*detail:  include public head file
*author:  ÍõÔª
***********************************************************/


/**************************************************************/
//#include "public.h"
#include "param.h"
#include "mc_driver.h"
#include "mc_control.h"
//#include "adc.h"
//#include "tim.h"
//#include "gpio.h"
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
const uint8_t halltable[]={0,1,5,4,6,2,3,0};
//-------------------------------------------
//»»ÏàË³Ðò±í---------------------------------
const uint8_t phtable[]={0,1,6,5,2,4,3,0};


//==========================================
//ÕýÏòÔËÐÐ»»Ïà------------------------------
//  ab,ba,cb,bc,ca,ac
const uint8_t Fphtable[]={0,1,6,5,2,4,3,0};//Õý»»Ïà
//==========================================
//·´ÏòÔËÐÐ»»Ïà------------------------------
const uint8_t Rphtable[]={0,5,4,1,3,6,2,0};//·´»»Ïà
//******************************************


//******************************************
//------------------------------------------
const uint8_t poztable[]={0,1,2,4,5,6,3,0};//Í£³µÎ»ÖÃ
//Êµ¼ÊµÄÍ£³µÎ»ÖÃ±íÊé·¨======================

//{0,1,2,4,5,0,3,0};//Í£³µÎ»


//------------------------------------------
const uint8_t phztable[]={0,1,3,5,5,6,3,0};//Õý¼ÓËÙ
//{0,6,1,5,5,6,3,0}
//------------------------------------------

const uint8_t prztable[]={0,6,3,5,5,6,3,0};//·´¼ÓËÙ

const unsigned short EVERY_GRADE_PWM_MAX_TAB1[] =
{
	0,
//	GRADE1_PWM_MAX,
//	GRADE2_PWM_MAX,
//	GRADE3_PWM_MAX,
//	GRADE4_PWM_MAX,
//	GRADE5_PWM_MAX,
//	GRADE6_PWM_MAX,
//	GRADE7_PWM_MAX,
//	GRADE8_PWM_MAX

};


const unsigned short EVERY_GRADE_PWM_REVS_MAX_TAB1[] =
{
	0,
//	GRADE1_PWM_REVS_MAX,
//	GRADE2_PWM_REVS_MAX,
//	GRADE3_PWM_REVS_MAX,
//	GRADE4_PWM_REVS_MAX,
//	GRADE5_PWM_REVS_MAX,
//	GRADE6_PWM_REVS_MAX,
//	GRADE7_PWM_REVS_MAX,
//	GRADE8_PWM_REVS_MAX

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
	if(Motordata.mfr==DIR_REVS)		//ccw
	{
//	
		if(
			(Motordata.swhkey.FRstop==0xaa)
			&&(Motordata.swhkey.Mgear == 2)
			)
		{   
			//RevStop_State = 1;
			if(Motordata.prct.anp>300)
			{
				RevStop_Cnt1 ++;
				if(RevStop_Cnt1 > 100)
				{
					RevStop_State = 1;

				}
			}
			
			if(RevStop_State == 1)
			{
		
			if(Motordata.ui.mroller>1&&Motordata.prct.anp<240)
			{ 
				Motordata.ui.mroller-=1;
			}
		
			if( Motordata.prct.anp>=240)
			{
				Motordata.ui.mroller=400;		//450
			}
			
			if(Motordata.ui.mroller<=2)	
			{
				Motordata.ui.blink=0;
				Motordata.ui.mroller=450;
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
	if(Motordata.mfr==DIR_REVS)		//ccw
	{
//	
		if(Motordata.swhkey.frstop==0xaa)
		{   
			if(Motordata.ui.mroller>1&&Motordata.prct.anp<240)
			{ 
				Motordata.ui.mroller-=1;
			}
		
			if( Motordata.prct.anp>=240)
			{
				Motordata.ui.mroller=450;
			}
			
			if(Motordata.ui.mroller<=2)	
			{
				Motordata.ui.blink=0;
				Motordata.ui.mroller=450;
				Motordata.station=stop;
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
void TS_ch_ph(uint8_t ky)
{ 
	uint8_t tsk;
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
void TSR_ch_ph(uint8_t ky)
{ 
	uint8_t tsk;
	ChangeDuty(Motordata.outduty);
	tsk=halltable[ky];
	Motordata.mstep=Rphtable[tsk];
	change_ph();
	Revs_Stop_Handle();
	
//
/*
	if(Motordata.swhkey.FRstop==0xaa)
	{   
		if(Motordata.ui.mroller>1&&Motordata.prct.anp<240)
		{ 
			Motordata.ui.mroller-=1;
		}
	
		if( Motordata.prct.anp>=240)
		{
			Motordata.ui.mroller=450;
		}
		
		if(Motordata.ui.mroller<=2)	
		{
			Motordata.ui.blink=0;
			Motordata.ui.mroller=450;
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
	if(Motordata.trcount>40)			//40
	{
		Motordata.trcount=40;		//40
	}
							
	if(Motordata.tvcount<	Motordata.trcount>>1)
	{
		Motordata.tvcount+=1; 
	}
	
	if(Motordata.tvcount>	Motordata.trcount>>1&&Motordata.tvcount>1)
	{
		Motordata.tvcount-=1; 	
	}
	
	Motordata.tqcount=Motordata.tvcount;//PSNLV;
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
void	dlay (uint16_t d)
{  
	uint16_t u,y;
	u=d;      //1.5us
	for(y=0;y<u;y++); 
		  
}
		
//=========================================================		

/***********************************************************
* º¯ÊýÃû³Æ  : void MCTask_ready()
* ²ÎÊýÃèÊö  : ÎÞ
* ·µ»ØÖµ    : ÎÞ
* ÃèÊö      :     
***********************************************************/
void MCTask_ready()
{
  if(Motordata.dswitch == MOTOR_ON)
  {
    Motordata.ui.mroller = 700;
//    PD2_OUT = 1;        //
    Motordata.swhkey.trdelay = PWR_DELAY_TIME;
    Motordata.station = startup;
    dlay(30);

    Motordata.prct.disv= Motordata.prct.volt;

    Motordata.prct. distp=Motordata.prct.tempr;//ÎÂ¶È

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
  if(Motordata.flgsw==1)
  {
    //=======================
    ///*
    dlay (3000);
    InJect_AB_Task();
    InJect_AC_Task();
    InJect_BC_Task();
    //========================
    InJect_ST_Prc();
    Motordata.mstep = Motordata.injgph;
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
    Motordata.injgph = Get_Step_ForInsertPulse();
    //dlay (3000);
    dlay (1000);
    Motordata.mstep=Motordata.injgph;
    Motordata.injgph = Get_Step_ForInsertPulse();
    */
    Motordata.flgsw = 0;
//    PC_ODR = 0xf0;    //
    dlay(100);
  }
//-----------------------------
}
//======================================================








/*
void MCTask_norrun()
{
	uint8_t  bemf;
	uint8_t cbuf;
	bemf=Get_pa_vhl();
//--»ñµÃ¼ì²âÈ¨ÏÞ--Æô¶¯¼ì²â--
//====================================================
//PB7_OUT= ~PB7_OUT;
 	if(Motordata.mfr==CW)  
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
		             		Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
				}
			 				
			}break;
		 
		}
	}
	
//====================================================
	if(Motordata.mfr==CCW)  
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
void MCTask_norrun1()
{
	uint8_t  bemf;
	uint8_t cbuf;
	bemf=Get_pa_vhl();
//--»ñµÃ¼ì²âÈ¨ÏÞ--Æô¶¯¼ì²â--
//====================================================
//PB7_OUT= ~PB7_OUT;
 	if(Motordata.mfr==CW)  
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
		             		Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
				}
			 				
			}break;
		 
		}
	}
	
//====================================================
	if(Motordata.mfr==CCW)  
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
					Motordata.trcount=0;
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
  if( Motordata.dswitch==MOTOR_ON)
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
#if 0
//
	switch(Motordata.station)
	{  
//=====================================
//==µÈ´ý×´Ì¬===============
		case ready:
		{  //==¼ì²âÊÇ·ñÔËÐÐ======= 
//=ÅÐ¶ÏÕý·´×ª==    												 
			if(Get_sw_fr()==0)
			{ 
				Motordata.mfr = SW_POS;			//CW	
			}
			if(Get_sw_fr()==1)
			{ 
				Motordata.mfr = SW_REVS;			//CCW
			}
//---------
			if(Motordata.ui.mfrch != Motordata.mfr)
			{
				Motordata.ui.mfrch = Motordata.mfr;
//update pwm
				Motordata.ui.gduty = EVERY_GRADE_PWM_MAX_TAB1[Motordata.swhkey.mgear];
				if(Motordata.mfr==DIR_REVS)
				{
					Motordata.ui.gduty = EVERY_GRADE_PWM_REVS_MAX_TAB1[Motordata.swhkey.mgear];
				}
				
				Motordata.swhkey.trdelay=PWR_DELAY_TIME;
			}
//				
			if( Motordata.dswitch==MOTOR_OFF)
			{	 
				Motordata.flgsw=1;
			}
						
//°´¼ü¿ª¹Ø						 
				MC_Swbut_Check();
										
								
				bskill_run();
						
//================================
				MCTask_ready();
				
				DisAllPwmOut();	
//===============================
								  
		} break;
		
//==================================
//»ñµÃµÚÒ»²½µÄÎ»ÖÃÊ¶±ð
		case  startup:
		{
//=»ñµÃµÚÒ»²½Î»ÖÃ==============
			PC6_OUT=0;
			PC5_OUT=0;
			PC7_OUT=0;
			pwm_reset();						 
			MCTask_Start();	
//==============================
			if( Motordata.mstep==Motordata.injgph)
			{
				Motordata.station=startrun;		
			}
//==================================
			if( Motordata.mstep!=Motordata.injgph)	
			{
				Motordata.station=ready;
				Motordata.flgsw=1;
				TIM5_ready_StartCount();
				Adc_Scan_timetrig_init();	
			}
//==================================
		} break;
		
//======================================	
//¼ÓËÙÍ¬²½Æô¶¯-----------
		case startrun:
		{
 
			if( Motordata.injgph!=0)
			{   
				PWM_INIT();//==ÖØÐÂ³õÊ¼»¯======
									
				if(Motordata.mfr==CW)//=====
				{
					Motordata.bstep.nwstep= poztable[Motordata.injgph]; 
				}//ÕýÎ»ÖÃ==
				if(Motordata.mfr==CCW)//·´Æô¶¯
				{//Motordata.bstep.nwstep=1;  
					Motordata.bstep.nwstep= poztable[Motordata.injgph];
				}
								 
				if(Motordata.bstep.nwstep>=1&&Motordata.bstep.nwstep<=6)
				{
//TIM5_StartCount();				 
					Motordata.station= norrun;
					Motordata.swhkey.killrun=5;		 
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
					Motordata.trcount=50;
					Motordata.tvcount=PSNLV;
//--------------------------------------------------
//==================================================
					if(Motordata.mfr==CW)//ÕýÆô¶¯
					{
						TS_ch_ph(phztable[Motordata.injgph]);//
						Motordata.tqcount=Motordata.tvcount;
					}
					if(Motordata.mfr==CCW)//·´Æô¶¯
					{						 
						TSR_ch_ph( prztable[Motordata.injgph]);//==Î´Ë³ ==							 
						Motordata.tqcount=Motordata.tvcount;		 
					}   
				}
			}

			if( Motordata.injgph==0)
			{
				Motordata.station=Stop;
				Motordata.flgsw=0;
				Adc_Scan_timetrig_init();
				TIM5_ready_StartCount();			 				 
			}					
		} break;		
		
//--------------------------------
//=ÔËÐÐ  =ÐÅºÅÔËÐÐ=====
		case    norrun:
		{
////////////////////////////////////////////			
			//MCTask_ready();

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

			if( Motordata.dswitch==MOTOR_ON)
			{	 
				Motordata.swhkey.killrun=0;
			}
								 
			if( Motordata.dswitch==MOTOR_OFF)		
			{ 
//Motordata.outduty=1;
				ChangeDuty(0);
				Motordata.swhkey.killrun+=1;
							 
				if( Motordata.swhkey.killrun==800)	//800
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
					Motordata.station=ready;
			         	Motordata.flgsw=0;
					Motordata.outduty=1;
					Adc_Scan_timetrig_init();
					TIM5_ready_StartCount();
				}
			}	
//==============================							
			ChangeDuty(Motordata.outduty);
				 
		} break;
		
//---------------------------------
//Òì³£Í£Ö¹=±¨´í×´Ì¬====
		case  stop:
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

			if( Motordata.dswitch==MOTOR_OFF)	
			{ 
				TIM1_CCER2_CC4E =0;
				ChangeDuty(0);
				Motordata.flgsw=0;
				Motordata.outduty=1;
				DisAllPwmOut();
				Motordata.ui.blink=0;
				Motordata.station=ready;
				Adc_Scan_timetrig_init();
				TIM5_ready_StartCount();
			}	
		} break;	
	}
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
