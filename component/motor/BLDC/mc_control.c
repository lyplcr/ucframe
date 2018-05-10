/**********************************************************
*name   : mc_control.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "public.h"
//#include "adc.h"
//#include "tim.h"
//#include "gpio.h"
#include "param.h"
#include "mc_driver.h"
#include "mc_control.h"
#include "inject.h"
#include "mswitch.h"
#include "mc_config.h"
#include "mdisply.h"


/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
//=========================================
const uint8_t halltable[]={0,1,5,4,6,2,3,0};
//-------------------------------------------
//换相顺序表---------------------------------
const uint8_t phtable[]={0,1,6,5,2,4,3,0};
//==========================================
//正向运行换相------------------------------
//  ab,ba,cb,bc,ca,ac
const uint8_t Fphtable[]={0,1,6,5,2,4,3,0};//正换相
//==========================================
//反向运行换相------------------------------
const uint8_t Rphtable[]={0,5,4,1,3,6,2,0};//反换相
//******************************************

//******************************************
//------------------------------------------
const uint8_t poztable[]={0,1,2,4,5,6,3,0};//停车位置
//实际的停车位置表书法======================
//{0,1,2,4,5,0,3,0};//停车位
//------------------------------------------
const uint8_t phztable[]={0,1,3,5,5,6,3,0};//正加速
//{0,6,1,5,5,6,3,0}
//------------------------------------------
const uint8_t prztable[]={0,6,3,5,5,6,3,0};//反加速

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

/*  functions ----------------------------------------------------------------*/


/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/

//-----------------------------------------


