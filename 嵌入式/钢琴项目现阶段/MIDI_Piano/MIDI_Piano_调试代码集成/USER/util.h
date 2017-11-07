/*
**************************
file info:
	author:fang.junpeng
	start time:2016-04-07
	email:tfzsll@126.com
	standard Message define for ISDebug & Cooperation
***************************
*/

#include "stm32f10x.h"
#include "Msgconfiguration.h"
#ifndef UTIL_H
#define UTIL_H

//direct copy the byte without any check of array overflow
void byteCopy(DebugMsg_t * Dst,u8* Src,s16 Length);

//get length of a string
u16 stringLength(u8* str);

//set the memory all to be byteValue you choose
void memorySet(u8* mem,u8 byteValue,s16 length);

#endif
