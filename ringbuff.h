#ifndef _RINGBUFF_H
#define _RINGBUFF_H

#include "stdlib.h"
#include "log.h"
#include "string.h"
typedef struct RingBuff *RingBuff_handle;

//ringbuff结构体
struct RingBuff
{
	unsigned char *source;	//ringbuff的头部
	unsigned char *tail;	//尾部
	unsigned char *write;	//写指针
	unsigned char *read;	//读指针
	int size;	//ringbuff总长度
	int writed_size;	//写入数据的长度
	int remain_size;	//剩余空间
	
};


RingBuff_handle createRingBuff(int size);
int writeRingBuff(RingBuff_handle handle,unsigned char *data,int size);
int readRingBuff(RingBuff_handle handle,unsigned char *data,int size);
int getRingBuffWritedSize(RingBuff_handle handle);
int getRingBuffTotalSize(RingBuff_handle handle);
int getRingBuffRemainSize(RingBuff_handle handle);
int deleteRingBuff(RingBuff_handle handle);

#endif
