/* Copyright (c) 王元
 * 20180101
 * 通用类
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <stdarg.h>
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
//#include "key.h"
//#include "comgui.h"
//#include "menugui.h"
//#include "bufferlist.h"
//#include "flash.h"
//#include "datamanager.h"

/* Private define -----------------------------------------------------------*/
#define BUFFERSIZE      64
extern uint8_t txbuffer[BUFFERSIZE];
extern uint8_t rxbuffer[BUFFERSIZE];
extern uint8_t begainposition;
extern uint8_t endposition;     // 这两个变量针对串口中断接收

/* Exported define -----------------------------------------------------------*/
#ifndef NULL
  #define NULL ((void *)0)
#endif

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

typedef enum {FAILED = 0, PASSED = !FAILED} status_t;



/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* IC proc */
typedef struct
{
  uint8_t cmd[2];
  uint8_t cmdsize;
  uint8_t addrsize; 
  uint8_t addr[4];
  uint8_t reg[4];
  uint16_t readsize;
  uint16_t writesize;
  uint8_t *data;
  void (*read)(void *pointhandle, ...);
  void (*write)(void *pointhandle, ...);
} cmdparam_t;   // 看能不能做成通用标准芯片读写结构

/* POINT */
#define SMOOTHDEP 6
typedef struct
{
  void (*CreatPoint)(void);
  void (*Calibration)(void);
  void (*Smooth)(int32_t data);
} point_t;

/* BITMAP */
typedef struct
{
  uint16_t bftype;      // 0x424d
  uint32_t bfsize;      // 
  uint32_t bfreserved;  // 0
  uint32_t bfoffbits;   // 0x00000436
} bitmapfileheader_t;
typedef struct
{
  uint32_t biSize;              //指定此结构体的长度，为40  
  uint32_t biWidth;             //位图宽 //160
  uint32_t biHeight;            //位图高 //160
  uint16_t biPlanes;            //平面数，为1                   
  uint16_t biBitCount;          //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32  //8
  uint32_t biCompression;       //压缩方式，可以是0，1，2，其中0表示不压缩 
  uint32_t biSizeImage;         //实际位图数据占用的字节数,像素为4的倍数 //160*160
  uint32_t biXPelsPerMeter;     //X方向分辨率 
  uint32_t biYPelsPerMeter;     //Y方向分辨率  
  uint32_t biClrUsed;           //使用的颜色数，如果为0，则表示默认值(2^颜色位数) 
  uint32_t biClrImportant;      //重要颜色数，如果为0，则表示所有颜色都是重要的 
} bitmapinfoheader_t;
typedef struct 
{
  uint8_t rgbBlue;              //该颜色的蓝色分量 
  uint8_t rgbGreen;             //该颜色的绿色分量 
  uint8_t rgbRed;               //该颜色的红色分量 
  uint8_t rgbReserved;          //保留值 
} rgbquad_t;            // 位图不是8的倍数时，数据填充     

typedef struct
{
  bitmapfileheader_t bitmapfileheader;
  bitmapinfoheader_t bitmapinfoheader;
//  palette_t palette;
  uint8_t *imagedata;
} bitmap_t;

/* ENCRYPT */
typedef struct
{
  void (*CreatEncrypt)(void);
} encrypt_t;

/* interface */
typedef struct
{
  uint8_t sfd;          // 帧开始符 #define 固定 0xA5
  uint8_t devid;        // 一般就一个只用0x01、0x00主机、0xff广播地址
  uint16_t length;      // 要不要拆分一个flag在前面？重发次数，
  uint8_t cmd;          // 指令
  uint8_t cmdplusl;     // 扩展指令
  uint8_t cmdplush;     // 扩展指令
  uint8_t checkcode;    // 用什么校验码好点
  uint8_t *pdata;       //
//  uint16_t eop;         // 0x0d 0x0a（即回车换行
} cmdpackets_t;         //comprotocol_t; datacom


/* COMMON */
typedef struct
{
  uint8_t indata[64];
  uint8_t outdata[64];
  uint8_t *pbuf;
//  void (*CommonInit)(void);
//  void (*CommonDeInit)(void);
  void (*printf)(void);
  void (*TxData)(int8_t *pdata, uint16_t size);
  void (*RxData)(int8_t *pdata, uint16_t size);
} common_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
#define MV2ADC(__X__)           ( (__X__*4095) / 3300 )
#define ADC2MV(__X__)           ( (__X__*3300) / 4095 )
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#define ABS(A,B) ((A) <= (B) ? (B-A) : (A-B))
#define PORTPIN(PORT, PIN, MODE)  	{ PORT, GPIO_PIN_ ## PIN, MODE }

// 得到指定地址上的数据
#define  MEM_B( x )  ( *( (byte *) (x) ) ) 
#define  MEM_W( x )  ( *( (word *) (x) ) )  

// 得到结构体类型中成员的偏移量 struct type field offset
#define STFO(type, field) ((int) &((type *) 0)-> field)
// 结构体中的字节数
#define FSIZ(type, field) sizeof( ((type *) 0)->field ) 

// 获取缓冲区的长度
#define countof(array)      (sizeof(array) / sizeof(*(array)))

//将一个字母转换为大写
#define UPCASE( c ) ( ((c) >= ’a' && (c) <= ’z') ? ((c) - 0×20) : (c) )

#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))
/* Exported functions ------------------------------------------------------- */
/*
 * Macros to concatenate 2 - 4 tokens together to form a single token.
 * Multiple levels of nesting are required to convince the preprocessor to
 * expand currently-defined tokens before concatenation.
 *
 * For example, if you have
 *     #define FOO 1
 *     #define BAR1 42
 * Then
 *     #define BAZ CONCAT2(BAR, FOO)
 * Will evaluate to BAR1, which then evaluates to 42.
 */
#define CONCAT_STAGE_1(w, x, y, z) w ## x ## y ## z
#define CONCAT2(w, x) CONCAT_STAGE_1(w, x, , )
#define CONCAT3(w, x, y) CONCAT_STAGE_1(w, x, y, )
#define CONCAT4(w, x, y, z) CONCAT_STAGE_1(w, x, y, z)

/*
 * Macros to turn the argument into a string constant.
 *
 * Compared to directly using the preprocessor # operator, this 2-stage macro
 * is safe with regards to using nested macros and defined arguments.
 */
#define STRINGIFY0(name)  #name
#define STRINGIFY(name)  STRINGIFY0(name)

/* Macros to access registers */
#define REG32_ADDR(addr) ((volatile uint32_t *)(addr))
#define REG16_ADDR(addr) ((volatile uint16_t *)(addr))
#define REG8_ADDR(addr)  ((volatile uint8_t  *)(addr))

#define REG32(addr) (*REG32_ADDR(addr))
#define REG16(addr) (*REG16_ADDR(addr))
#define REG8(addr)  (*REG8_ADDR(addr))

/* Exported functions ------------------------------------------------------- */

extern void CommonInit(void);
extern void Serial_PutString(uint8_t *p_string);
//extern HAL_StatusTypeDef Serial_PutByte( uint8_t param );
extern uint32_t Str2Int(uint8_t *p_inputstr, uint32_t *p_intnum);



#endif  /* __COMMON_H */
