#ifndef __PLAY_H
#define __PLAY_H

#include "PWM.H"
#include <stdlib.h>

#define ClosePianoKey 8
#define OpenPianoKey 9
#define FirstPlace 1
typedef struct
{
	int controlForceQuery[8];//力度渐变栈，将渐变过程中的力度依次压入栈中
	int currentForcePlace ;//当前力度渐变栈的位置
	float timePiece;//每一级力度持续时间
	long interruptTime;//每一级力度持续时间需要经历的中断次数(会变)
	long constantInterruptTime;//每一级力度持续时间需要经历的中断次数（不变）
	int degree;//初始力度与最终力度的差值
}ChangingForceBlock;


void GetPresure(u8 Keynum ,u8 startForce);
void StartPlay(u8 Keynum,u8  startForce,u8 endForce,u16 lastTime);
void PWM_Continue( u8 num);
void GetChangingPresure(u8 Keynum,u8 startForce,u8 endForce,u16 lastTime);
void CAN_Play(void);
void ChangingForceTimeProcess(u8 pianoKey);
void TIM2_Interrupt_Time_Control(u8 pianoKey);
enum NUM
{
	B=1
};
#endif



