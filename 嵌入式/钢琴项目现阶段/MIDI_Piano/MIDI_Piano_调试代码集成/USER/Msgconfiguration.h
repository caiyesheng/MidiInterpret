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
	u8 msgHead;//Э��ͷ
	struct{
		u8 DControl;//������,�������޸�������������޸�ռ�ձȻ���Ƶ��
		//u8 DArg:4;//�������޸�������������޸�ռ�ձȻ���Ƶ��
		u8 Rhythm;//������
	}debugInfo;
	u8 dataLength;//�����ֶγ���
	u8 data[4];//�����ֶ�����
}DebugMsg_t;

#endif
