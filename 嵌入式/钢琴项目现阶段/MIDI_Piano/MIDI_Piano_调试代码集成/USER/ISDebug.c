/**************************************
 * 文件名  ：ISDebug.c
 * 描述    ：调试软件处理函数
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/	
#include "ISDebug.h"
#include "util.h"
#include "can.h"
#include "SysTick.h"
#include "time.h"
extern  DebugMsg_t CurrentDebugMsg ;
extern int Force_Array[85][9],Force_Array_Base[85][9],Force_Array_Duty[85][9],Force_Array_Frequency[85][9];
extern u8 CurrentPianoKey;//标志现在操作的音符号
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
int getCurrentFrequency(u8 CurrentPianoKey,u8 Force){//得到当前频率
	return Force_Array_Frequency[CurrentPianoKey][Force];//系统时针频率72M、分频系数18、向上计数阈值100，Force_Array[0]为跳变总周期
	//72M/18/100/Force_Array_Base[CurrentPianoKey][Force]
	//系统时针频率/分频系数/自动重装载/跳变需要经过的中断次数
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
void Debug_Modify(DebugMsg_t* DebugMsg){//通过对Force_Array数组进行修改完成频率和占空比的修改
	u8 Force,Duty,Rhythm;
	u16 Frequency;
	Rhythm = DebugMsg->debugInfo.Rhythm;
	if(Rhythm <= PWM_NUM){
		Force=DebugMsg->data[0];
		if(DebugMsg->debugInfo.DControl == 0x10){//修改频率
			Frequency=DebugMsg->data[1]*256+DebugMsg->data[2];
			printf("现频率为%d\r\n",getCurrentFrequency(Rhythm,Force));
			setCurrentFrequency(Rhythm,Force,Frequency);
			printf("修改后频率为%d\r\n",getCurrentFrequency(Rhythm,Force));
			}
			
		else if(DebugMsg->debugInfo.DControl == 0x11){//修改占空比
			Duty=DebugMsg->data[1];
			printf("现占空比为%d\r\n",getCurrentDuty(Rhythm,Force));
			setCurrentDuty(Rhythm,Force,Duty);
			printf("修改后占空比为%d\r\n",getCurrentDuty(Rhythm,Force));
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

void Debug_Play(DebugMsg_t* DebugMsg){//将接受到的播放时长乘以1000
	u8 Rhythm,Force,time;
	u32 Timecount=0;
	
	if(DebugMsg->debugInfo.Rhythm<=PWM_NUM){
		Force=DebugMsg->data[0];
		time=DebugMsg->data[1];
		Rhythm=DebugMsg->debugInfo.Rhythm;
		
		GetPresure( Rhythm , Force);//按下按键
		Delay_ms(1000);//延时1秒
		PWM_close(Rhythm,0);
		
	}
	else return;
}

void Debug_Stop(DebugMsg_t* DebugMsg){
	u8 i=0;
	for(i=0;i<=PWM_NUM;i++)
		PWM_close(i,0);
	printf("停止程序完成\r\n");
}

void MSG_interpret(DebugMsg_t* dMsg){
	if(!dMsg)
		return;
	printf("进入调试翻译程序\r\n");
	switch(dMsg->debugInfo.DControl){//determin which DControl
		case eDC_Modify_Frequency:   Debug_Modify(dMsg); break;//修改频率操作入口
		case eDC_Modify_Duty:   Debug_Modify(dMsg); break;//修改占空比操作入口
		case eDC_Query:   Debug_Query(dMsg); break;//查询操作入口
		case eDC_Stop: 	Debug_Stop(dMsg); break;//停止操作入口
		case eDC_Play:   Debug_Play(dMsg); break;//播放操作入口
		default: break;
		}
	}



