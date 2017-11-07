/*
**************************
file info:
	author:fang.junpeng
	start time:2016-04-07
	email:tfzsll@126.com
	protocol define for ISDebug,mian for argumet test
***************************
*/

#include "stm32f10x.h"
#include "Msgconfiguration.h"
#include "PWM.h"
#include "Play.h"
#include "util.h"
#include "can.h"
#include "SysTick.h"
#include "time.h"

#ifndef ISDEBUG_H
#define ISDEBUG_H
extern volatile PWMCon_t PWMCon[PWM_NUM];
// get functions


u8 getDebugControlInfo(DebugMsg_t* dMsg);
u8 getDebugArgInfo(DebugMsg_t* dMsg);
u8* getDebugData(DebugMsg_t* dMsg);
u8 getDebugRhythmInfo(DebugMsg_t* dMsg);
int getCurrentFrequency(u8 PianoKey,u8 Force);
int getCurrentDuty(u8 PianoKey,u8 Force);
//set functions
void setDebugControlInfo(DebugMsg_t* DebugMsg,DebugControl_e dc);
void setDebugArgInfo(DebugMsg_t* DebugMsg,ArgType_e at);
void setDebugData(DebugMsg_t* DebugMsg,u8* data);
void setDebugRhythminfo(DebugMsg_t* DebugMsg,u8 rhythm);
void setCurrentFrequency(u8 PianoKey,u8 Force, int Frequency);
void setCurrentDuty(u8 PianoKey,u8 Force,u8 Duty);
//reset inside sDebugMsg & sComMsgForDebug
void resetDebugMsg(void);
void DebugMsg_send(u8 Rhythm,u8 Force);
void Debug_Modify(DebugMsg_t* DebugMsg);
void Debug_Query(DebugMsg_t* DebugMsg);
void Debug_Play(DebugMsg_t* DebugMsg);
void Debug_Stop(DebugMsg_t* DebugMsg);
void MSG_interpret(DebugMsg_t* dMsg);

#endif

