#include "nvic.h"
/*
�ж����ȼ�����ռ���ȼ�   �����ȼ� 
CAN1���գ�2 0
USART1��  

*/
void NVIC_Init_User(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	

		NVIC_InitTypeDef  			NVIC_InitStructure;

		NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;	 //CAN�����ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //�����ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
//		NVIC_InitStructure.NVIC_IRQChannel=USB_HP_CAN1_TX_IRQn;	 
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; 
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
//		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//		NVIC_Init(&NVIC_InitStructure);	  	
}