/******************************************************************
*
*说明  ：公共部分程序段，并行运行与状态机
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
    if( (Motordata.SWhkey.FRstop==0xaa) && (Motordata.SWhkey.Mgear == 2) )
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
    if(Motordata.SWhkey.FRstop==0xaa)
    {   
      if(Motordata.UI.roller>1 && Motordata.prct.Anp<240)
      { 
        Motordata.UI.roller -= 1;
      }
      if( Motordata.prct.Anp >= 240)
      {
        Motordata.UI.roller = 450;
      }
      if(Motordata.UI.roller <= 2)
      {
        Motordata.UI.blink = 0;
        Motordata.UI.roller = 450;
        Motordata.station = Stop;
      }
    }
  }
#endif
#endif
}

// 
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

// 
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

// 
void dlay (u16 d)
{  
  u16 u,y;
  
  u=d;      //1.5us
  for(y=0;y<u;y++); 		  
}
		
// 
void MCTask_Ready()
{   
  if( Motordata.Dswitch==MOTOR_ON)
  {
    Motordata.UI.roller=700;
    GPIOD->ODR |= 0x04;     // PD2_OUT=1;
    Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
    Motordata.station=Startup;
    dlay(30);
		
    Motordata.prct.DISv= Motordata.prct.Volt;
    Motordata.prct. DIStp=Motordata.prct.Tempr;//温度
    //Motordata.prct. DIStp = Motordata.prct.MosTemp;
    //Motordata.prct. DIStp = Motordata.prct.MosAddBatTemp;
//   Motordata.prct.DISvsm;//过压
//   Motordata.prct.DISism;//过流
//   Motordata.prct.DISois;//
    check_erorr();
  }
  DisAllPwmOut();
}
//========================================================

void MCTask_Start()
{
  //==脉枕注入============
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
    //==解析=============
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
    GPIOC->ODR |= 0xf0;     //PC_ODR=0xf0;

    dlay(100);
  }
  //-----------------------------
}
//======================================================

#if 0
void MCTask_NorRun(void)
{
  uint8_t  bemf;
  uint8_t cbuf;
  
  bemf=Get_pa_vhl();
//--获得检测权限--启动检测--
//PB7_OUT= ~PB7_OUT;
  if(Motordata.MFR==CW)  
  {
    switch(Motordata.bstep.nwstep)
    {
      //001
      //fbemfb//ab
    case  PSN1:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep=PSN2;
        TS_ch_ph(PSN1);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //101
      //rbemfc//cb
    case  PSN2:
      Motordata.bstep.odstep= bemf&0x04;
      if(Motordata.bstep.odstep==0x04)
      { 
        Motordata.bstep.nwstep= PSN3;
        TS_ch_ph(PSN2);
        TS_lpv();
        Motordata.TRcount=0;
      }//4//4
      break;
      //100
      //fbemfa//ca
    case  PSN3:
      Motordata.bstep.odstep= bemf&0x01;
      if(Motordata.bstep.odstep==0x00)	
      {	
        Motordata.bstep.nwstep= PSN4;
        TS_ch_ph(PSN3);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //110
      //rbemfb//ba
    case  PSN4:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x02)
      {
        Motordata.bstep.nwstep= PSN5;
        TS_ch_ph(PSN4);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //010
      //fbemfc//bc
    case  PSN5:
      Motordata.bstep.odstep= bemf&0x04;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep= PSN6;
        TS_ch_ph(PSN5);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //011
      //rbemfa//ac
    case  PSN6:
      Motordata.bstep.odstep= bemf&0x01;
      if(Motordata.bstep.odstep==0x01)
      {	  
        Motordata.bstep.nwstep= PSN1;
        TS_ch_ph(PSN6);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
    }
  }
  if(Motordata.MFR==CCW)  
  {
    switch(Motordata.bstep.nwstep)
    {
      //001
      //fbemfc//ac
    case  PSN1:
      Motordata.bstep.odstep= bemf&0x04;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep=PSN2;
        TSR_ch_ph(PSN1);     //ac
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //011
      //rbemfb//bc
    case  PSN2:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x02)
      { 
        Motordata.bstep.nwstep= PSN3;
        TSR_ch_ph(PSN2);//bc
        TS_lpv();
        Motordata.TRcount=0;
      }//4//4
      break;
      //010
      //fbemfa//ba
    case  PSN3:
      Motordata.bstep.odstep= bemf&0x01;//a
      if(Motordata.bstep.odstep==0x00)	
      {	
        Motordata.bstep.nwstep= PSN4;
        TSR_ch_ph(PSN3);//ba
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //110
      //rbemfc//ca
    case  PSN4:
      Motordata.bstep.odstep= bemf&0x04;//c
      if(Motordata.bstep.odstep==0x04)
      {  
        Motordata.bstep.nwstep= PSN5;
        TSR_ch_ph(PSN4);//ca
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //100
      //fbemfb//cb
    case  PSN5:
      Motordata.bstep.odstep= bemf&0x02;//b
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep= PSN6;
        TSR_ch_ph(PSN5);//cb
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //101
      //rbemfa//ab
    case  PSN6:
      Motordata.bstep.odstep= bemf&0x01;//a
      if(Motordata.bstep.odstep==0x01)
      {	  
        Motordata.bstep.nwstep= PSN1;
        TSR_ch_ph(PSN6);//ab
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
    }
  }
}
#endif


// 
void MCTask_NorRun1()
{
  uint8_t bemf, cbuf;
  
  bemf = Get_pa_vhl();
  
  //PB7_OUT= ~PB7_OUT;
  if(Motordata.MFR==CW)  
  {
    switch(Motordata.bstep.nwstep)
    {
    //001
    //fbemfb //ab
    case  PSN1:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep=PSN2;
        TS_ch_ph(PSN1);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
    //101
    //rbemfc //cb
    case  PSN2:
      Motordata.bstep.odstep = bemf&0x04;
      if(Motordata.bstep.odstep==0x04)
      { 
        Motordata.bstep.nwstep= PSN3;
        TS_ch_ph(PSN2);
        TS_lpv();
        Motordata.TRcount=0;
      }//4//4
      break;
      //100
      //fbemfa//ca
    case  PSN3:
      Motordata.bstep.odstep = bemf&0x01;
      if(Motordata.bstep.odstep==0x00)	
      {	
        Motordata.bstep.nwstep= PSN4;
        TS_ch_ph(PSN3);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //110
      //rbemfb//ba
    case  PSN4:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x02)
      {
        Motordata.bstep.nwstep= PSN5;
        TS_ch_ph(PSN4);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //010
      //fbemfc//bc
    case  PSN5:
      Motordata.bstep.odstep= bemf&0x04;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep= PSN6;
        TS_ch_ph(PSN5);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //011
      //rbemfa//ac
    case  PSN6:
      Motordata.bstep.odstep= bemf&0x01;
      if(Motordata.bstep.odstep==0x01)
      {	  
        Motordata.bstep.nwstep= PSN1;
        TS_ch_ph(PSN6);
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
    }
  }

  if(Motordata.MFR==CCW)  
  {
    switch(Motordata.bstep.nwstep)
    {
      //001
      //fbemfc//ac
    case  PSN1:
      Motordata.bstep.odstep= bemf&0x04;
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep=PSN2;
        TSR_ch_ph(PSN1);     //ac
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //011
      //rbemfb//bc
    case  PSN2:
      Motordata.bstep.odstep= bemf&0x02;
      if(Motordata.bstep.odstep==0x02)
      { 
        Motordata.bstep.nwstep= PSN3;
        TSR_ch_ph(PSN2);//bc
        TS_lpv();
        Motordata.TRcount=0;
      }//4//4
      break;
      //010
      //fbemfa//ba
    case  PSN3:
      Motordata.bstep.odstep= bemf&0x01;//a
      if(Motordata.bstep.odstep==0x00)	
      {	
        Motordata.bstep.nwstep= PSN4;
        TSR_ch_ph(PSN3);//ba
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //110
      //rbemfc//ca
    case  PSN4:
      Motordata.bstep.odstep= bemf&0x04;//c
      if(Motordata.bstep.odstep==0x04)
      {  
        Motordata.bstep.nwstep= PSN5;
        TSR_ch_ph(PSN4);//ca
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //100
      //fbemfb//cb
    case  PSN5:
      Motordata.bstep.odstep= bemf&0x02;//b
      if(Motordata.bstep.odstep==0x00)
      {
        Motordata.bstep.nwstep= PSN6;
        TSR_ch_ph(PSN5);//cb
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
      //101
      //rbemfa//ab
    case  PSN6:
      Motordata.bstep.odstep= bemf&0x01;//a
      if(Motordata.bstep.odstep==0x01)
      {	  
        Motordata.bstep.nwstep= PSN1;
        TSR_ch_ph(PSN6);//ab
        TS_lpv();
        Motordata.TRcount=0;
      }
      break;
    }
  }
}


// 停止状态
void MCTask_Stop()
{
  DisAllPwmOut();
  // switch()
  if( Motordata.Dswitch==MOTOR_ON)
  {
  }
}

// 状态机部分的运行程序，与公用程序部分并行
void Motor_Run(void)
{ 
  switch(Motordata.station)
  {
    case Ready:         // 等待状态
      {  //==检测是否运行======= 
        if(Get_sw_fr()==0)      // 判断正反转
        {
          Motordata.MFR = SW_POS;			//CW	
        }
        if(Get_sw_fr()==1)
        { 
          Motordata.MFR = SW_REVS;			//CCW
        }
        
        if(Motordata.UI.MFRch != Motordata.MFR)
        {
          Motordata.UI.MFRch = Motordata.MFR;
          Motordata.UI.duty = EVERY_GRADE_PWM_MAX_TAB1[Motordata.SWhkey.gear];
          if(Motordata.MFR == DIR_REVS) 
          {
            Motordata.UI.duty = EVERY_GRADE_PWM_REVS_MAX_TAB1[Motordata.SWhkey.gear];
          }
          Motordata.SWhkey.TRdelay = PWR_DELAY_TIME;
        }
        if( Motordata.Dswitch == MOTOR_OFF)
        {	 
          Motordata.Flgsw=1;
        }			
        MC_Swbut_Check();       // 按键开关
        bskill_run();		
        MCTask_Ready();
        DisAllPwmOut();	
      } break;
  case  Startup:        //获得第一步的位置识别
    {
      GPIOC->ODR &= 0x1f;   // PC6_OUT=0;PC5_OUT=0;PC7_OUT=0;
      pwm_reset();
      MCTask_Start();	
      if( Motordata.mstep == Motordata.INJGPH)
      {
        Motordata.station = StartRun;
      }
      if( Motordata.mstep!=Motordata.INJGPH)	
      {
        Motordata.station=Ready;
        Motordata.Flgsw=1;
        TIM5_Ready_StartCount();
        Adc_Scan_timetrig_init();
      }
    } break;	
  case StartRun:        //加速同步启动
    {
      if( Motordata.INJGPH!=0)
      {   
        PWM_INIT();//==重新初始化
        if(Motordata.MFR==CW)
        {
          Motordata.bstep.nwstep= poztable[Motordata.INJGPH]; 
        }//正位置
        if(Motordata.MFR==CCW)//反启动
        {//Motordata.bstep.nwstep=1;  
          Motordata.bstep.nwstep= poztable[Motordata.INJGPH];
        }
        if(Motordata.bstep.nwstep>=1&&Motordata.bstep.nwstep<=6)
        {
//TIM5_StartCount();			
          Motordata.station= NorRun;
          Motordata.SWhkey.KILLrun=5;		 
 //setup ch4
          TIM1->CCMR4 = 0x68;     // TIM1_CCMR4=0x68;
          TIM1->CCER2 |= 0x30;    // TIM1_CCER2_CC4P =1;TIM1_CCER2_CC4E =1;
          Motordata.outduty=50;
          //adc  pwm trig 
          Adc_Scan_pwmtrig_init();
          Adc_Start();
          Motordata.TRcount=50;
          Motordata.TVcount=PSNLV;
          
          if(Motordata.MFR==CW)//正启动
          {
            TS_ch_ph(phztable[Motordata.INJGPH]);
            Motordata.TQcount=Motordata.TVcount;
          }
          if(Motordata.MFR==CCW)//反启动
          {					
            TSR_ch_ph( prztable[Motordata.INJGPH]);//==未顺 
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
  case NorRun:    // 运行
    {
      //MCTask_Ready();
      Motordata.prct.DISv= Motordata.prct.Volt;
      Motordata.prct. DIStp=Motordata.prct.Tempr;//温度
      Motordata.prct. DIStp = Motordata.prct.MosTemp;
      Motordata.prct. DIStp = Motordata.prct.MosAddBatTemp;
      check_erorr();
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
          TIM1->CCER2 &= 0xef;  // TIM1_CCER2_CC4E =0;
          ChangeDuty(1);
          DisAllPwmOut();
#ifdef	FUNC_BREAK_EN
          GPIOC->ODR |= 0xe0;     // PC6_OUT=1; PC5_OUT=1; PC7_OUT=1;	
#else
          GPIOC->ODR &= 0x1f;   // PC6_OUT=0;PC5_OUT=0;PC7_OUT=0;
#endif					
          //js170720 dlay (4000);
          dlay (4000);
          GPIOC->ODR &= 0x1f;     // PC6_OUT=0; PC5_OUT=0; PC7_OUT=0;
          Motordata.station=Ready;
          Motordata.Flgsw=0;
          Motordata.outduty=1;
          Adc_Scan_timetrig_init();
          TIM5_Ready_StartCount();
        }
      }	
      ChangeDuty(Motordata.outduty);
    } break;
  case  Stop://异常停止=报错状态====
    {
//EBrake();//=MISTAKE;
      MCTask_Stop();	
//报错===============	
      ChangeDuty(0);	
//      if(Motordata.fault != 0)
//      {
//        PD2_OUT=0;
//      }
//      else
//      {
//        PD2_OUT=1;
//      }		
      if( Motordata.Dswitch==MOTOR_OFF)	
      { 
        TIM1->CCER2 &= 0xef;  // TIM1_CCER2_CC4E =0;				
        ChangeDuty(0);
        Motordata.Flgsw=0;
        Motordata.outduty=1;
        DisAllPwmOut();
        Motordata.UI.blink = 0;
        Motordata.station = Ready;
        Adc_Scan_timetrig_init();
        TIM5_Ready_StartCount();
      }	
    } break;
  }
}


