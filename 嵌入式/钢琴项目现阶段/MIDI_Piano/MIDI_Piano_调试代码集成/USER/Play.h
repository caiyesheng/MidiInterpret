#ifndef __PLAY_H
#define __PLAY_H

#include "PWM.H"
#include <stdlib.h>

#define ClosePianoKey 8
#define OpenPianoKey 9
#define FirstPlace 1
typedef struct
{
	int controlForceQuery[8];//���Ƚ���ջ������������е���������ѹ��ջ��
	int currentForcePlace ;//��ǰ���Ƚ���ջ��λ��
	float timePiece;//ÿһ�����ȳ���ʱ��
	long interruptTime;//ÿһ�����ȳ���ʱ����Ҫ�������жϴ���(���)
	long constantInterruptTime;//ÿһ�����ȳ���ʱ����Ҫ�������жϴ��������䣩
	int degree;//��ʼ�������������ȵĲ�ֵ
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



