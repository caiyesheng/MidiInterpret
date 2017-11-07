/**************************************
 * 文件名  ：Play.c
 * 描述    ：琴谱弹奏应用函数库（PWM.c文件的扩展）
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/	


#include "play.h"
extern  PWMCon_t PWMCon[PWM_NUM];
long TIM2_Interrupt_Time[13] = {100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000};
void GetPresure(u8 Keynum ,u8 Force )//按下琴键
{
	PWMCon[Keynum].Baseduty = getBasedutyFromForce(Keynum, Force);
	PWMCon[Keynum].Base = getBaseFromForce(Keynum, Force);
	PWMCon[Keynum].state = PianoKeyOn;
	PWMCon[Keynum].time = 0 ;
	TIM2_Interrupt_Time[Keynum]=100000;
	//PWMCon[Keynum].LifeTime = Duration;

}

void PWM_Continue( u8 num)//代表弹琴在判断后可继续弹奏
{
	PWMCon[num].time++;
	
	if(PWMCon[num].time == PWMCon[num].Baseduty)
	{
		GPIO_SetBits(GPIOB, PWMCon[num].GPIO_Pin);
	}
			
	else if(PWMCon[num].time==PWMCon[num].Base)
	{
		GPIO_ResetBits(GPIOB, PWMCon[num].GPIO_Pin);
		PWMCon[num].time=0;
	}
	if(PWMCon[num].DelayTime > 0)
		PWMCon[num].DelayTime--; 
	if(PWMCon[num].RestTimeForChangeForce > 0)
	{
		PWMCon[num].RestTimeForChangeForce --;
	}
}
extern CanRxMsg RxMessage;

void StartPlay(u8 Keynum,u8 startForce,u8 endForce,u16 lastTime)
{
	if(startForce == endForce)//needn't change the force when pianokey playing
	{
		GetPresure(Keynum,startForce);
	}
	else if(startForce  !=  endForce)//need to change the force when pianokey playing
	{
		GetChangingPresure(Keynum,startForce,endForce,lastTime);
	}
	
}

void CAN_Play(void)
{
	int pianoKey;
	//RxMessage.Data[0]为播放协议头
	pianoKey = RxMessage.Data[2]% 12;//为使琴键对应到STM32特定引脚上
	if(pianoKey == 0)
		pianoKey = 12;
	//装载数据帧
	PWMCon[pianoKey].PianoKey = pianoKey;
	PWMCon[pianoKey].Action = RxMessage.Data[1];
	PWMCon[pianoKey].startForce = RxMessage.Data[3];
	PWMCon[pianoKey].endForce = RxMessage.Data[4];
	PWMCon[pianoKey].lastTime = RxMessage.Data[5];
	PWMCon[pianoKey].DelayTime = RxMessage.Data[6];
	
	
	if(PWMCon[pianoKey].Action == ClosePianoKey)
		{
			PWM_close(PWMCon[pianoKey].PianoKey,PWMCon[pianoKey].DelayTime);
		}
	else if(PWMCon[pianoKey].Action == OpenPianoKey|| PWMCon[pianoKey].Action == ClosePianoKey)
	{
		if(PWMCon[pianoKey].startForce > 0)//如果接受到力度大于0，i键开始弹奏。
			StartPlay(PWMCon[pianoKey].PianoKey,PWMCon[pianoKey].startForce,PWMCon[pianoKey].endForce,PWMCon[pianoKey].lastTime);
		else //如果接受到力度等于0
			PWM_close(PWMCon[pianoKey].PianoKey,PWMCon[pianoKey].DelayTime);//delay的单位是25us,所以变换后单位变为1ms
	}
}



ChangingForceBlock ControlForceBlock[13]; 

void GetChangingPresure(u8 Keynum,u8 startForce,u8 endForce,u16 lastTime)
{
	int i;
	
	GetPresure(Keynum,startForce);//以起始力度开始
	
	ControlForceBlock[Keynum].degree = endForce - startForce;//得到起始力度和最终力度的差值
	ControlForceBlock[Keynum].timePiece = (float)lastTime / (float)(ControlForceBlock[Keynum].degree+1);//得到力度渐变每个力度阶级的时间
	//中断频率为40000,即0.000025s中断一次，而timePiece的单位为0.02s,所以要多除以50
	ControlForceBlock[Keynum].interruptTime = (int)(ControlForceBlock[Keynum].timePiece / (0.000025*50));//将正常世界的时间转化为所要经历的中断次数
	ControlForceBlock[Keynum].constantInterruptTime = ControlForceBlock[Keynum].interruptTime;//设置一个常量记录下中断次数
	ControlForceBlock[Keynum].currentForcePlace = FirstPlace;//力度队列的头
  ControlForceBlock[Keynum].controlForceQuery[0] = startForce;//力度队列第一个元素初始化
	
	for(i = 1; i<=ControlForceBlock[Keynum].degree ; i++)//力度队列各个元素初始化
	{
		ControlForceBlock[Keynum].controlForceQuery[i] = ControlForceBlock[Keynum].controlForceQuery[i-1] + 
		ControlForceBlock[Keynum].degree / abs(ControlForceBlock[Keynum].degree) ;
	  
	}
}






