#include "ringbuff.h"

void main()
{
	unsigned char *data = "12345";
	unsigned char *rec;
	rec = malloc(sizeof(unsigned char));
	RingBuff_handle rb = createRingBuff(10);

	//写5个
	writeRingBuff(rb,data,(int)strlen(data));
	//读5个
	readRingBuff(rb,rec,5);
	LOGI("%s",rec);
	//写9个
	data = "123456789";
	writeRingBuff(rb,data,(int)strlen(data));
	
	//读八个
	readRingBuff(rb,rec,8);
	LOGI("%s",rec);
	
	deleteRingBuff(rb);
}