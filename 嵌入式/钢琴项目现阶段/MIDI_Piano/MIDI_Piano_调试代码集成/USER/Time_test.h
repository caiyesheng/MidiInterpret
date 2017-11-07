#ifndef TIME_TEST_H
#define TIME_TEST_H

#include "stm32f10x.h"
 
#define START_TIME  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_Cmd(TIM2, ENABLE); 
													
										//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);TIM_Cmd(TIM3, ENABLE)
#define STOP_TIME  TIM_Cmd(TIM2, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE); \
										//TIM_Cmd(TIM3, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , DISABLE)
void TIM2_NVIC_Configuration(void);
void TIM2_Configuration(void);
void TIM3_NVIC_Configuration(void);
void TIM3_Configuration(void);
#endif	/* TIME_TEST_H */
