#include "ringbuff.h"

/*
* 创建一个ringbuff 用户定义字节大小
*/
RingBuff_handle createRingBuff(int totalsize)
{
	RingBuff_handle ringbuff;
	ringbuff = malloc(sizeof(struct RingBuff));
	ringbuff->source = malloc(totalsize);
	if(ringbuff->source !=NULL)
	{
		LOGI("create ringbuff success!");
	}
	
	ringbuff->write = ringbuff->source;
	ringbuff->read = ringbuff->source;
	ringbuff->writed_size = 0;
	ringbuff->tail = ringbuff->source + totalsize;
	ringbuff->size = totalsize;
	ringbuff->remain_size = totalsize;
	return ringbuff;
	
}

/*
* 写入ringbuff handle 数据 数据字节长度
*/
int writeRingBuff(RingBuff_handle handle,unsigned char *data,int size)
{
	//检查剩余内存是否足够
	if(handle->remain_size > size)
	{
		//写指针在读指针前
		if(handle->write - handle->read >0)
		{
			int writebytes = handle->tail - handle->write - size;
			//写入的数据小于写指针到内存尾部
			if(writebytes >= 0)
			{
				memcpy(handle->write,data,size);
				handle->write += size;
		
			}
			else //写入的数据大于写指针到内存尾部，需要从头部继续写入
			{
				//写入数据到尾部
				memcpy(handle->write,data,handle->tail - handle->write);
				data += handle->tail - handle->write;
				writebytes = abs(writebytes);
				//从头部继续写入剩余数据
				memcpy(handle->source,data,writebytes);
				handle->write = handle->source +  writebytes;
			
			}
		}
		else	//读指针在写指针前
		{
			memcpy(handle->write,data,size);
			handle->write += size;
			
		}
		LOGI("write success");
		//更新参数
		getRingBuffRemainSize(handle);
		return 1;	
	}
	else
	{
		LOGE("write fail");
		return 0;
	}
	
}

/*
* 读取ringbuff数据 
*/
int readRingBuff(RingBuff_handle handle,unsigned char *data,int size)
{
	if(data == NULL)
	{
		malloc(sizeof(unsigned char));
	}
	//要读取的数据少于已经写入的数据
	if(handle->writed_size >= size)
	{
		//写指针在读指针前
		if(handle->write - handle->read >0)
		{
			memcpy(data,handle->read,size);
			handle->read += size;
		}
		else	//读指针在写指针前
		{
			int readbytes = handle->tail - handle->read - size;
			
			//读取，不用从头读
			if(readbytes > 0)
			{
				memcpy(data,handle->read,size);
				handle->read += size;
			}
			else 	//需要从头读
			{
				memcpy(data,handle->read,handle->tail - handle->read);
				readbytes = abs(readbytes);
				data += handle->tail - handle->read;
				memcpy(data,handle->source,readbytes);
				handle->read = handle->source + readbytes;
			}
		}
		
		LOGI("read success");
		//更新参数
		getRingBuffRemainSize(handle);
		return 1;
	}
	else
	{
		LOGE("read fail");
		return 0;
	}
	
}

/*
* 获得已写入数据的字节
*/
int getRingBuffWritedSize(RingBuff_handle handle)
{
	handle->writed_size = (handle->size + (handle->write - handle->read)) % handle->size;
	LOGI("writed_size = %d",handle->writed_size);
	return handle->writed_size;
}

/*
* 获得ringbuff长度
*/
int getRingBuffTotalSize(RingBuff_handle handle)
{
	LOGI("total_size = %d",handle->size);
	return handle->size;
}

/*
* 获得ringbuff剩余长度
*/
int getRingBuffRemainSize(RingBuff_handle handle)
{
	int writed,total;
	total = getRingBuffTotalSize(handle);
	writed = getRingBuffWritedSize(handle);
	LOGI("RemainSize = %d",(total - writed));
	handle->remain_size = total - writed;
	return handle->remain_size;
}

/*
* 删除ringbuff
*/
int deleteRingBuff(RingBuff_handle handle)
{
	if(handle == NULL ||handle->source == NULL)
	{
		LOGE("free fail");
		return 0;
	}
	free(handle->source);
	free(handle);
	LOGI("free ringbuff success");
	return 1;
}

