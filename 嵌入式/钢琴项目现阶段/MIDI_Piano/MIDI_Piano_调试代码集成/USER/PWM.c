/**************************************
 * 文件名  ：PWM.c
 * 描述    ：生成对应力度的PWM波形
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/	
#include "PWM.h"
PWMCon_t PWMCon[PWM_NUM];
int Force_Array_Duty[PWM_NUM+1][ForceNum+1] = {  {0,0,0,0,0,0,0,0,0},//各琴键力度占空比
														
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//1 to 12
															
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//13 to 24
															
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//25 to 36
														
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//37 to 48
																
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//49 to 60
														
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//61 to 72
															
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},
														{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},{0,35,36,38,40,41,43,46,50},//73 to 84	
			};
			
int Force_Array_Frequency[PWM_NUM+1][ForceNum+1] = {  {0,0,0,0,0,0,0,0,0},//各琴键力度

																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//1 to 12
																	 
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//13 to 24
																	
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//25 to 36
																
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//37 to 48
																	
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//49 to 60

																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//61 to 72
																
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},
																 {0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},{0,400,400,400,400,400,400,400,400},//73 to 84	 
																	
																};
int Force_Array_Base[PWM_NUM+1][ForceNum+1];//中断计数上限
int Force_Array[PWM_NUM+1][ForceNum+1];//中断计数占空比跳变点								
void Force_init(void)
{
	int i,j;
	for(i = 1; i<=PWM_NUM ; i++ )
		for(j = 1 ; j<=ForceNum ;j++)
		{
			Force_Array_Base[i][j] = 40000/Force_Array_Frequency[i][j];//100
		}
		
	for(i = 1; i<=PWM_NUM ; i++ )
		for(j = 1 ; j<=ForceNum ;j++)
		{
			Force_Array[i][j] = (int)(Force_Array_Base[i][j] * (float)Force_Array_Duty[i][j]/100);
		}
}																
int getBaseFromForce(u8 PianoKey,u8 Force){//
	
	if(Force == 8)
		return Force_Array_Base[PianoKey][8];
	if(Force == 7)
		return Force_Array_Base[PianoKey][7];
	if(Force == 6)
		return Force_Array_Base[PianoKey][6];
	if(Force == 5)
		return Force_Array_Base[PianoKey][5];
	if(Force == 4)
		return Force_Array_Base[PianoKey][4];
	if(Force == 3)
		return Force_Array_Base[PianoKey][3];
	if(Force == 2)
		return Force_Array_Base[PianoKey][2];
	if(Force == 1)
		return Force_Array_Base[PianoKey][1];
	return 0;
}
int getBasedutyFromForce(u8 PianoKey,u8 Force){//
	if(Force == 8)
		return Force_Array[PianoKey][8];
	if(Force == 7)
		return Force_Array[PianoKey][7];
	if(Force == 6)
		return Force_Array[PianoKey][6];
	if(Force == 5)
		return Force_Array[PianoKey][5];
	if(Force == 4)
		return Force_Array[PianoKey][4];
	if(Force == 3)
		return Force_Array[PianoKey][3];
	if(Force == 2)
		return Force_Array[PianoKey][2];
	if(Force == 1)
		return Force_Array[PianoKey][1];
	return 0;
}
  
void GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  // set GPIOA
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); //  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOA , &GPIO_InitStructure);  //
	GPIO_SetBits(GPIOA, GPIO_Pin_All);
	
	// set GPIOB
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); //   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOB , &GPIO_InitStructure);  //
	//引脚B3、B3引脚复用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_3|GPIO_Pin_4);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能映射
	
	GPIO_SetBits(GPIOB, GPIO_Pin_All);
}

//init PWM Cfg
void PWM_init(void){
	// set 84 gpio
	GPIO_Config();
	Force_init();
	PWMCon_MAPING_GPIO();
	PWMCon_PianoKeyset();
}
void PWMCon_PianoKeyset()//按照琴键映射表来设置每个PWMCon结构体对应的琴键
{
	
	
}
void PWMCon_MAPING_GPIO(void)// 引脚B连接钢琴，引脚A用来复用
{
	int j;
	
		for(j = 1; j <= 12; j++)
		{
			PWMCon[j].GPIO_Pin = GPIO_Pin_0 * pow(2,j-1);
			PWMCon[j].GPIO = B;
		}
	
}
//close PWM
void PWM_close(u16 PianoKey,long DelayTime){
	
	PWMCon[PianoKey].state=PianoKeyOff;
	GPIO_SetBits(GPIOB, PWMCon[PianoKey].GPIO_Pin);
	PWMCon[PianoKey].time = 0;
	PMW_Delay(PianoKey,DelayTime);
}
void PMW_Delay(u8 PianoKey,long DelayTime)
{
	PWMCon[PianoKey].state= PianoKeyOff ;
	//287默认发送的延时时间为1毫秒，而DelayTime的时间单位为0.025毫秒，所以需要乘上倍数DelayTimeMulti(40)
	PWMCon[PianoKey].DelayTime = DelayTimeMulti * DelayTime;
}
void PWM_Shutdown(void)
{
	int i;
	for(i = 1; i <= 12; i++)
	 GPIO_SetBits(GPIOB, PWMCon[i].GPIO_Pin);
}

long extern TIM2_Interrupt_Time[13];
extern ChangingForceBlock ControlForceBlock[13]; 

void PWM_Interrupt_Tim2(void){
	int pianoKey;
	for(pianoKey = 1; pianoKey <= 12; pianoKey++)
	{//轮询该从控板的所有键位
		if(PWMCon[pianoKey].state == PianoKeyOn||PWMCon[pianoKey].DelayTime > 0)
			{
			TIM2_Interrupt_Time_Control(pianoKey);//利用中断控制一个琴键在12000次中断后没有收到任何指令则关闭琴键
			if(ControlForceBlock[pianoKey].interruptTime > 0)//如果力度控制块中的剩余力度次数大于0，则进入力度控制程序
				ChangingForceTimeProcess(pianoKey);
			PWM_Continue(pianoKey);			
			}
		else
			PWM_close(pianoKey,0);
	}
}


void ChangingForceTimeProcess(u8 pianoKey)
{
		ControlForceBlock[pianoKey].interruptTime--;//中断次数减1
		if(ControlForceBlock[pianoKey].interruptTime == 0 )//如果剩余中断次数为0，则准备考虑是否变到下一个力度或者停止改变
			{
				if(ControlForceBlock[pianoKey].currentForcePlace <ControlForceBlock[pianoKey].degree)//如果力度渐变栈未渐变完毕
				{
					
					GetPresure(pianoKey,ControlForceBlock[pianoKey].controlForceQuery[ControlForceBlock[pianoKey].currentForcePlace]);//力度改变
					ControlForceBlock[pianoKey].currentForcePlace++;//力度控制栈位置进1
					ControlForceBlock[pianoKey].interruptTime = ControlForceBlock[pianoKey].constantInterruptTime;//剩余中断次数重置
				}		
				else if(ControlForceBlock[pianoKey].currentForcePlace == ControlForceBlock[pianoKey].degree)//力度渐变栈到最后一个
				{
					
					GetPresure(pianoKey,ControlForceBlock[pianoKey].controlForceQuery[ControlForceBlock[pianoKey].currentForcePlace]);//改变力度
					ControlForceBlock[pianoKey].currentForcePlace++;
				}
			}
		
}
//这个函数只要是在STM32的某一琴键只收到了开音而没有收到关音的情况下，让琴键能在经历12000次中断仍没有得到任何操作的情况下，自主关闭琴键
void  TIM2_Interrupt_Time_Control(u8 pianoKey)
{
		if(TIM2_Interrupt_Time[pianoKey] == 0 )//12000次中断(3秒)内没有得到操作命令,则关闭琴键然后重置中断次数
			{
				PWM_close(pianoKey,0);
				TIM2_Interrupt_Time[pianoKey]=120000;
			}
		TIM2_Interrupt_Time[pianoKey]--;
}

