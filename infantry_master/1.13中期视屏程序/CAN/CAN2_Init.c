#include "init.h"

/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/
//CAN2���������շ�

/*************************************************************************
�������ƣ�CAN2_Configuration
�������ܣ���ʼ��CAN2����Ϊ1M������
*************************************************************************/
void CAN2_Configuration(void)
{
		/*****************************************�����ģ��ṹ�����**********************************************/  	
    CAN_InitTypeDef        CAN_InitStruct;
    CAN_FilterInitTypeDef  CAN_InitFilter;
    GPIO_InitTypeDef       GPIO_InitStruct;
		/*******************************************ʹ��ʱ��**********************************************/  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

		/*******************************����CAN���������Ӧ��IO�ڸ��ù���*********************************/  
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
	

		/********************************************��λCAN2**********************************************/        
    CAN_DeInit(CAN2);
    CAN_StructInit(&CAN_InitStruct);
		/*************************************��ʼ��CAN����ģʽ��������************************************/    
    CAN_InitStruct.CAN_TTCM = DISABLE;													//ʧ��ʱ�䴥��ͨ��ģʽ
    CAN_InitStruct.CAN_ABOM = DISABLE;													//ʧ���Զ������߹رչ���
    CAN_InitStruct.CAN_AWUM = DISABLE;													//ʧ���Զ�����ģʽ
    CAN_InitStruct.CAN_NART = DISABLE;													//ʹ���Զ��ط�����
    CAN_InitStruct.CAN_RFLM = DISABLE;													//����FIFO�������������һ������ǰһ��
    CAN_InitStruct.CAN_TXFP = ENABLE;														//ʹ�ܷ���FIFO�����ȼ�
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;								//����CAN���߹���������ģʽ
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
    CAN_InitStruct.CAN_Prescaler =3;   																//CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN2, &CAN_InitStruct);
		/*************************************��ʼ����������************************************/
		//CAN2�Ĺ��������14-27
		CAN_InitFilter.CAN_FilterNumber = 14;													//ѡ���������14
		CAN_InitFilter.CAN_FilterMode = CAN_FilterMode_IdMask;				//���ñ�ʶ���б�ģʽ
		CAN_InitFilter.CAN_FilterScale = CAN_FilterScale_32bit;				//���ù�������14��λ��Ϊ32
		CAN_InitFilter.CAN_FilterIdHigh = 0x0000;											//�������й��˱�ʶ��ID��������
		CAN_InitFilter.CAN_FilterIdLow = 0x0000;										
		CAN_InitFilter.CAN_FilterMaskIdHigh = 0x0000;									//�������е�ID��Ϊ���ù��ģ�����������
		CAN_InitFilter.CAN_FilterMaskIdLow = 0x0000;									
		CAN_InitFilter.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;									//���ù���������һ��FIFO1
		CAN_InitFilter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_InitFilter);															//�˲�����ʼ��
 		/***************************************ʹ��CAN�ж�*************************************/   
    CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,DISABLE);
}
/*************************************************************************
�������ƣ�CAN2_TX_IRQHandler
�������ܣ�CAN2�ķ����жϺ���
*************************************************************************/
void CAN2_TX_IRQHandler(void)
{	
   if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
	 {
		 	CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
	 }
}

/*************************************************************************
�������ƣ�CAN2_RX1_IRQHandler
�������ܣ�CAN2�Ľ����жϺ���
*************************************************************************/
void CAN2_RX1_IRQHandler(void)
{
    CanRxMsg rx_message;
    if(CAN_GetITStatus(CAN2,CAN_IT_FMP1)!= RESET)
		{			  
				CAN_ClearITPendingBit(CAN2, CAN_IT_FMP1);
        CAN_Receive(CAN2, CAN_FIFO1, &rx_message);
      //  CanReceiveIO(&rx_message);		
		}
}

