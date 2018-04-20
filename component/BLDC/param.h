/**********************************************************
*name   : mian.c
*detail : include public head file
*version&time: v1.0 (2018-4-1)
*author&team : 王元
***********************************************************/

#ifndef __PARAM_H
#define __PARAM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/*  defines ------------------------------------------------------------------*/
// #define PROJ_SST16_194 
// #define PROJ_SST16_DK
// #define PROJ_SST17_1a1
#define PROJ_SST17_1A4
// #define PROJ_SST17_1B3

#define PWR_DELAY_TIME	80	// 8s

#define FUNC_REVS_STOP_EN
#define FUNC_BREAK_EN

#define VBAT_18V_EN

#ifdef VBAT_18V_EN
#define BAT_VOLT1_ADC   380     // 3.2V
#define BAT_VOLT2_ADC   425     // 3.6V
#define BAT_VOLT3_ADC   450     // 3.9V
#endif

#ifdef VBAT_36V_EN
#define BAT_VOLT1_ADC   409     // 3.2V
#define BAT_VOLT2_ADC   460     // 3.6V
#define BAT_VOLT3_ADC   498     // 3.9V
#endif

// protect dot
// OV
// UV
// most OT
// oc

/*  typedef ------------------------------------------------------------------*/
// 
typedef enum
{
  checkme = 1,
  ready = 2,
  startup = 3,
  startrun = 4,
  norrun = 5,
  fause = 6,
  brake = 7,
  stop = 8
} mstate_t;

//
typedef struct
{
  uint8_t hallnow;
  uint8_t hallold;
  uint8_t hallnext;
  uint8_t halllp;
  uint8_t halllf;
} hall_t;

//
typedef struct
{
  uint8_t nwstep;
  uint8_t nestep;
  uint8_t odstep;
} rstep_t;

//
typedef struct
{
  uint16_t gduty;
  uint16_t mroller;
  uint16_t mledcount;
  uint16_t showstep;
  uint16_t showbuf;
  uint16_t bkcount;
  uint16_t showcount;
  uint16_t showtime;
  uint8_t  adspeedt;
  uint8_t  blink;
  uint8_t  mfrch;
} mui_t;

// 
typedef enum
{
  eno = 0,
  ehall = 6,    // 霍尔错误
  eovp = 3,     // 过压
  eocp = 1,     // 过流
  eoct = 5,     // 过温
  ebkr = 4,     // 堵转
  elvp = 2      // 欠压
} mert_t;

// 
typedef struct
{
  uint8_t mgear;        // 挡位
  uint8_t swkey;
  uint8_t sskey;
  uint8_t sakeyflg;
  uint8_t abkeyflg;
  uint8_t frstop;
  uint8_t tiwno;
  uint8_t tiwoff;
  uint8_t readkey;
  uint8_t spkey;
  uint16_t trdelay;
  uint16_t trdealy1;
  uint16_t onbuf;
  uint16_t ofbuf;
  uint16_t killrun;
} swh_t;

//  
typedef struct
{
  uint8_t clcount;
  uint16_t volt;
  uint16_t anp;
  uint16_t tempr;
  uint16_t mostemp;
  uint16_t mosaddbattemp;
  uint16_t battemp;
  // 二阶滤波
  uint16_t disv;
  uint16_t distp;       // 温度
  uint16_t disvsm;      // 过压
  uint16_t disism;      // 过流
  uint16_t disois;
  
  uint16_t bufovp;      // 欠压保护
  uint16_t bufsep;      // 过压保护
  uint16_t bufocp;      // 过流保护
  uint16_t bufoct;      // 过温保护
} mprc_t;

//
typedef struct
{
  mstate_t station;
  hall_t bhall;
  rstep_t bstep;
  mui_t ui;
  mert_t fault;
  swh_t swhkey;
  mprc_t prct;

  uint16_t outduty;
  uint16_t hopeduty;
  uint16_t trcount;
  uint16_t tqcount;
  uint16_t tvcount;
  uint8_t batpower;
  uint8_t dswitch;
  uint8_t injgph;
  uint8_t mfr;
  uint8_t flgsw;
  uint8_t disstatus;
  uint8_t mstep;
  uint8_t test;
} motorparam_t;

//
typedef struct
{
  uint16_t ADC_inj_o;
  uint16_t ADC_inj_l;
  uint16_t ADC_inj_n;
  uint16_t ADC_inj_ne;
  uint16_t chsptime;
  uint8_t incount;
  uint8_t smcount;
} collect_t;


/*  variables  ---------------------------------------------------------------*/
extern motorparam_t Motordata;
extern collect_t Injection;

extern const uint8_t halltble[];
extern const uint8_t phtable[];
extern const uint8_t LPT[];
extern uint8_t bemfchtable[];
extern uint8_t Tphtable[];
/*  functions ----------------------------------------------------------------*/

