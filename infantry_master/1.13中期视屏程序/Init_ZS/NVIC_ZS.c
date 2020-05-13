#include "init.h"
void NvicInitType(void)
{
	/************************************************
遥控 0 0
CAN1接收 0 1
外部中断线4/MPU9250 中断 0 2
CAN2接收 1 0
  PC接收 1 1
  外部中断线9-5 按键中断 1 2
  外部中断线15-10 检测中断 1 2
CAN1发送 7 0  未使用
CAN2发送 7 1 未使用
***********************************************/

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //DUS接收中断                      
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);
		/*****************************************设置RX中断**********************************************/        
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;									//选择中断通道为CAN_TX
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;						//设置抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;									//设置副优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/******************************************设置TX中断**********************************************/        
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;             
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);   
/*****************************************设置RX中断**********************************************/        
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;									//选择中断通道为CAN_RX
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;						//设置抢占优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;									//设置副优先级为1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
/******************************************设置TX中断**********************************************/        
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;           //未使用
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);    
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//MPU6050中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   //MPU6050中断                      
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
//	NVIC_Init(&NVIC_InitStructure);

}

