/**********************************************************
*name:      gpio.h
*version:   v1.0
*mcu:       903k3
*sdk:       stvd
*detail:    gpio 
*author:    hongwei luo
*date:      2016-4-6
***********************************************************/
#ifndef _ADC_H_
#define _ADC_H_
#endif

#define	BEMFA_ADC_CH		4
#define	BEMFB_ADC_CH		5
#define	BEMFC_ADC_CH		6

#define	CURR_ADC_CH		2


#define	CURR_CHANEL	2
#define	BEMFA_CHANEL	4
#define	BEMFB_CHANEL	5
#define	BEMFC_CHANEL	6

void Adc_Scan_timetrig_init(void);
void Adc_Scan_pwmtrig_init(void);
extern void Set_adc_chan(unsigned char channel);
extern u16 adc_temp [4];
extern u8 adc_times;
void   Adc_Start(void);
void   adc_init(void);
void   adcc(void);
extern void  Adc_SetUp_ch(unsigned char ch);
void   Adc_SetUp_Init(void);
void  Adc_SetUp_ch1(void);
void  Adc_SetUp_ch2(void);
void  Adc_SetUp_ch3(void);
void  Getval_prc_updata(void);