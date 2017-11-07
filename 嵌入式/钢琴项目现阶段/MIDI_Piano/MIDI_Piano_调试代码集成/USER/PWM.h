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
	u16 GPIO_Pin;//引脚号
	u8 GPIO;//区别引脚A、B
	u16 PianoKey;//琴键号
	u16 Frequency;//频率
	u16 Duty;//占空比
	u16 Base;//PWM跳变上限
	u16 Baseduty;//占空比PWM跳变值
	u8 state;//是否在运行
	u16 time;//记录在一个引脚电平跳变周期内何时进行电平高低改变
	u8 Action;//播放协议时的操作类型
	u8 startForce;//渐变力度开始力度
	u8 endForce;//渐变力度结束力度
	long lastTime;//渐变力度琴键持续时间，非渐变没有该变量
	long DelayTime;//记录一个琴键在接受到停止指令后还需要持续弹奏的时间
	long RestTimeForChangeForce;//记录一个琴键下一次需要改变力度所要经历的中断次数
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

