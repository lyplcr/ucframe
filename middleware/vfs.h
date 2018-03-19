/* Copyright (c) 2018 ÍõÔª
 * 20180101
 * virtual file system
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VFS_H
#define __VFS_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t fsid;
  char name[8];
  void (*fsinit);
  void (*IOCtrl);
  void (*Creat);
  void (*Open);
  void (*Read);
  void (*Write);
  void (*Delete);
  void (*Close);	
} vfs_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

