#include "nvic.h"
/*
中断优先级：抢占优先级   子优先级 
CAN1接收：2 0
USART1：  1 0
TIM2:     7 1
TIM3:     6 0
*/
void NVIC_Init_User(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	

		NVIC_InitTypeDef  			NVIC_InitStructure;

		NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;	 //CAN接收中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
//		NVIC_InitStructure.NVIC_IRQChannel=USB_HP_CAN1_TX_IRQn;	 
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; 
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
//		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//		NVIC_Init(&NVIC_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
 	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
		
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  	
}


