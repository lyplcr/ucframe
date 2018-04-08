/* Copyright (c) 2017 pace 王元
 * 
 * fingerprint identification
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_H
#define __FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* 类型定义 ------------------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;
#define hfmspi hspi1


/* 宏定义 --------------------------------------------------------------------*/
#define WINBORD
//#define BOYA
#define FLASHFIFOSIZE 1024

/* 私有宏定义 ----------------------------------------------------------------*/
#define FM_PAGESIZE             256
#define FM_SECTORSIZE           4*1024
#define FM_BLOCKSIZE            64*1024  
#define FM_CHIPSIZE             16*1024*1024

#define FM_FLAG_WIP             0x01
#define FM_DUMMY                0xFF
//ID and Security Instructions
#define FM_CMD_JEDECID          0x9F
#define FM_CMD_DEVICEID         0x90    // 0xAB
#define FM_CMD_POWERDOWN 	0xB9
#define FM_CDM_RELEASE	        0xAB
//Configuration and Status Instructions
#define FM_CMD_WREN             0x06
#define FM_CMD_WRDIS            0x04
#define FM_CMD_RDSR		0x05    // 0X35
#define FM_CMD_WRSR		0x01
//Read Instructions
#define FM_CMD_WRITE            0x02
#define FM_CMD_READ             0x03
#define FM_CMD_FASERD		0x0B 
//Program and Erase Instructions
#define FM_CMD_PAGEPROGRAM	0x02
#define FM_CMD_SECTORERASE	0x20
#define FM_CMD_BLOCKERASE	0xD8 
#define FM_CMD_CHIPERASE	0xC7//0x60

#define FM_CMD_DUMMY            0xA5



/* 扩展变量 ------------------------------------------------------------------*/

extern void SPIFlashInit(void);

typedef struct
{
  cmdparam_t cmdparam;
  uint8_t cmd[4];
  uint8_t reg[4];
  uint8_t fifo[FLASHFIFOSIZE];
  
//  void (*Init)(void);
  void (*ReadJedecID)(void);
  void (*ReadDeviceID)(void);
  void (*PowerDown)(void);
  void (*Release)(void);
  void (*ChipErase)(void);
  void (*SectorErase)(uint32_t SectorAddr);
  void (*StartReadSequence)(uint32_t addr);
  int8_t (*Write)(uint32_t addr, uint8_t *pbuffer, uint16_t size);
  int8_t (*Read)(uint32_t addr, uint8_t *pbuffer, uint16_t size);
} spiflash_t;
extern spiflash_t spiflash;

typedef struct
{
  uint32_t control;
  uint32_t state;
  uint8_t *data;
  int8_t (*Read)(uint32_t addr, uint8_t *data, uint16_t length);
  int8_t (*Write)(uint32_t addr, uint8_t *data, uint16_t length);
  int8_t (*RWreg)(uint8_t *wrdata, uint8_t wrsize, uint8_t *rddata, uint8_t rdsize);
} flash_t;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

#endif