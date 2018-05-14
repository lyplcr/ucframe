/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

#ifndef _PARAM_H_
#define _PARAM_H_


/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/*  defines&macro ------------------------------------------------------------*/
//#define PROJ_SST16_194
//#define PROJ_SST16_195
//#define PROJ_SST17_DK
//#define PROJ_SST17_1A1	//L
#define PROJ_SST17_1A4		//W
//#define PROJ_SST17_1B3

//no option pwr on delay time
#define	PWR_DELAY_TIME	80	//8S

//revs stop function
#define	FUNC_REVS_STOP_EN
//break function
#define	FUNC_BREAK_EN
// 
//bat volt selection
#define	VBAT_18V_EN
//#define VBAT_36V_EN

//BAT cap  VOLT
#ifdef	VBAT_18V_EN
////2/17
#define	BAT_VOLT1_ADC			380     //308//370//380	////3.2V
#define	BAT_VOLT2_ADC			425     //420		////3.6V
#define	BAT_VOLT3_ADC			450     //462		////3.9V
#endif

#ifdef	VBAT_36V_EN
////1/16
#define	BAT_VOLT1_ADC			409		////3.2V
#define	BAT_VOLT2_ADC			460		////3.6V
#define	BAT_VOLT3_ADC			498		////3.9V
#endif

//protect dot
//OV
#define	FUNC_OV_PROTECT_EN
#define	OVP_VOLT_ADC			575		//541////4.5V

//UV
#define	FUNC_UV_PROTECT_EN
#define	UVP_VOLT_ADC			360//370//309//358//365//370		//349////2.9V		//365		//15V

//mos OT
#define	FUNC_MOSOT_PROTECT_EN
#define	OTP_VOLT_ADC			120		//85

//OC
//hard oc
#define	FUNC_HOC_PROTECT_EN
//soft oc
#define	FUNC_SOC_PROTECT_EN
//
#define	OCP_VOLT_ADC			750		//38a 最大电流

//LIMIT CURR
#define	FUNC_LIMIT_CURR_EN
//
#define	LIMIT_CURR_VOLT_ADC	400//330//400//450		//400--15A		//500-18A
#define	LIMIT_CURR1_VOLT_ADC	290//240//8A
#define	LIMIT_CURR2_VOLT_ADC	330//290//14A
#define	LIMIT_CURR3_VOLT_ADC	400//330	//15A//350	//17A	//340//16A

//grade num pwm para set 

#define	SPEED_GRADE_MIN		1

//#ifdef	PROJ_SST16_195
//#define	SPEED_GRADE_MAX		2
//#define	GRADE1_PWM_MAX		1110
//#define	GRADE2_PWM_MAX		1280
//#define	GRADE3_PWM_MAX		700
//#define	GRADE4_PWM_MAX		850
//#define	GRADE5_PWM_MAX		1280
//#define	GRADE6_PWM_MAX		1000
//#define	GRADE7_PWM_MAX		1000
//#define	GRADE8_PWM_MAX		1000
//#define	GRADE1_PWM_REVS_MAX		1130
//#define	GRADE2_PWM_REVS_MAX		1280	//850
//#define	GRADE3_PWM_REVS_MAX		1280
//#define	GRADE4_PWM_REVS_MAX		1000
//#define	GRADE5_PWM_REVS_MAX		1000
//#define	GRADE6_PWM_REVS_MAX		1000
//#define	GRADE7_PWM_REVS_MAX		1000
//#define	GRADE8_PWM_REVS_MAX		1000
//#endif

//#ifdef	PROJ_SST16_194
//#define	SPEED_GRADE_MAX		5
//#define	GRADE1_PWM_MAX		400
//#define	GRADE2_PWM_MAX		600
//#define	GRADE3_PWM_MAX		700
//#define	GRADE4_PWM_MAX		850
//#define	GRADE5_PWM_MAX		1280
//#define	GRADE6_PWM_MAX		1000
//#define	GRADE7_PWM_MAX		1000
//#define	GRADE8_PWM_MAX		1000
//#define	GRADE1_PWM_REVS_MAX		1200
//#define	GRADE2_PWM_REVS_MAX		1200	//850
//#define	GRADE3_PWM_REVS_MAX		1280
//#define	GRADE4_PWM_REVS_MAX		1000
//#define	GRADE5_PWM_REVS_MAX		1000
//#define	GRADE6_PWM_REVS_MAX		1000
//#define	GRADE7_PWM_REVS_MAX		1000
//#define	GRADE8_PWM_REVS_MAX		1000
//#endif

