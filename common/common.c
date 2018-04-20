/**********************************************************
*name   : mian.c
*detail : include public head file
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* define -----------------------------------------------------------*/
/* types ------------------------------------------------------------*/
/* constants --------------------------------------------------------*/
/* macro ------------------------------------------------------------*/
/* vriable ----------------------------------------------------------*/
uint8_t txbuffer[BUFFERSIZE];
uint8_t rxbuffer[BUFFERSIZE];
uint8_t begainposition;
uint8_t endposition;

/*  functions ----------------------------------------------------------------*/
/**
  * @brief  Print a string on the HyperTerminal
  * @param  p_string: The string to be printed
  * @retval None
  */
void Serial_PutString(uint8_t *p_string)
{
//  uint16_t length = 0;
//
//  while (p_string[length] != '\0')
//  {
//    length++;
//  }
//  HAL_UART_Transmit(&UartHandle, p_string, length, length+10);
}

/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef HAL_OK if OK
  */
//HAL_StatusTypeDef Serial_PutByte( uint8_t param )
//{
//  if ( UartHandle.gState == HAL_UART_STATE_TIMEOUT )
//  {
//    UartHandle.gState = HAL_UART_STATE_READY;
//  }
//  return HAL_UART_Transmit(&UartHandle, &param, 1, 10);
//}
/* Exported functions ------------------------------------------------------- */
/* COMMON FUNCTIONS */
status_t BufferCompare(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}


/* INTERFACE */
int8_t TXData(uint32_t handle, uint8_t *data, uint16_t length)
{
  return 0;
}

int8_t RXData(uint32_t handle, uint8_t *data, uint16_t length)
{
  return 0;
}






/* COMMON 注册需要用到的模块 */
void CommonInit(void)
{
//  CreatDataTime();
//  CreatKey();
}

