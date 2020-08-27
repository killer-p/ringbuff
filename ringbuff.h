#ifndef _RINGBUFF_H
#define _RINGBUFF_H

#include "stdlib.h"
#include "log.h"
#include "string.h"
typedef struct RingBuff *RingBuff_handle;

struct RingBuff
{
	unsigned char *source;
	unsigned char *tail;
	unsigned char *write;
	unsigned char *read;
	int size;
	int writed_size;
	int remain_size;
	
};


RingBuff_handle createRingBuff(int size);
int writeRingBuff(RingBuff_handle handle,unsigned char *data,int size);
int readRingBuff(RingBuff_handle handle,unsigned char *data,int size);
int getRingBuffWritedSize(RingBuff_handle handle);
int getRingBuffTotalSize(RingBuff_handle handle);
int getRingBuffRemainSize(RingBuff_handle handle);
int deleteRingBuff(RingBuff_handle handle);

#endif
