/**************************************
 * �ļ���  ��PWM.c
 * ����    �����ɶ�Ӧ���ȵ�PWM����
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ���
 * ��汾  ��ST3.0.0  

*********************************************************/	
#include "PWM.h"
PWMCon_t PWMCon[PWM_NUM];
int Force_Array_Duty[PWM_NUM+1][ForceNum+1] = {  {0,0,0,0,0,0,0,0,0},//���ټ�����ռ�ձ�
														
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
			
int Force_Array_Frequency[PWM_NUM+1][ForceNum+1] = {  {0,0,0,0,0,0,0,0,0},//���ټ�����

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
int Force_Array_Base[PWM_NUM+1][ForceNum+1];//�жϼ�������
int Force_Array[PWM_NUM+1][ForceNum+1];//�жϼ���ռ�ձ������								
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
	//����B3��B3���Ÿ���
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_3|GPIO_Pin_4);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//ʹ��ӳ��
	
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
void PWMCon_PianoKeyset()//�����ټ�ӳ���������ÿ��PWMCon�ṹ���Ӧ���ټ�
{
	
	
}
void PWMCon_MAPING_GPIO(void)// ����B���Ӹ��٣�����A��������
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
	//287Ĭ�Ϸ��͵���ʱʱ��Ϊ1���룬��DelayTime��ʱ�䵥λΪ0.025���룬������Ҫ���ϱ���DelayTimeMulti(40)
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
	{//��ѯ�ôӿذ�����м�λ
		if(PWMCon[pianoKey].state == PianoKeyOn||PWMCon[pianoKey].DelayTime > 0)
			{
			TIM2_Interrupt_Time_Control(pianoKey);//�����жϿ���һ���ټ���12000���жϺ�û���յ��κ�ָ����ر��ټ�
			if(ControlForceBlock[pianoKey].interruptTime > 0)//������ȿ��ƿ��е�ʣ�����ȴ�������0����������ȿ��Ƴ���
				ChangingForceTimeProcess(pianoKey);
			PWM_Continue(pianoKey);			
			}
		else
			PWM_close(pianoKey,0);
	}
}


void ChangingForceTimeProcess(u8 pianoKey)
{
		ControlForceBlock[pianoKey].interruptTime--;//�жϴ�����1
		if(ControlForceBlock[pianoKey].interruptTime == 0 )//���ʣ���жϴ���Ϊ0����׼�������Ƿ�䵽��һ�����Ȼ���ֹͣ�ı�
			{
				if(ControlForceBlock[pianoKey].currentForcePlace <ControlForceBlock[pianoKey].degree)//������Ƚ���ջδ�������
				{
					
					GetPresure(pianoKey,ControlForceBlock[pianoKey].controlForceQuery[ControlForceBlock[pianoKey].currentForcePlace]);//���ȸı�
					ControlForceBlock[pianoKey].currentForcePlace++;//���ȿ���ջλ�ý�1
					ControlForceBlock[pianoKey].interruptTime = ControlForceBlock[pianoKey].constantInterruptTime;//ʣ���жϴ�������
				}		
				else if(ControlForceBlock[pianoKey].currentForcePlace == ControlForceBlock[pianoKey].degree)//���Ƚ���ջ�����һ��
				{
					
					GetPresure(pianoKey,ControlForceBlock[pianoKey].controlForceQuery[ControlForceBlock[pianoKey].currentForcePlace]);//�ı�����
					ControlForceBlock[pianoKey].currentForcePlace++;
				}
			}
		
}
//�������ֻҪ����STM32��ĳһ�ټ�ֻ�յ��˿�����û���յ�����������£����ټ����ھ���12000���ж���û�еõ��κβ���������£������ر��ټ�
void  TIM2_Interrupt_Time_Control(u8 pianoKey)
{
		if(TIM2_Interrupt_Time[pianoKey] == 0 )//12000���ж�(3��)��û�еõ���������,��ر��ټ�Ȼ�������жϴ���
			{
				PWM_close(pianoKey,0);
				TIM2_Interrupt_Time[pianoKey]=120000;
			}
		TIM2_Interrupt_Time[pianoKey]--;
}

