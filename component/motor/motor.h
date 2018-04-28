/**********************************************************
*name   : motor.h
*detail : motorÄ£¿éÈë¿Ú
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_H
#define __MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "param.h"

/*  defines&macro ------------------------------------------------------------*/
#define BLDC

/*  typedef ------------------------------------------------------------------*/
typedef struct
{
  int (*MotorRest)(void);
  
} motor_t;

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/
void MotorInit(void);

#endif

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/