/***************************************
 * 文件名  ：main.c
 * 描述    ：自动智能钢琴弹奏系统         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0   *
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
		if(Flag_DebugMsg){//调试协议入口
			byteCopy(CurrentDebugMsg,RxBuffer1,8);//按照最后的发送报文格式进行拷贝。
			MSG_interpret(CurrentDebugMsg);
			Flag_DebugMsg = FlagOff;
		}
		if(Flag_PlaySong){//收到弹奏指令入口
			CAN_Play();
			Flag_PlaySong = FlagOff;
		}
		if(Flag_PWM){//PWM跳变入口
			PWM_Interrupt_Tim2();
			Flag_PWM = FlagOff; 
		}
	}
}


void BasicConfiguretion(void)
{
	SystemInit(); // 配置系统时钟为 72M 
	PWM_init();//初始化配置所有需要用到的引脚以及完全琴键与引脚的映射关系配置
	USART1_Config();
	SysTick_Init();//问题：PWM波形无法在此延时中产生
	CAN_Config();
	TIM2_NVIC_Configuration(); // TIM2 定时配置
  TIM2_Configuration(); 	
	START_TIME;	 // TIM2 开始计时
}

		
	
	



