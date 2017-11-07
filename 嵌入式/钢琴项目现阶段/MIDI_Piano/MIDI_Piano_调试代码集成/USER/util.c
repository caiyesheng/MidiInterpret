/**************************************
 * 文件名  ：util.c
 * 描述    ：数据处理
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/	
#include "util.h"
void byteCopy(DebugMsg_t * Dst,u8* Src,s16 Length){
	//if(0 == Dst || 0 == Src)//check pointer
	//	return;
	int i;
	Dst->msgHead = Src[0];
	//printf("  \r\n0x%x  ",Dst->msgHead);
	Dst->debugInfo.DControl = Src[1];
	//printf("  \r\n0x%x  ",Dst->debugInfo.DControl);
	Dst->debugInfo.Rhythm = Src[2];
	//printf("  \r\n0x%x  ",Dst->debugInfo.Rhythm);
	Dst->dataLength = Src[3];
	//printf("  \r\n0x%x  ",Dst->dataLength);
	for(i=0; i<Dst->dataLength ;i++)
	{
		Dst->data[i] = Src[4+i];
	}
	//for(i=0; i<Dst->dataLength ;i++)
	//printf("  \r\n0x%x  ",Dst->data[i]);
}

u16 stringLength(u8* str){
	u16 length=0;
	if(0 != str){//check str pointer
		while(0 != *str++)
			length++;
	}
	return length;
}

void memorySet(u8* mem,u8 byteValue,s16 length){
	if(0 == mem)
		return;
	while(length>0){
		mem[--length]=byteValue;
	}
}

