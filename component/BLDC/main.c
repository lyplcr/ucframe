/***************************************************************
*-------------------- 脉动定位启动版----------------------------
*电机      ：  motor volt:18vdc----------------------------
*应用      ：  无感无刷电动扳手----------------------------
*版本&时间 ：  v3.0 8月5日---------------------------------
*硬件版本  ：  SST15-461-1.1-------------------------------
*--------------------------------------------------------------
**************************************************************/

/*======================================
*BLDCM  CONTROL  SYSTERM  FOR ETOOLS
*TWO  POLOS  VDC 18V  20000RPM SPEED
**************************************/
//=======================================
#include "stm8s903k.h"
#include "stm8s_type.h"
#include "stm8_bit.h"
#include "public.h"
//=======================================
#include "mc_config.h"
#include "adc.h"
#include "mc_control.h"
#include "param.h"
#include "mswitch.h"
#include "tim.h"
#include "mdisply.h"
/****************************************/
#define  MCU    _sys_903_
#define  CMP     PACE_WL
//==============================


//==全局数据结构封装=============
param   Motordata;
collect Injection;
//===函数声明部分使用============
void UI_Functiong_init(void);


//===初始化临时调试添加==========
void UI_Functiong_init()
{

//===轻触开关检查寄存器初始化===
	Motordata.SWhkey.sakeyflg=0;
	Motordata.SWhkey.SSkey=0;
	Motordata.SWhkey.SWkey=0;
//===Ready定时器初始化==========	



//====adc检测模式初始化=========
	 Adc_Scan_timetrig_init();
	 TIM5_Ready_StartCount();
	 Adc_Start();
	 
//=====开关延迟初始化===========	
	Motordata.SWhkey.ONbuf=0;
	Motordata.SWhkey.OFbuf=0;
	PD4_OUT=0;
	PD2_OUT=0;
	//Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
//==============================
  //看门狗初始化
	 dlay (50000);
	 Motordata.UI.BKcount=0;
	 Motordata.UI.adspeedt=3;
	 Motordata.UI.Blink=0;	
	 
//========================
	if(Get_sw_fr()==0)	//=判断正反转==
	{ 
		Motordata.MFR=SW_POS;			//CW		
	}
	if(Get_sw_fr()==1)
	{ 
		Motordata.MFR=SW_REVS;			//CCW
	}//---------
								
	Motordata.UI.MFRch= Motordata.MFR;
								
	PD2_OUT=1;
	Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
  //中断优先级初始化============
	Motordata.prct.clcount=0;
//===显示寄存器初始化===========
	Motordata.Disstatus=6;
	 //====================
	Motordata.prct. DIStp=0;
	Motordata.prct.DISvsm=0;
	Motordata.prct.DISism=0;
	Motordata.prct.DISois=0;
//=============================	 
//==读eeprom===================
	Motordata.UI.Mroller=450;
	read_eeprom_vla();
#ifdef	PROJ_SST16_195
	Motordata.SWhkey.FRstop=0xaa;
#endif   
}




//=============================

main()
{
  	u8 usx;
 //===系统 初始化控制========
	Sys_Init();

 //===电机系统初始化=========
	Motor_Init();
 
//==控制板＃外设初始化======
	UI_Functiong_init();
	 
 //===等待电压稳定===========
	Motordata.Dswitch=MOTOR_OFF;
	dlay (50000);
	
	 // _asm("sim");
	// Motordata.Flgsw=1;
	
	while (1)
	{	
	//	MCTask_Start();
	 
			
//一级完全保护程序段 *********
		Motor_ip();
			  
//开关 状态读取*******
		Check_switch_onff();
	
//电机运行保护********
			  
		if( Motordata.station==Stop&&Motordata.UI.Blink>0)   
		{     
			usx= showsp[Motordata.UI.showcount];
		       if(usx==1)
			{ 
				Disp_error_on();  
			}
			else
			{ 
				Disp_error_of();  
			}	
		}
		 
//电机运行状态--------
		Motor_Run();
	}

}














