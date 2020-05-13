#include "init.h"


/*----CAN1_TX-----PA12----*/
/*----CAN1_RX-----PA11----*/

/*************************************************************************
�������ƣ�CAN1_Configuration
�������ܣ���ʼ��CAN1����Ϊ1M������
*************************************************************************/
void CAN1_Configuration(void)
{
		/*****************************************�����ģ��ṹ�����**********************************************/  	
    CAN_InitTypeDef        CAN_InitStruct;
    CAN_FilterInitTypeDef  CAN_InitFilter;
    GPIO_InitTypeDef       GPIO_InitStruct;
		/*******************************************ʹ��ʱ��**********************************************/  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

		/*******************************����CAN���������Ӧ��IO�ڸ��ù���*********************************/  
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	
	
		/********************************************��λCAN1**********************************************/        
    CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStruct);
		/*************************************��ʼ��CAN����ģʽ��������************************************/    
    CAN_InitStruct.CAN_TTCM = DISABLE;													//ʧ��ʱ�䴥��ͨ��ģʽ
    CAN_InitStruct.CAN_ABOM = DISABLE;													//ʧ���Զ������߹رչ���
    CAN_InitStruct.CAN_AWUM = DISABLE;													//ʧ���Զ�����ģʽ
    CAN_InitStruct.CAN_NART = DISABLE;													//ʹ���Զ��ط�����
    CAN_InitStruct.CAN_RFLM = DISABLE;													//����FIFO�������������һ������ǰһ��
    CAN_InitStruct.CAN_TXFP = ENABLE;														//ʹ�ܷ���FIFO�����ȼ�
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;								//����CAN���߹����ڻػ�ģʽ
		/*************************************
			BaudRate = 1 / NominalBitTime,
			NominalBitTime = tq + tBS1 + tBS2,
			tBS1 = tq x (TS1[3:0] + 1),
			tBS2 = tq x (TS2[2:0] + 1),
			tq = (BRP[9:0] + 1) x tPCLK,
			tPCLK = APB ʱ������
			***********************************/
    CAN_InitStruct.CAN_SJW  = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStruct.CAN_Prescaler = 3;   																//CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN1, &CAN_InitStruct);
		/*************************************��ʼ����������************************************/
		//CAN1�Ĺ��������0-13
		CAN_InitFilter.CAN_FilterNumber = 0;													//ѡ���������0
		CAN_InitFilter.CAN_FilterMode = CAN_FilterMode_IdMask;				//���ñ�ʶ���б�ģʽ
		CAN_InitFilter.CAN_FilterScale = CAN_FilterScale_32bit;				//���ù�������0��λ��Ϊ32
		CAN_InitFilter.CAN_FilterIdHigh = 0x0000;											//�������й��˱�ʶ��ID��������
		CAN_InitFilter.CAN_FilterIdLow = 0x0000;										
		CAN_InitFilter.CAN_FilterMaskIdHigh = 0x0000;									//�������е�ID��Ϊ���ù��ģ�����������
		CAN_InitFilter.CAN_FilterMaskIdLow = 0x0000;									
		CAN_InitFilter.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;									//���ù���������һ��FIFO0
		CAN_InitFilter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_InitFilter);															//�˲�����ʼ��
 		/***************************************ʹ��CAN�ж�*************************************/   
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,DISABLE);
}

/*************************************************************************
�������ƣ�CAN1_TX_IRQHandler
�������ܣ�CAN1�ķ����жϺ���
*************************************************************************/
void CAN1_TX_IRQHandler(void)
{
   if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET)
	 {
		 	 CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
	 }
}


/*************************************************************************
�������ƣ�CAN1_RX0_IRQHandler
�������ܣ�CAN1�Ľ����жϺ���
*************************************************************************/

void CAN1_RX0_IRQHandler(void)
{
    CanRxMsg rx_message;
    if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
		{
			 CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
			 CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
       CanReceiveMsgProcess(&rx_message);  
		}
}


