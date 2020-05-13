#include"nvic.h"

#include "nvic.h"
/*
�ж����ȼ�����ռ���ȼ�   �����ȼ� 
CAN1���գ�0 1
CAN1���ͣ�0 2
TIM2:     0 3
TIM3:     0 4
�������ⲿ��0 6
*/
void NVIC_Init_User(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
		NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;	  	 //CAN�����ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					   
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;	 //CAN�����ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //��ռ���ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //�����ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


