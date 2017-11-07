/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "PWM.h"
#include "Play.h"
int sign;
extern volatile u32 time;
extern u8 Flag_DebugMsg;
extern  CanRxMsg RxMessage;
extern volatile u32 CCR,Period;
extern u8 Flag_PlaySong;
extern volatile PWMCon_t PWMCon[PWM_NUM];

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
extern void TimingDelay_Decrement(void);
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval : None
  */
int extern Flag_PWM;
void TIM2_IRQHandler(void)//中断的频率是40000
{
	int i;
	
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) //取中断向量表的状态值
	{	    
			Flag_PWM = FlagOn;	
			TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
			
	}	
}
void TIM3_IRQHandler(void)
{
	
	
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	u8 extern RxBuffer1[2000];
	int RxCount1 = 0;
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  /* 比较是否是发送的数据和ID */ 
	switch((u8)RxMessage.Data[0])
	{
		case DebugProtocolHead:{//调试协议头
		while(RxCount1 < 9)   RxBuffer1[RxCount1++] = (u8)RxMessage.Data[RxCount1];
		Flag_DebugMsg = FlagOn;break;
		//Main函数同步收到标志，进入调试函数
		}
		case PlayProtocolHead:{//播放协议头
		Flag_PlaySong = FlagOn;break;
		}
		
	}//switch
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
