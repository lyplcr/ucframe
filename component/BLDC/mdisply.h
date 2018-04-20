//#include "public.h"



#define  LED1   PB7_OUT
#define  LED2   PB6_OUT
#define  LED3   PF4_OUT
#define  LED4   PE5_OUT
#define  SW1    PB4_OUT
#define  SW2    PB5_OUT


extern  const  uint8_t  showsp[];

void  DIS_mode_scan_status(void);
void  eeprom_openlock(void);
void  eeprom_w_char(void);
void  Disp_error_on(void);
void  Disp_error_of(void);
void  POWER_dis_prc(void);
void  FScan_disply(void);
void  FScan_fof(void);
void  FScan_fon(void);
void  FScan_led4(void);
void  FScan_sw1(void);
void  FScan_sw2(void);
