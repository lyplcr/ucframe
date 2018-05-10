/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

#ifndef _MC_CONTROL_H_
#define _MC_CONTROL_H_


/* Includes ------------------------------------------------------------------*/

/*  defines&macro ------------------------------------------------------------*/
// 启动参数
#define  POWER_OFF_PWM  100     //关机最小占空比
#define  POWER_ON_PWM   150     //开机占空比===
#define  MOTOR_OFF      4
#define  MOTOR_ON       6
#define  RUNUP_TIME     200      //加速时间可变
#define  MAXRPM       20000      //最大运行转速
#define  MINRPM       1800       //最小运行转速

//MIN_POLE_TIME  20000/60=333r/s**250us/p
//MAX_POLE_TIME  1800/60******** 2000us/p
#define  SDSWITCH_MIN_OFF  150     //关闭开关值
#define  SDSWITCH_MIN_ON   330//410     //启动开关值
// 转动方向
#define  CW  1
#define  CCW 0
//开关方向
#define  SW_POS	        CW
#define  SW_REVS        CCW
//正反转方向
#define  DIR_POS	CW
#define  DIR_REVS	CCW

#define  FR   CW
//============================================
#define  PSN1      1
#define  PSN2      2
#define  PSN3      3
#define  PSN4      4
#define  PSN5      5
#define  PSN6      6

#define  PSNLV     50
// 定位
#define  INJAB    0x42
#define  INJBA    0x42
//--------------------
#define  INJAC    0x42
#define  INJCA    0x42
//--------------------
#define  INJBC    0x42
#define  INJCB    0x42
//--------------------
#define  INJTIM   0x80
// 充电自检
#define  CHANGE_T  0x88

// 自检参数
#define  MCHECK_A   0x01
#define  MCHECK_V   0x01
#define  MCHECK_PH  0x01
//
#define  MCHECK_A  0x01
#define  MCHECK_A  0x01
// 
#define  MCHECK_A  0x01
#define  MCHECK_A  0x01

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
extern uint8_t Pcount;
extern uint8_t const poztable[];
extern uint8_t const phztable[];

/*  functions ----------------------------------------------------------------*/
extern  void mrun(void);
void  Motor_Run(void);
void  Motor_Init(void);
void TS_ch_ph(u8 ky);
void TSR_ch_ph(u8 ky);
void TS_lpv(void);
//void  MC_Switch_Check(void);
//==================================
void     MCTask_CheckMe(void);
void       MCTask_Ready(void);
void       MCTask_Start(void);
void       MCTask_StRun(void);
void      MCTask_NorRun1(void);
void        MCTask_Stop(void);
//==================================
//脉动相关函数声明------------------
void           check_ph(void);
void        Iject_Check(void);
void	           dlay (u16 d);
void         INject_prc(void);
void      InJect_ST_Prc(void);
//void       STrun_init(void);
//==========inj=====================


//INJECT  --------------------------
//==================================


#endif




