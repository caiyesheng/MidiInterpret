/**************************************
 * �ļ���  ��ISDebug.c
 * ����    ���������������
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ���
 * ��汾  ��ST3.0.0  

*********************************************************/	
#include "ISDebug.h"
#include "util.h"
#include "can.h"
#include "SysTick.h"
#include "time.h"
extern  DebugMsg_t CurrentDebugMsg ;
extern int Force_Array[85][9],Force_Array_Base[85][9],Force_Array_Duty[85][9],Force_Array_Frequency[85][9];
extern u8 CurrentPianoKey;//��־���ڲ�����������
extern CanTxMsg TxMessage;
// get functions
u8  getDebugControlInfo(DebugMsg_t* dMsg){
	if(!dMsg)
		return 0;
	return dMsg->debugInfo.DControl;
}
u8 getDebugArgInfo(DebugMsg_t* dMsg){
	if(!dMsg)
		return 0;
	return dMsg->debugInfo.DControl;
}
 
u8* getDebugData(DebugMsg_t* dMsg){
	if(!dMsg)
		return 0;
	return dMsg->data;
}

u8 getDebugRhythmInfo(DebugMsg_t* dMsg){
	if(!dMsg)
		return 0;
  return 	dMsg->debugInfo.Rhythm;
}
int getCurrentFrequency(u8 CurrentPianoKey,u8 Force){//�õ���ǰƵ��
	return Force_Array_Frequency[CurrentPianoKey][Force];//ϵͳʱ��Ƶ��72M����Ƶϵ��18�����ϼ�����ֵ100��Force_Array[0]Ϊ����������
	//72M/18/100/Force_Array_Base[CurrentPianoKey][Force]
	//ϵͳʱ��Ƶ��/��Ƶϵ��/�Զ���װ��/������Ҫ�������жϴ���
}
int getCurrentDuty(u8 CurrentPianoKey,u8 Force){
	
		return Force_Array_Duty[CurrentPianoKey][Force];
}
//set functions

void setDebugControlInfo(DebugMsg_t* DebugMsg,DebugControl_e dc){
	if(!DebugMsg)                                                                     
		return;
	DebugMsg->debugInfo.DControl = dc;
}
void setDebugArgInfo(DebugMsg_t* DebugMsg,ArgType_e at){
	if(! DebugMsg)
		return;
	DebugMsg->debugInfo.DControl = at;
}
void setDebugData(DebugMsg_t* DebugMsg,u8 *data){
	if(!DebugMsg)
		return;
	byteCopy(DebugMsg,(u8*)data,DebugMsg->dataLength);
}

void setDebugRhythminfo(DebugMsg_t* DebugMsg,u8 rhythm){
	if(!DebugMsg)
		return;
	DebugMsg->debugInfo.Rhythm=rhythm;	
	}

void setCurrentFrequency(u8 CurrentPianoKey,u8 Force , int Frequency){
	
	Force_Array_Frequency[CurrentPianoKey][Force] = Frequency ;
	Force_Array_Base[CurrentPianoKey][Force] = 40000/Frequency;
	Force_Array[CurrentPianoKey][Force] =  Force_Array_Base[CurrentPianoKey][Force]*(float)Force_Array_Duty[CurrentPianoKey][Force]/100;
}
void setCurrentDuty(u8 CurrentPianoKey,u8 Force , u8 Duty){
	
	Force_Array_Duty[CurrentPianoKey][Force] = Duty;
	Force_Array[CurrentPianoKey][Force] =  Force_Array_Base[CurrentPianoKey][Force]*(float)Force_Array_Duty[CurrentPianoKey][Force]/100;
}


//reset inside sDebugMsg & sComMsgForDebug
void resetDebugMsg(void){
	memorySet((u8*)&CurrentDebugMsg,0,sizeof(DebugMsg_t));
}
void DebugMsg_send(u8 Rhythm,u8 Force)
{
	
	CAN_SetMsg(Rhythm,Force);
	CAN_Transmit(CAN1,&TxMessage);
}

/*
	those function follows are applied for interpreting DebugMsg   
*/

//all types of function offered for the Modifying
void Debug_Modify(DebugMsg_t* DebugMsg){//ͨ����Force_Array��������޸����Ƶ�ʺ�ռ�ձȵ��޸�
	u8 Force,Duty,Rhythm;
	u16 Frequency;
	Rhythm = DebugMsg->debugInfo.Rhythm;
	if(Rhythm <= PWM_NUM){
		Force=DebugMsg->data[0];
		if(DebugMsg->debugInfo.DControl == 0x10){//�޸�Ƶ��
			Frequency=DebugMsg->data[1]*256+DebugMsg->data[2];
			printf("��Ƶ��Ϊ%d\r\n",getCurrentFrequency(Rhythm,Force));
			setCurrentFrequency(Rhythm,Force,Frequency);
			printf("�޸ĺ�Ƶ��Ϊ%d\r\n",getCurrentFrequency(Rhythm,Force));
			}
			
		else if(DebugMsg->debugInfo.DControl == 0x11){//�޸�ռ�ձ�
			Duty=DebugMsg->data[1];
			printf("��ռ�ձ�Ϊ%d\r\n",getCurrentDuty(Rhythm,Force));
			setCurrentDuty(Rhythm,Force,Duty);
			printf("�޸ĺ�ռ�ձ�Ϊ%d\r\n",getCurrentDuty(Rhythm,Force));
		} 
			}
	else return;
	}

void Debug_Query(DebugMsg_t* DebugMsg){//
	u8 Force,Rhythm;
	if(DebugMsg->debugInfo.Rhythm<=PWM_NUM){
		Rhythm = DebugMsg->debugInfo.Rhythm;
		Force = DebugMsg->data[0];
		DebugMsg_send(Rhythm,Force);
	}
	else return;
}

void Debug_Play(DebugMsg_t* DebugMsg){//�����ܵ��Ĳ���ʱ������1000
	u8 Rhythm,Force,time;
	u32 Timecount=0;
	
	if(DebugMsg->debugInfo.Rhythm<=PWM_NUM){
		Force=DebugMsg->data[0];
		time=DebugMsg->data[1];
		Rhythm=DebugMsg->debugInfo.Rhythm;
		
		GetPresure( Rhythm , Force);//���°���
		Delay_ms(1000);//��ʱ1��
		PWM_close(Rhythm,0);
		
	}
	else return;
}

void Debug_Stop(DebugMsg_t* DebugMsg){
	u8 i=0;
	for(i=0;i<=PWM_NUM;i++)
		PWM_close(i,0);
	printf("ֹͣ�������\r\n");
}

void MSG_interpret(DebugMsg_t* dMsg){
	if(!dMsg)
		return;
	printf("������Է������\r\n");
	switch(dMsg->debugInfo.DControl){//determin which DControl
		case eDC_Modify_Frequency:   Debug_Modify(dMsg); break;//�޸�Ƶ�ʲ������
		case eDC_Modify_Duty:   Debug_Modify(dMsg); break;//�޸�ռ�ձȲ������
		case eDC_Query:   Debug_Query(dMsg); break;//��ѯ�������
		case eDC_Stop: 	Debug_Stop(dMsg); break;//ֹͣ�������
		case eDC_Play:   Debug_Play(dMsg); break;//���Ų������
		default: break;
		}
	}



