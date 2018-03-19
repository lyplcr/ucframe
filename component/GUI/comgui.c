/* Copyright (c) 2017 pace 王元
 * 
 * fingerprint identification
 */

/* Includes ------------------------------------------------------------------*/
#include "comgui.h"
#include "flash.h"

/* Exported define -----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Flash_Menu(void)
{
  uint8_t key;
  
  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n=                    (C) COPYRIGHT 2017 PACE                         =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=       chipsailing fingerprint  Application  (Version 1.0.0)        =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=                    By PACE Application Team                        =");
  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n\r\n");

  while (1)
  {
//    Serial_PutString("\r\n\r\n");
//    Serial_PutString("\r\n=================== Main Menu ============================");
//    Serial_PutString("\r\n  读设备ID     --------------------------- 1");
//    Serial_PutString("\r\n  读FLASH ID   --------------------------- 2");
//    Serial_PutString("\r\n  read         --------------------------- 3");
//    Serial_PutString("\r\n  write        --------------------------- 4");
//    Serial_PutString("\r\n  erase        --------------------------- 5");
//    Serial_PutString("\r\n  返回主菜单   --------------------------- 0");
//    Serial_PutString("\r\n==========================================================\r\n\n");

    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
	
    /* Receive key */
    HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);

    switch (key)
    {
    case '1' :
      spiflash.ReadDeviceID();
      HAL_UART_Transmit(&UartHandle, spiflash.reg, 4, 10);
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    case '2' :
      spiflash.ReadJedecID();
      HAL_UART_Transmit(&UartHandle, spiflash.reg, 4, 10);
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    case '3' :
      memset(spiflash.fifo, 0, 100);
      spiflash.Read(0, spiflash.fifo, 100);
      HAL_UART_Transmit(&UartHandle, spiflash.fifo, 100, 10);
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    case '4' :
    {
      uint8_t test[100];
      for (uint8_t i=0;i<100;i++)
      {
        test[i]=i;
      }
      spiflash.Write(0, test, 100);
      break;
    }
    case '5' :
    {
      uint8_t test[100];
      for (uint8_t i=0;i<100;i++)
      {
        test[i]=i*2;
      }
      spiflash.Write(0, test, 100);
      break;
    }
    default:
      Serial_PutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
      break;
    }
  }
}


