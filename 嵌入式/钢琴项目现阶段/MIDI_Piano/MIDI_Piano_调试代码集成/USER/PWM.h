/*
**************************
file info:
	author:fang.junpeng
	start time:2016-03-24
	email:tfzsll@126.com
	for PWM output
***************************
*/

#include "stm32f10x.h"
#include "stdio.h"
#include "Play.h"
#include "math.h"
#ifndef PWM_H
#define PWM_H
#define PWM_NUM 84
#define ForceNum 8
#define DelayTimeMulti 40
#define PianoKeyOn 1 
#define PianoKeyOff 0
typedef struct{
	u16 GPIO_Pin;//���ź�
	u8 GPIO;//��������A��B
	u16 PianoKey;//�ټ���
	u16 Frequency;//Ƶ��
	u16 Duty;//ռ�ձ�
	u16 Base;//PWM��������
	u16 Baseduty;//ռ�ձ�PWM����ֵ
	u8 state;//�Ƿ�������
	u16 time;//��¼��һ�����ŵ�ƽ���������ں�ʱ���е�ƽ�ߵ͸ı�
	u8 Action;//����Э��ʱ�Ĳ�������
	u8 startForce;//�������ȿ�ʼ����
	u8 endForce;//�������Ƚ�������
	long lastTime;//���������ټ�����ʱ�䣬�ǽ���û�иñ���
	long DelayTime;//��¼һ���ټ��ڽ��ܵ�ָֹͣ�����Ҫ���������ʱ��
	long RestTimeForChangeForce;//��¼һ���ټ���һ����Ҫ�ı�������Ҫ�������жϴ���
}PWMCon_t;

void PWMCon_MAPING_GPIO(void);

int getBaseFromForce(u8 PianoKey,u8 Force);

int getBasedutyFromForce(u8 PianoKey,u8 Force);

void  KeyToGPIO(void);

int getPWMLifetime(u16 i);

//init PWM Cfg
void PWM_init(void);
void Force_init(void);
void GPIO_Config(void);
void PMW_Delay(u8 PianoKey,long Lifetime);
void PWMCon_PianoKeyset();
void PWM_Shutdown(void);
//close PWM
void PWM_close(u16 PianoKey,long DelayTime);
//for call back
void PWM_callback(int argc,void **argv);
void PWM_Interrupt_Tim2(void);
#endif

