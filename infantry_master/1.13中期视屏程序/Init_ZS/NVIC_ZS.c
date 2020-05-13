#include "init.h"
void NvicInitType(void)
{
	/************************************************
ң�� 0 0
CAN1���� 0 1
�ⲿ�ж���4/MPU9250 �ж� 0 2
CAN2���� 1 0
  PC���� 1 1
  �ⲿ�ж���9-5 �����ж� 1 2
  �ⲿ�ж���15-10 ����ж� 1 2
CAN1���� 7 0  δʹ��
CAN2���� 7 1 δʹ��
***********************************************/

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //DUS�����ж�                      
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);
		/*****************************************����RX�ж�**********************************************/        
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;									//ѡ���ж�ͨ��ΪCAN_TX
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;						//������ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;									//���ø����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/******************************************����TX�ж�**********************************************/        
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;             
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);   
/*****************************************����RX�ж�**********************************************/        
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;									//ѡ���ж�ͨ��ΪCAN_RX
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;						//������ռ���ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;									//���ø����ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
/******************************************����TX�ж�**********************************************/        
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;           //δʹ��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);    
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//MPU6050�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   //MPU6050�ж�                      
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
//	NVIC_Init(&NVIC_InitStructure);

}

