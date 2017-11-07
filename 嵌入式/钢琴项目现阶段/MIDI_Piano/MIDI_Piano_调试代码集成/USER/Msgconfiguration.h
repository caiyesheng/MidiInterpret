#include "stm32f10x.h"

#ifndef MSGCONFIG_H
#define MSGCONFIG_H


//which Argument to debug
typedef enum{
	ePWM_Fre=0,ePWM_Duty,eMusc_Beat
}ArgType_e;

//which style to debug
typedef enum{
	eDC_None=0,
	eDC_Modify_Frequency=0x10,//modify the argument
	eDC_Modify_Duty=0x11,
	eDC_Query=0x20,		//query the argument
	//for running control
	eDC_Stop=0x30,
	eDC_Play=0x40,
}DebugControl_e;

//debug message struct
typedef struct{
	u8 msgHead;//协议头
	struct{
		u8 DControl;//控制码,控制在修改音量情况下是修改占空比还是频率
		//u8 DArg:4;//控制在修改音量情况下是修改占空比还是频率
		u8 Rhythm;//音符号
	}debugInfo;
	u8 dataLength;//数据字段长度
	u8 data[4];//数据字段内容
}DebugMsg_t;

#endif
