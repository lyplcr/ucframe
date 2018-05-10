/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"
#include "motor.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief TRAP Interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Top Level Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TLI_IRQHandler, 0)

{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Clock Controller Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTA Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  GPIOA->CR2=0x00;
  GPIOA->CR2=0x0e; 
}

/**
  * @brief External Interrupt PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  GPIOB->CR2=0x00; 
  GPIOB->CR2=0xe0;			
}

/**
  * @brief External Interrupt PORTC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  
}

/**
  * @brief External Interrupt PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  GPIOD->CR2=0x00;
  GPIOD->CR2=0x04;
}

/**
  * @brief External Interrupt PORTE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined (STM8S903) || defined (STM8AF622x) 
/**
  * @brief External Interrupt PORTF Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x) */

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
  TIM1->SR1 = 0x00;
  TIM1->EGR |= 0x01;
  DisAllPwmOut();
  Motordata.fault = elvp;
  Motordata.station = Stop;
  Motordata.UI.blink = 9;
}

/**
  * @brief Timer1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer5 Update/Overflow/Break/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
{
  TIM5->IER =0x00;
  TIM5->SR1 = 0x00;
  
  Motordata.TRcount++;
  if(Motordata.TQcount > 0)
  {
    Motordata.TQcount -= 1;
  }
  Motordata.UI.ledcount++;
  if(Motordata.UI.ledcount > 30)
  {
    Motordata.UI.ledcount = 0;
    Motordata.Disstatus++;
    if(Motordata.Disstatus == 7)
    {
      Motordata.Disstatus = 1;
    }
  }
  if(Motordata.UI.blink == 0)
  {
  // DIS_mode_scan_status();
    FScan_disply();
  }
  switch(Motordata.station)
  {
  case Ready :
    if (ADC1->CSR & ADC1_CSR_EOC == 0)  // if(ADC_CSR_EOC==0)
    {
      Adc_Start();
    }
    if( Motordata.Dswitch==MOTOR_ON)
    {
    }
    if( Motordata.Dswitch==MOTOR_OFF)
    {
      if(Motordata.SWhkey.TRdelay > 0)
      {
        if(Motordata.SWhkey.TRdelay1 > 0)
        {
          Motordata.SWhkey.TRdelay1--;	
        }
        else
        {
          Motordata.SWhkey.TRdelay1 = 2000;	//2500
          Motordata.SWhkey.TRdelay--;
        }
      }
      else
      { 
        if(Motordata.SWhkey.TRdelay1 > 0)
        {
          Motordata.SWhkey.TRdelay1--;	
        }
        else
        {
          GPIOD->ODR &= 0xfb;        // DEALY
        }
      }
    }
    break;
  case NorRun :    
    if(Motordata.TQcount==0)
    {     
      MCTask_NorRun1();	
    }
    break;
  case  Stop :  
    if (ADC1->CSR & ADC1_CSR_EOC == 0)  // if(ADC_CSR_EOC==0)
    {
      Adc_Start();
    }
    //if(Motordata.fault==eNO)	
    if(Motordata.UI.showtime>=4000)
    {
      Motordata.UI.showtime=0;
      Motordata.UI.showcount+=1;
      if( Motordata.UI.showcount==14)
      {
        Motordata.UI.showcount = Motordata.UI.blink;
        //	Motordata.UI.Blink
      }	
    }
    Motordata.UI.showtime++;
    break;
  }
  TIM5->CNTRH = 0; 
  TIM5->CNTRL = 0;
  TIM5->IER = 0x01;
 }
 
/**
  * @brief Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }


/**
  * @brief UART1 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART1 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }


/**
  * @brief I2C Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief ADC1 interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
#define	START_SLOW_CNT          1       // 3
#define	ADJUST_ADD_PWM_WIDTH	1
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
  static unsigned char Start_Slow_Cnt = 0;
  ADC1->CSR &= (~ADC1_CSR_EOC);      // ADC_CSR_EOC=0;

  switch(Motordata.station)
  {
  case Ready:
    Getval_prc_updata();
    break;
  case NorRun:
    Getval_prc_updata();
    Motor_Limit_Curr();		
//  if(Motordata.MFR==CW) 
//  {
//    if(Motordata.outduty<Motordata.hopeduty&&Motordata.outduty< Motordata.UI.Gduty)
//    {  
//      Motordata.outduty++;			 
//    }
//  }
//  if(Motordata.MFR==CCW) 
//  {
//    if(Motordata.outduty<Motordata.hopeduty&&Motordata.outduty< Motordata.UI.Gduty)
//    {  
//      Motordata.outduty++;			 
//    }
//  } 			
//pwm adjust
    if( (Motordata.outduty<Motordata.hopeduty) && (Motordata.outduty<Motordata.UI.duty) )
    {
      Start_Slow_Cnt++;
      if(Start_Slow_Cnt >= START_SLOW_CNT)
      {
        //Motordata.outduty++;
        Motordata.outduty += ADJUST_ADD_PWM_WIDTH;
        Start_Slow_Cnt = 0;
      }
    }
    if( (Motordata.outduty>Motordata.hopeduty) || (Motordata.outduty>Motordata.UI.duty) )		//10
    {
      //Motordata.outduty=Motordata.hopeduty;
      Motordata.outduty -= 5;
    }		
    break;
  case Stop :    
    Getval_prc_updata();
    break;
  }
}

/**
  * @brief Timer6 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  TIM6->IER = 0x00;
  TIM6->SR1 = 0x00; 	
  TIM6->IER = 0x01;
}


/**
  * @brief Eeprom EEC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/