#if 0
#ifndef _PARAM_H_
#define _PARAM_H_
#endif
//#include"stm8s_type.h"
#include"public.h"

//方案选择
//#define PROJ_SST16_194
//#define PROJ_SST16_195
//#define PROJ_SST17_DK
//#define PROJ_SST17_1A1  //L
#define PROJ_SST17_1A4  //W
//#define PROJ_SST17_1B3
//no option pwr on delay time
#define PWR_DELAY_TIME   80  //8S
//revs stop function
#define FUNC_REVS_STOP_EN
//break function
#define FUNC_BREAK_EN
//bat volt selection
#define VBAT_18V_EN
//#define VBAT_36V_EN
//BAT cap  VOLT
#ifdef VBAT_18V_EN
////2/17
#define BAT_VOLT1_ADC   380//308//370//380  ////3.2V
#define BAT_VOLT2_ADC   425//420  ////3.6V
#define BAT_VOLT3_ADC   450//462  ////3.9V
#endif
#ifdef VBAT_36V_EN
////1/16
#define BAT_VOLT1_ADC   409  ////3.2V
#define BAT_VOLT2_ADC   460  ////3.6V
#define BAT_VOLT3_ADC   498  ////3.9V
#endif
//protect dot
//OV
#define FUNC_OV_PROTECT_EN
#define OVP_VOLT_ADC   575  //541////4.5V
//UV
#define FUNC_UV_PROTECT_EN
#define UVP_VOLT_ADC   360//370//309//358//365//370  //349////2.9V  //365  //15V
//mos OT
#define FUNC_MOSOT_PROTECT_EN
#define OTP_VOLT_ADC   120  //85
//OC
//hard oc
#define FUNC_HOC_PROTECT_EN
//soft oc
#define FUNC_SOC_PROTECT_EN
//
#define OCP_VOLT_ADC   750  //38a
//LIMIT CURR
#define FUNC_LIMIT_CURR_EN
//
#define LIMIT_CURR_VOLT_ADC    400//330//400//450  //400--15A  //500-18A
#define LIMIT_CURR1_VOLT_ADC 290//240//8A
#define LIMIT_CURR2_VOLT_ADC 330//290//14A
#define LIMIT_CURR3_VOLT_ADC 400//330 //15A//350 //17A //340//16A
 
//grade num pwm para set 
#define SPEED_GRADE_MIN  1
#ifdef PROJ_SST16_195
#define SPEED_GRADE_MAX  2
//
#define GRADE1_PWM_MAX  1110
#define GRADE2_PWM_MAX  1280
#define GRADE3_PWM_MAX  700
#define GRADE4_PWM_MAX  850
#define GRADE5_PWM_MAX  1280
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1130
#define GRADE2_PWM_REVS_MAX  1280 //850
#define GRADE3_PWM_REVS_MAX  1280
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif
#ifdef PROJ_SST16_194
#define SPEED_GRADE_MAX  5
//
#define GRADE1_PWM_MAX  400
#define GRADE2_PWM_MAX  600
#define GRADE3_PWM_MAX  700
#define GRADE4_PWM_MAX  850
#define GRADE5_PWM_MAX  1280
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1200
#define GRADE2_PWM_REVS_MAX  1200 //850
#define GRADE3_PWM_REVS_MAX  1280
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif
//L
#ifdef PROJ_SST17_1A1
#define SPEED_GRADE_MAX  2
//
#define GRADE1_PWM_MAX  700
#define GRADE2_PWM_MAX  1280 //850
#define GRADE3_PWM_MAX  1250
#define GRADE4_PWM_MAX  1000
#define GRADE5_PWM_MAX  1000
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1250
#define GRADE2_PWM_REVS_MAX  1280 //850
#define GRADE3_PWM_REVS_MAX  1250
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif
//W
#ifdef PROJ_SST17_DK
#define SPEED_GRADE_MAX  2
//
#define GRADE1_PWM_MAX  700
#define GRADE2_PWM_MAX  1280 //850
#define GRADE3_PWM_MAX  1270
#define GRADE4_PWM_MAX  1000
#define GRADE5_PWM_MAX  1000
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1280
#define GRADE2_PWM_REVS_MAX  1280 //850
#define GRADE3_PWM_REVS_MAX  1280
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif
//W
#ifdef PROJ_SST17_1A4
#define SPEED_GRADE_MAX  3
//
#define GRADE1_PWM_MAX  900//915  //920
#define GRADE2_PWM_MAX  1050//1000 //850
#define GRADE3_PWM_MAX  1250//1150//1200//1280
#define GRADE4_PWM_MAX  1000
#define GRADE5_PWM_MAX  1000
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1280//1200//1280
#define GRADE2_PWM_REVS_MAX  1280//1200//1280 //850
#define GRADE3_PWM_REVS_MAX  1280//1200//1280
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif
#ifdef PROJ_SST17_1B3
#define SPEED_GRADE_MAX  2
//
#define GRADE1_PWM_MAX  600
#define GRADE2_PWM_MAX  1280 //850
#define GRADE3_PWM_MAX  1280
#define GRADE4_PWM_MAX  1000
#define GRADE5_PWM_MAX  1000
#define GRADE6_PWM_MAX  1000
#define GRADE7_PWM_MAX  1000
#define GRADE8_PWM_MAX  1000
#define GRADE1_PWM_REVS_MAX  1280
#define GRADE2_PWM_REVS_MAX  1280 //850
#define GRADE3_PWM_REVS_MAX  1280
#define GRADE4_PWM_REVS_MAX  1000
#define GRADE5_PWM_REVS_MAX  1000
#define GRADE6_PWM_REVS_MAX  1000
#define GRADE7_PWM_REVS_MAX  1000
#define GRADE8_PWM_REVS_MAX  1000
#endif

