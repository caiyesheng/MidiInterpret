#include "can.h" 
CanTxMsg TxMessage,RxMessage;
extern u8 Force_Array_Base[85][9];
extern u8 Force_Array[85][9];
/**************************************
 * 文件名  ：can.c
 * 描述    ：CAN通信协议实现
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/	
 
static void CAN_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
   	
  	/*外设时钟设置*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
  	/*IO设置*/
		//GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	
		/* Configure CAN pin: RX PA11*/									          
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	             // 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
    
		/* Configure CAN pin: TX PA12 */									               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/*
 * 函数名：CAN_NVIC_Config
 * 描述  ：CAN的NVIC 配置,第1优先级组，0，0优先级
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_NVIC_Config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 	/*中断设置*/
		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * 函数名：CAN_Mode_Config
 * 描述  ：CAN的模式 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_Mode_Config(void)
{
   	CAN_InitTypeDef        CAN_InitStructure;
	 	/************************CAN通信参数设置**********************************/
		/*CAN寄存器初始化*/
		CAN_DeInit(CAN1);
		CAN_StructInit(&CAN_InitStructure);
		/*CAN单元初始化*/
		CAN_InitStructure.CAN_TTCM=DISABLE;			   //MCR-TTCM  时间触发通信模式使能
    CAN_InitStructure.CAN_ABOM=DISABLE;			   //MCR-ABOM  自动离线管理 
    CAN_InitStructure.CAN_AWUM=ENABLE;			   //MCR-AWUM  自动唤醒模式
    CAN_InitStructure.CAN_NART=ENABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
    CAN_InitStructure.CAN_RFLM=DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
    CAN_InitStructure.CAN_TXFP=ENABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //正常发送模式
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW 重新同步跳跃宽度 2个时间单元
    CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 时间段1 占用了6个时间单元
    CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元
    CAN_InitStructure.CAN_Prescaler = 4;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 36/(1+5+3)/4=1Mbps
		CAN_Init(CAN1, &CAN_InitStructure);
}

/*
 * 函数名：CAN_Filter_Config
 * 描述  ：CAN的过滤器 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_Filter_Config(void)
{
		CAN_FilterInitTypeDef  CAN_FilterInitStructure;

		/*CAN过滤器初始化*/
		CAN_FilterInitStructure.CAN_FilterNumber=0;						//过滤器组0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	//工作在标识符屏蔽位模式
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	//过滤器位宽为单个32位。
		/* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */

    CAN_FilterInitStructure.CAN_FilterIdHigh=  (((u32)0x0007<<21)&0xFFFF0000)>>16;				//要过滤的ID高位 
    CAN_FilterInitStructure.CAN_FilterIdLow=  (((u32)0x0007<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;//要过滤的ID低位 
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xFFFF;			//过滤器高16位每位必须匹配
    CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0xFFFF;			//过滤器低16位每位必须匹配
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=	CAN_FilterFIFO0 ;				//过滤器被关联到FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=	ENABLE;			//使能过滤器
		CAN_FilterInit(&CAN_FilterInitStructure);
		/*CAN通信中断使能*/
		CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


/*
 * 函数名：CAN_Config
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void CAN_Config(void)
{
  CAN_GPIO_Config();
  CAN_NVIC_Config();
  CAN_Mode_Config();
  CAN_Filter_Config();   
}
/*
 * 函数名：CAN_SetMsg
 * 描述  ：CAN通信报文内容设置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */	 
void CAN_SetMsg(u8 Rhythm,u8 Force)
{	  
  TxMessage.StdId=0x0002;						 
  //TxMessage.ExtId=0x00;					 //使用的扩展ID
  TxMessage.IDE=CAN_ID_STD;					 //扩展模式
  TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
  TxMessage.DLC=3;							 //数据长度为2字节
  TxMessage.Data[0]=(u16)getCurrentFrequency(Rhythm,Force)>>8;
  TxMessage.Data[1]=(u16)getCurrentFrequency(Rhythm,Force)&0x00FF;//需要用两个字节一个数字
	TxMessage.Data[2]=getCurrentDuty(Rhythm,Force);
	//TxMessage.Data[3]=Force_Array[Rhythm][Force];
	//TxMessage.Data[4]=Force_Array_Base[Rhythm][Force];
}

/*************************END OF FILE******************************/