//L
//#ifdef	PROJ_SST17_1A1
//#define	SPEED_GRADE_MAX		2
//#define	GRADE1_PWM_MAX		700
//#define	GRADE2_PWM_MAX		1280	//850
//#define	GRADE3_PWM_MAX		1250
//#define	GRADE4_PWM_MAX		1000
//#define	GRADE5_PWM_MAX		1000
//#define	GRADE6_PWM_MAX		1000
//#define	GRADE7_PWM_MAX		1000
//#define	GRADE8_PWM_MAX		1000
//#define	GRADE1_PWM_REVS_MAX		1250
//#define	GRADE2_PWM_REVS_MAX		1280	//850
//#define	GRADE3_PWM_REVS_MAX		1250
//#define	GRADE4_PWM_REVS_MAX		1000
//#define	GRADE5_PWM_REVS_MAX		1000
//#define	GRADE6_PWM_REVS_MAX		1000
//#define	GRADE7_PWM_REVS_MAX		1000
//#define	GRADE8_PWM_REVS_MAX		1000
//#endif

//W
//#ifdef	PROJ_SST17_DK
//#define	SPEED_GRADE_MAX		2
//#define	GRADE1_PWM_MAX		700
//#define	GRADE2_PWM_MAX		1280	//850
//#define	GRADE3_PWM_MAX		1270
//#define	GRADE4_PWM_MAX		1000
//#define	GRADE5_PWM_MAX		1000
//#define	GRADE6_PWM_MAX		1000
//#define	GRADE7_PWM_MAX		1000
//#define	GRADE8_PWM_MAX		1000
//#define	GRADE1_PWM_REVS_MAX		1280
//#define	GRADE2_PWM_REVS_MAX		1280	//850
//#define	GRADE3_PWM_REVS_MAX		1280
//#define	GRADE4_PWM_REVS_MAX		1000
//#define	GRADE5_PWM_REVS_MAX		1000
//#define	GRADE6_PWM_REVS_MAX		1000
//#define	GRADE7_PWM_REVS_MAX		1000
//#define	GRADE8_PWM_REVS_MAX		1000
//#endif

//W
#ifdef	PROJ_SST17_1A4
#define	SPEED_GRADE_MAX		3
#define	GRADE1_PWM_MAX		900     //915		//920
#define	GRADE2_PWM_MAX		1050    //1000	//850
#define	GRADE3_PWM_MAX		1250    //1150//1200//1280
#define	GRADE4_PWM_MAX		1000
#define	GRADE5_PWM_MAX		1000
#define	GRADE6_PWM_MAX		1000
#define	GRADE7_PWM_MAX		1000
#define	GRADE8_PWM_MAX		1000
#define	GRADE1_PWM_REVS_MAX     1280    //1200//1280
#define	GRADE2_PWM_REVS_MAX	1280    //1200//1280	//850
#define	GRADE3_PWM_REVS_MAX	1280    //1200//1280
#define	GRADE4_PWM_REVS_MAX	1000
#define	GRADE5_PWM_REVS_MAX	1000
#define	GRADE6_PWM_REVS_MAX	1000
#define	GRADE7_PWM_REVS_MAX	1000
#define	GRADE8_PWM_REVS_MAX	1000
#endif

//#ifdef	PROJ_SST17_1B3
//#define	SPEED_GRADE_MAX		2
//#define	GRADE1_PWM_MAX		600
//#define	GRADE2_PWM_MAX		1280	//850
//#define	GRADE3_PWM_MAX		1280
//#define	GRADE4_PWM_MAX		1000
//#define	GRADE5_PWM_MAX		1000
//#define	GRADE6_PWM_MAX		1000
//#define	GRADE7_PWM_MAX		1000
//#define	GRADE8_PWM_MAX		1000
//#define	GRADE1_PWM_REVS_MAX		1280
//#define	GRADE2_PWM_REVS_MAX		1280	//850
//#define	GRADE3_PWM_REVS_MAX		1280
//#define	GRADE4_PWM_REVS_MAX		1000
//#define	GRADE5_PWM_REVS_MAX		1000
//#define	GRADE6_PWM_REVS_MAX		1000
//#define	GRADE7_PWM_REVS_MAX		1000
//#define	GRADE8_PWM_REVS_MAX		1000
//#endif


