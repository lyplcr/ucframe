/**********************************************************
*name   : flash.c
*detail : flash相关，看能否用注册模式
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "flash.h"

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
//__IO status_t TransferStatus1 = FAILED;
spiflash_t spiflash;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RWFlash(cmdparam_t *cmdparam)
{
  
}

void ReadJedecID(void)
{
  uint8_t cmd[4] = {FM_CMD_JEDECID, 0, 0, 0};
  memset(spiflash.reg, 0, 4);
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  HAL_SPI_Receive(&hfmspi, spiflash.reg, 3, 10);
  FM_CS_HIGH();
}

void ReadDeviceID(void)
{
  uint8_t cmd[4] = {FM_CMD_DEVICEID, 0, 0, 0};
  memset(spiflash.reg, 0, 4);
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 4, 10);
  HAL_SPI_Receive(&hfmspi, spiflash.reg, 2, 10);
  FM_CS_HIGH();
}

void PowerDown(void)   
{
  uint8_t cmd[4] = {FM_CMD_POWERDOWN, 0, 0, 0};
  
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  FM_CS_HIGH();
}

void Release(void)   
{
  uint8_t cmd[4] = {FM_CDM_RELEASE, 0, 0, 0};
  
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  FM_CS_HIGH();
}

void WriteEnable(void)
{
  uint8_t cmd[4] = {FM_CMD_WREN, 0, 0, 0};
  
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  FM_CS_HIGH();
}

void WaitForWriteEnd(void)
{
  uint8_t cmd[4] = {FM_CMD_RDSR, 0, 0, 0};
  uint8_t status = 0;

  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  cmd[0] = FM_DUMMY;
  do
  {
    HAL_SPI_TransmitReceive(&hfmspi, cmd, &status, 1, 10);	 
  } while ((status & FM_FLAG_WIP) == SET);
  FM_CS_HIGH();
}

void SectorErase(uint32_t sectoraddr)
{
  uint8_t cmd[4] = {FM_CMD_SECTORERASE, sectoraddr>>16, sectoraddr>>8, sectoraddr};
  
  WriteEnable();
  WaitForWriteEnd();
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 4, 10);
  FM_CS_HIGH();
  WaitForWriteEnd();
}

void ChipErase(void)
{
  uint8_t cmd[4] = {FM_CMD_CHIPERASE, 0, 0, 0};
  
  WriteEnable();
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 1, 10);
  FM_CS_HIGH();
  WaitForWriteEnd();
}

int8_t FMWrite(uint32_t addr, uint8_t *pbuffer, uint16_t size)
{
  uint8_t cmd[4] = {FM_CMD_PAGEPROGRAM, addr>>16, addr>>8, addr};
  
//  if (addr%FM_SECTORSIZE == 0)
//  {
//    SectorErase(addr);
//  }
  WriteEnable();
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 4, 10);
  HAL_SPI_Transmit(&hfmspi, pbuffer, FM_PAGESIZE, 10);
  FM_CS_HIGH();
  cmd[1] = (addr+FM_PAGESIZE)>>16;
  cmd[2] = (addr+FM_PAGESIZE)>>8;
  cmd[3] = (addr+FM_PAGESIZE)>>0;
  WaitForWriteEnd();
  
  WriteEnable();
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 4, 10);
  HAL_SPI_Transmit(&hfmspi, pbuffer+FM_PAGESIZE, FM_PAGESIZE, 10);
  FM_CS_HIGH();
  WaitForWriteEnd();
  
  return 0;
}

int8_t FMRead(uint32_t addr, uint8_t *pbuffer, uint16_t size)
{
  uint8_t cmd[4] = {FM_CMD_READ, addr>>16, addr>>8, addr};
  
  FM_CS_LOW();
  HAL_SPI_Transmit(&hfmspi, cmd, 4, 10);
  HAL_SPI_Receive(&hfmspi, pbuffer, size, 10);
  FM_CS_HIGH();
  
  return 0;
}

int8_t BufferWrite(uint32_t addr, uint8_t* pbuffer, uint16_t size)
{
  uint8_t numofpage, numofsingle, count;

  count = FM_PAGESIZE - (addr % FM_PAGESIZE);
  numofpage =  size / FM_PAGESIZE;
  numofsingle = size % FM_PAGESIZE;

  if ((addr % FM_PAGESIZE) == 0) /* 若地址与 FM_PAGESIZE 对齐  */
  {
    if (numofpage == 0) /* size < FM_PAGESIZE */
    {
//      if (addr%FM_SECTORSIZE == 0)
//      {
//        SectorErase(addr);
//      }
      FMWrite(addr, pbuffer, size);
    }
    else /* size > FM_PAGESIZE */
    {
      while (numofpage--)
      {
        FMWrite(addr, pbuffer, FM_PAGESIZE);
        addr +=  FM_PAGESIZE;
        pbuffer += FM_PAGESIZE;
      }
      FMWrite(addr, pbuffer, numofsingle);
    }
  }
  else /* 若地址与 FM_PAGESIZE 不对齐 */
  {
    if (numofpage == 0) /* size < FM_PAGESIZE */
    {
      if (numofsingle > count) /* (size + addr) > FM_PAGESIZE */
      {
        FMWrite(addr, pbuffer, count);
        FMWrite(addr+count, pbuffer+count, numofsingle-count);
      }
      else
      {
        FMWrite(addr, pbuffer, size);
      }
    }
    else /* size > FM_PAGESIZE */
    {
      size -= count;
      numofpage =  size / FM_PAGESIZE;
      numofsingle = size % FM_PAGESIZE;

      FMWrite(addr, pbuffer, count);
      addr +=  count;
      pbuffer += count;

      while (numofpage--)
      {
        FMWrite(addr, pbuffer, FM_PAGESIZE);
        addr +=  FM_PAGESIZE;
        pbuffer += FM_PAGESIZE;
      }
      
      if (numofsingle != 0)
      {
        FMWrite(addr, pbuffer, numofsingle);
      }
    }
  }
  
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
int8_t FLASHRead(uint32_t addr, uint8_t *data, uint16_t length)
{
  
  return 0;
}

int8_t FLASHWrite(uint32_t addr, uint8_t *data, uint16_t length)
{
  
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
void SPIFlashInit(void)
{
  spiflash.ReadJedecID = ReadJedecID;
  spiflash.ReadDeviceID = ReadDeviceID;
  spiflash.PowerDown = PowerDown;
  spiflash.Release = Release;
  spiflash.SectorErase = SectorErase;
  spiflash.ChipErase = ChipErase;
  spiflash.Write = FMWrite;
  spiflash.Read = FMRead;
  
  FM_WP_HIGH();
  FM_HD_HIGH();
  WriteEnable();
}