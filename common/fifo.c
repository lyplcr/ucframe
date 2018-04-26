


#include "CirQueue.h"


CirQueue stQueue;


/*	$Function		:  Init_Queue		
==  ===============================================================
==	Description		:	
==	Argument		:	*Q
==					:	
== 	Return			:	none
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/
void InitQueue(CirQueue *Q)
{
   u8 i;	
	Q->front = Q->rear = 0;
	Q->count = 0;
	memset(Q->receive,0,QueueSize);
		
}



/*	$Function		:  QueueEmpty		
==  ===============================================================
==	Description		:	
==	Argument		:	*Q
==					:	
== 	Return			:	if count =0 is return 1,if not return 0
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/

u16 QueueEmpty(CirQueue *Q)
{
	return Q->count == 0;           
}



/*	$Function		:  QueueFull		
==  ===============================================================
==	Description		:	
==	Argument		:	*Q
==					:	
== 	Return			:	if count = Queuesize is return 1,if not return 0
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/

u16 QueueFull(CirQueue *Q)
{
	return Q->count == QueueSize;  
}




/*	$Function		:  QueuePushIn		
==  ===============================================================
==	Description		:	
==	Argument		:	*Q,x
==					:	
== 	Return			:	if queue is full return 0 ,if not return 1
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/

u8 EnQueue(CirQueue *Q,u8 x)   
{
	if(QueueFull(Q))
	{
		return 0;
	}
	Q->count++;
	Q->receive[Q->rear] = x;              		
	Q->rear = (Q->rear+1)%QueueSize;
	return 1;
}



/*	$Function		:  QueuePushIn		
==  ===============================================================
==	Description		:	
==	Argument		:	*Q ,*dat
==					:	
== 	Return			:	if queue is empty return 0 ,if not return 1
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/
u8 DeQueue(CirQueue *Q, u8 *dat)
{
	if(QueueEmpty(Q))
	{
		return 0;
	}
	*dat = Q->receive[Q->front];
	Q->front = (Q->front +1)%QueueSize;
	Q->count--;
	return 1;
}



/*	$Function		:  QueuePushIn		
==  ===============================================================
==	Description		:	
==	Argument		:	*rxdata,length
==					:	
== 	Return			:	none
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/
u8 QueuePushIn(u8 *rxdata,u8 length)
{
	u8 i;
	if(QueueFull(&stQueue))
	{
		return 0;
	}
	
	for(i=0;i<length;i++)
	{
		EnQueue(&stQueue,*rxdata++);
	}
	return 1;
}




/*	$Function		:  QueuePopOut		
==  ===============================================================
==	Description		:	
==	Argument		:	*buf,length
==					:	
== 	Return			:	none
==	Modification	:	2014-03-05        xu_chenhua		Create
==  ===============================================================
*/
u8 QueuePopOut(u8 *buf, u16 length)
{
	u8 i;
	if(QueueEmpty(&stQueue))
	{
		return 0;
	}
	for(i=0;i<length;i++)
	{
		DeQueue(&stQueue, &buf[i]);
	}
	return 1;
}


