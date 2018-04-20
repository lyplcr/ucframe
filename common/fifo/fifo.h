
#ifndef __CIRQUEUE_H_
#define __CIRQUEUE_H_

#include  "usr_define.h"
#include <string.h>
#include <stdlib.h>


#define QueueSize  64

typedef struct _TagCirQueue
{
	u16 front;
	u16 rear;
	u16 count;
	u8  receive[QueueSize];
}CirQueue;

extern CirQueue stQueue;

u8 QueuePopOut(u8 * buf,u16 length);
u8 QueuePushIn(u8 * rxdata,u8 length);
void InitQueue(CirQueue * Q);




//extern U8 CanQueuePopOut(U8 * buf,U32 length);
//extern void CanQueuePushIn(U32 ID,U16 *CanData,U8 DataLength);

//extern U8 UartRxdatPopOut(U8 * buf,U32 length);
//extern U8 UartRxdatPushIn(U8 * rxdata,U8 length);

//extern U8 UartRxCandataPushIn(U8 *rxdata,U8 length);
//extern U8 UartRxCandataPopOut(U8 *buf, U32 length);



#endif




