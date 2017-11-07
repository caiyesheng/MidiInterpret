/**************************************
 * �ļ���  ��Play.c
 * ����    �����׵���Ӧ�ú����⣨PWM.c�ļ�����չ��
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ���
 * ��汾  ��ST3.0.0  

*********************************************************/	


#include "play.h"
extern  PWMCon_t PWMCon[PWM_NUM];
long TIM2_Interrupt_Time[13] = {100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000};
void GetPresure(u8 Keynum ,u8 Force )//�����ټ�
{
	PWMCon[Keynum].Baseduty = getBasedutyFromForce(Keynum, Force);
	PWMCon[Keynum].Base = getBaseFromForce(Keynum, Force);
	PWMCon[Keynum].state = PianoKeyOn;
	PWMCon[Keynum].time = 0 ;
	TIM2_Interrupt_Time[Keynum]=100000;
	//PWMCon[Keynum].LifeTime = Duration;

}

void PWM_Continue( u8 num)//���������жϺ�ɼ�������
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
	//RxMessage.Data[0]Ϊ����Э��ͷ
	pianoKey = RxMessage.Data[2]% 12;//Ϊʹ�ټ���Ӧ��STM32�ض�������
	if(pianoKey == 0)
		pianoKey = 12;
	//װ������֡
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
		if(PWMCon[pianoKey].startForce > 0)//������ܵ����ȴ���0��i����ʼ���ࡣ
			StartPlay(PWMCon[pianoKey].PianoKey,PWMCon[pianoKey].startForce,PWMCon[pianoKey].endForce,PWMCon[pianoKey].lastTime);
		else //������ܵ����ȵ���0
			PWM_close(PWMCon[pianoKey].PianoKey,PWMCon[pianoKey].DelayTime);//delay�ĵ�λ��25us,���Ա任��λ��Ϊ1ms
	}
}



ChangingForceBlock ControlForceBlock[13]; 

void GetChangingPresure(u8 Keynum,u8 startForce,u8 endForce,u16 lastTime)
{
	int i;
	
	GetPresure(Keynum,startForce);//����ʼ���ȿ�ʼ
	
	ControlForceBlock[Keynum].degree = endForce - startForce;//�õ���ʼ���Ⱥ��������ȵĲ�ֵ
	ControlForceBlock[Keynum].timePiece = (float)lastTime / (float)(ControlForceBlock[Keynum].degree+1);//�õ����Ƚ���ÿ�����Ƚ׼���ʱ��
	//�ж�Ƶ��Ϊ40000,��0.000025s�ж�һ�Σ���timePiece�ĵ�λΪ0.02s,����Ҫ�����50
	ControlForceBlock[Keynum].interruptTime = (int)(ControlForceBlock[Keynum].timePiece / (0.000025*50));//�����������ʱ��ת��Ϊ��Ҫ�������жϴ���
	ControlForceBlock[Keynum].constantInterruptTime = ControlForceBlock[Keynum].interruptTime;//����һ��������¼���жϴ���
	ControlForceBlock[Keynum].currentForcePlace = FirstPlace;//���ȶ��е�ͷ
  ControlForceBlock[Keynum].controlForceQuery[0] = startForce;//���ȶ��е�һ��Ԫ�س�ʼ��
	
	for(i = 1; i<=ControlForceBlock[Keynum].degree ; i++)//���ȶ��и���Ԫ�س�ʼ��
	{
		ControlForceBlock[Keynum].controlForceQuery[i] = ControlForceBlock[Keynum].controlForceQuery[i-1] + 
		ControlForceBlock[Keynum].degree / abs(ControlForceBlock[Keynum].degree) ;
	  
	}
}






