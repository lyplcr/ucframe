
#ifndef _MSWITCH_H_
#define _MSWITCH_H_
#endif







extern uint8_t adc_sflg;
extern uint16_t sw_count;

void MC_Swbut_Check(void);
extern void Get_adc_vl(void);
void Get_sw_fr(void);
void Get_adc_sw(void);

void Check_switch_onff(void);
void check_erorr(void);
extern  void read_eeprom_vla(void);
extern void   Motor_ip(void);
extern void   Motor_Limit_Curr(void);


