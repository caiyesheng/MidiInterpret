#include "can.h" 
CanTxMsg TxMessage,RxMessage;
extern u8 Force_Array_Base[85][9];
extern u8 Force_Array[85][9];
/**************************************
 * �ļ���  ��can.c
 * ����    ��CANͨ��Э��ʵ��
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ���
 * ��汾  ��ST3.0.0  

*********************************************************/	
 
static void CAN_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
   	
  	/*����ʱ������*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
  	/*IO����*/
		//GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	
		/* Configure CAN pin: RX PA11*/									          
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	             // ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
    
		/* Configure CAN pin: TX PA12 */									               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/*
 * ��������CAN_NVIC_Config
 * ����  ��CAN��NVIC ����,��1���ȼ��飬0��0���ȼ�
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_NVIC_Config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 	/*�ж�����*/
		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //�����ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������CAN_Mode_Config
 * ����  ��CAN��ģʽ ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_Mode_Config(void)
{
   	CAN_InitTypeDef        CAN_InitStructure;
	 	/************************CANͨ�Ų�������**********************************/
		/*CAN�Ĵ�����ʼ��*/
		CAN_DeInit(CAN1);
		CAN_StructInit(&CAN_InitStructure);
		/*CAN��Ԫ��ʼ��*/
		CAN_InitStructure.CAN_TTCM=DISABLE;			   //MCR-TTCM  ʱ�䴥��ͨ��ģʽʹ��
    CAN_InitStructure.CAN_ABOM=DISABLE;			   //MCR-ABOM  �Զ����߹��� 
    CAN_InitStructure.CAN_AWUM=ENABLE;			   //MCR-AWUM  �Զ�����ģʽ
    CAN_InitStructure.CAN_NART=ENABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
    CAN_InitStructure.CAN_RFLM=DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
    CAN_InitStructure.CAN_TXFP=ENABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //��������ģʽ
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_Prescaler = 4;		   ////BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 36/(1+5+3)/4=1Mbps
		CAN_Init(CAN1, &CAN_InitStructure);
}

/*
 * ��������CAN_Filter_Config
 * ����  ��CAN�Ĺ����� ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_Filter_Config(void)
{
		CAN_FilterInitTypeDef  CAN_FilterInitStructure;

		/*CAN��������ʼ��*/
		CAN_FilterInitStructure.CAN_FilterNumber=0;						//��������0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	//�����ڱ�ʶ������λģʽ
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	//������λ��Ϊ����32λ��
		/* ʹ�ܱ��ı�ʾ�����������ձ�ʾ�������ݽ��бȶԹ��ˣ���չID�������µľ����������ǵĻ��������FIFO0�� */

    CAN_FilterInitStructure.CAN_FilterIdHigh=  (((u32)0x0007<<21)&0xFFFF0000)>>16;				//Ҫ���˵�ID��λ 
    CAN_FilterInitStructure.CAN_FilterIdLow=  (((u32)0x0007<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;//Ҫ���˵�ID��λ 
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xFFFF;			//��������16λÿλ����ƥ��
    CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0xFFFF;			//��������16λÿλ����ƥ��
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=	CAN_FilterFIFO0 ;				//��������������FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=	ENABLE;			//ʹ�ܹ�����
		CAN_FilterInit(&CAN_FilterInitStructure);
		/*CANͨ���ж�ʹ��*/
		CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


/*
 * ��������CAN_Config
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void CAN_Config(void)
{
  CAN_GPIO_Config();
  CAN_NVIC_Config();
  CAN_Mode_Config();
  CAN_Filter_Config();   
}
/*
 * ��������CAN_SetMsg
 * ����  ��CANͨ�ű�����������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */	 
void CAN_SetMsg(u8 Rhythm,u8 Force)
{	  
  TxMessage.StdId=0x0002;						 
  //TxMessage.ExtId=0x00;					 //ʹ�õ���չID
  TxMessage.IDE=CAN_ID_STD;					 //��չģʽ
  TxMessage.RTR=CAN_RTR_DATA;				 //���͵�������
  TxMessage.DLC=3;							 //���ݳ���Ϊ2�ֽ�
  TxMessage.Data[0]=(u16)getCurrentFrequency(Rhythm,Force)>>8;
  TxMessage.Data[1]=(u16)getCurrentFrequency(Rhythm,Force)&0x00FF;//��Ҫ�������ֽ�һ������
	TxMessage.Data[2]=getCurrentDuty(Rhythm,Force);
	//TxMessage.Data[3]=Force_Array[Rhythm][Force];
	//TxMessage.Data[4]=Force_Array_Base[Rhythm][Force];
}

/*************************END OF FILE******************************/