/******************************************************
*------------- data typedef----------------------------
*******************************************************/
//状态机的状态值定义，枚举========================
typedef  enum  mstate
{
 Checkme=1,
 Ready=2,
 Startup=3,
 StartRun=4,
 NorRun=5,
 Fause=6,
 Brake=7,
 Stop=8
}mstate;
/**********************************************************/
//定义一个结构体数据类型，主要用于存储adc相关数据==========
//----------------------------------------------------------
//定义一个结构体数据类型，用于系统运行的主要参数存储========
typedef  struct collect
{
//-----------------------
 u16 ADC_inj_o;
 u16 ADC_inj_l;
 s16 ADC_inj_n;
 s16 ADC_inj_ne;
//-----------------------
 u8  incount; 
 u16 chsptime;
 u8 smcount;
}collect;   
 
//============================================================
//************************************************************
typedef  struct hall
{   
//==================
 u8  Hallnow;    
 u8  Hallold;
 u8  hallnext;
 u8  halllp;
 u8  halllf;
                          
}hall;

//************************************************************
typedef  struct Rstep
{ 
 u8  nwstep;
 u8  nestep;
 u8  odstep;
}Rstep;
//============================================================
          
/***********************************************************/
typedef  struct Mprc
{ 
 u8   clcount; 
 u16  Volt;
 u16  Anp;
 u16  Tempr;
// 
 u16  MosTemp;
 u16  MosAddBatTemp;
 u16  BatTemp; 
//==二阶滤波=======
 u16  DISv;
 u16  DIStp;//温度
 
 u16  DISvsm;//过压
 u16  DISism;//过流
 u16  DISois;//
           
//======================
 u16  bufovp;//欠压保护
 u16  bufsep;//过压保护
 u16  bufocp;//过流保护
 u16  bufoct;//过温保护
}Mprc;
/********************************************/     
           
typedef  enum   Mert
{  
 eNO=0,
 //  eHall=6,  //霍尔错误
 eOvp=3,   //过压
 eOcp=1,   // 过流
 eOct=5,   //过温
 eBkr=4,   // 堵转
 elvp=2    //欠压
}Mert; 
           
           
/****************************************************/  
typedef   struct  swh
{
 u8   Mgear;//==档位===
 u8   SWkey;//
 u8   SSkey;
 u16  TRdelay;
 u16  TRdelay1; 
 u8   sakeyflg;
 u8   sbkeyflg;
 u8   FRstop;
 u8   TIWNO;
 u8   TIWOFF;
 u16  ONbuf;
 u16  OFbuf;
 u16  KILLrun;
 u8  readkey;
 u8  spkey;
            
}swh;
           
/***************************************************/    
typedef    struct Mui
{
 u16    Gduty;
 u16    Mroller;
 u16    Mledcount;
 u16    showstep;
 u16    showbuf;
 u16    BKcount;
 u8     adspeedt;
 u16    showcount;
 u16    showtime;
//====================
 u8     Blink;
 u8     MFRch;
}Mui;           
           
/**********************************************************/
//定义一个结构体数据类型，用于系统运行的主要参数存储======= 
typedef  struct  prarm
{
//状态机=============
 mstate station;
 hall   bHall; 
 Rstep  bstep;
 Mui     UI; 
 Mert   fault;
 swh    SWhkey;
 Mprc   prct   ;
 u8     BatPower;
 s16    outduty;
 u16    hopeduty;
 u8     Dswitch;
 u8     INJGPH;
 u8     MFR;
 u8     Flgsw;
 u8     Disstatus;
 u8    mstep;
 u8    test;       
 u16    TRcount;
 u16    TQcount;
 u16    TVcount;
            
}param; 
/***********************************************************/
/*de  extern  param
************************************************************/
//全局变量声明==============================================
extern    param  Motordata;
extern    collect Injection;
/***************************/
 
extern         u8 pz_buf;
extern const   halltable[];
extern const   phtable[];
extern         bemfchtable[];
extern         Tphtable[];
extern const   LPT[];
/***********************************************************/
/***********************************************************/
//函数声明===================================================
#endif

#endif