/*  typedef ------------------------------------------------------------------*/
// 电机状态机
typedef  enum mstate
{
  Checkme       = 1,
  Ready         = 2,
  Startup       = 3,
  StartRun      = 4,
  NorRun        = 5,
  Fause         = 6,
  Brake         = 7,
  Stop          = 8,
} state_t;

// ADC相关数据
typedef  struct collect
{
  uint16_t ADC_inj_o;
  uint16_t ADC_inj_l;
  int16_t ADC_inj_n;
  int16_t ADC_inj_ne;
  uint16_t chsptime;
  uint8_t incount; 
  uint8_t smcount;
} collect_t;			

// 霍尔信息
typedef  struct hall
{
  uint8_t  Hallnow;
  uint8_t  Hallold;
  uint8_t  hallnext;
  uint8_t  halllp;
  uint8_t  halllf;
  uint8_t fill1;
  uint8_t fill2;
  uint8_t fill3;
} hall_t;

// 
typedef  struct Rstep
{
  uint8_t nwstep;
  uint8_t nestep;
  uint8_t odstep;
  uint8_t fill;
} rstep_t;

// 
typedef  struct Mprc
{
  uint8_t fill;
  uint8_t clcount;
  uint16_t  Volt;
  uint16_t  Anp;
  uint16_t  Tempr;
  uint16_t  MosTemp;
  uint16_t  MosAddBatTemp;
  uint16_t  BatTemp;	
  uint16_t  DISv;       // 二阶滤波
  uint16_t  DIStp;      // 温度
  uint16_t  DISvsm;     // 过压
  uint16_t  DISism;     // 过流
  uint16_t  DISois;
  uint16_t  bufovp;     // 欠压保护
  uint16_t  bufsep;     // 过压保护
  uint16_t  bufocp;     // 过流保护
  uint16_t  bufoct;     // 过温保护
} mprc_t;

// 
typedef  enum   Mert
{
  eNO   = 0,    // 
  eOcp  = 1,    // 过流
  elvp  = 2,    // 欠压
  eOvp  = 3,    // 过压
  eBkr  = 4,    // 堵转
  eOct  = 5,    // 过温
  ehall = 6,    // 霍尔错误
} ert_t;	

// 
typedef struct swh
{
  uint8_t gear;        // 档位
  uint8_t swkey;
  uint8_t sskey;
  uint8_t sakeyflg;
  uint8_t sbkeyflg;
  uint8_t FRstop;
  uint8_t TIWNO;
  uint8_t TIWOFF;
  uint8_t readkey;
  uint8_t spkey;
  uint16_t  TRdelay;
  uint16_t  TRdelay1;
  uint16_t  ONbuf;
  uint16_t  OFbuf;
  uint16_t  KILLrun;
} swh_t;
							
// LED显示用
typedef struct Mui
{
  uint16_t duty;
  uint16_t roller;
  uint16_t ledcount;
  uint16_t showstep;
  uint16_t showbuf;
  uint16_t bkcount;
  uint16_t showcount;
  uint16_t showtime;
  uint8_t adspeedt;
  uint8_t blink;
  uint8_t MFRch;
  uint8_t fill;
} ui_t;						 

// 系统运行的主要参数集合
typedef struct prarm
{
  state_t station;
  rstep_t bstep;
  mprc_t  prct; // 要存储？
  hall_t  bHall; 
  swh_t   SWhkey;  
  ert_t   fault;
  ui_t    UI;	 
  uint16_t hopeduty;
  uint16_t TRcount;
  uint16_t TQcount;
  uint16_t TVcount;
  int16_t  outduty;  
  uint8_t  BatPower;
  uint8_t  Dswitch;     // 开关状态
  uint8_t  INJGPH;
  uint8_t  MFR;
  uint8_t  Flgsw;
  uint8_t  Disstatus;
  uint8_t  mstep;
  uint8_t  test;						 							 
} param_t;

/*  variables&constants  -----------------------------------------------------*/
extern param_t  Motordata;
extern collect_t Injection;
extern uint8_t pz_buf;
extern uint8_t  bemfchtable[];
extern uint8_t  Tphtable[];
extern const uint8_t  halltable[];
extern const uint8_t  phtable[];
extern const uint8_t  LPT[];

#endif

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/