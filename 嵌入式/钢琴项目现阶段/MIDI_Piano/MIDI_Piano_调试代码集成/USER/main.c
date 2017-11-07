/***************************************
 * �ļ���  ��main.c
 * ����    ���Զ����ܸ��ٵ���ϵͳ         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * ��汾  ��ST3.0.0   *
********************************************************/	
#include "headfile.h"//all headfile here

u8 Flag_DebugMsg,Flag_PlaySong,Flag_PWM;		//interrupt signal
u8 RxBuffer1[20],CurrentPianoKey;
DebugMsg_t   p; 
DebugMsg_t * CurrentDebugMsg = &p;
extern volatile PWMCon_t PWMCon[PWM_NUM] ;
void BasicConfiguretion(void);

	
int main(void)
{
	BasicConfiguretion();// all basic configuretion startup
	printf( "\r\n Stm32 is starting \r\n");
	GetPresure(3,5);
	while(1)
	{
		if(Flag_DebugMsg){//����Э�����
			byteCopy(CurrentDebugMsg,RxBuffer1,8);//�������ķ��ͱ��ĸ�ʽ���п�����
			MSG_interpret(CurrentDebugMsg);
			Flag_DebugMsg = FlagOff;
		}
		if(Flag_PlaySong){//�յ�����ָ�����
			CAN_Play();
			Flag_PlaySong = FlagOff;
		}
		if(Flag_PWM){//PWM�������
			PWM_Interrupt_Tim2();
			Flag_PWM = FlagOff; 
		}
	}
}


void BasicConfiguretion(void)
{
	SystemInit(); // ����ϵͳʱ��Ϊ 72M 
	PWM_init();//��ʼ������������Ҫ�õ��������Լ���ȫ�ټ������ŵ�ӳ���ϵ����
	USART1_Config();
	SysTick_Init();//���⣺PWM�����޷��ڴ���ʱ�в���
	CAN_Config();
	TIM2_NVIC_Configuration(); // TIM2 ��ʱ����
  TIM2_Configuration(); 	
	START_TIME;	 // TIM2 ��ʼ��ʱ
}

		
	
	



