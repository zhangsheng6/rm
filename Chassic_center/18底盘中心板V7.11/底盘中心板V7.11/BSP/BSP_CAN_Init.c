#include "BSP_CAN_Init.h"

#include "init.h"
CanRxMsg RXMsg;  
CanTxMsg TXMsg; //can ��������

void BSP_Can_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	CAN_InitTypeDef CAN_InitStruct;
	CAN_FilterInitTypeDef	CAN_FilterInitStruct;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;//RX
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;//����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;//TX
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//���츴��
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/*CAN_InitStructure�Ĵ�����ʼ��*/
	CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStruct);
	
	/*CAN_InitStructure��Ԫ��ʼ��*/
	CAN_InitStruct.CAN_TTCM=DISABLE;//��ʱ�䴥��ͨ��ģʽ
	CAN_InitStruct.CAN_TXFP=ENABLE;//���ȼ��ɱ��ı�ʶ������
	CAN_InitStruct.CAN_RFLM=ENABLE;//�����������µĲ����Ǿɵ�
	CAN_InitStruct.CAN_AWUM=DISABLE;//˯��ģʽͨ���������
	CAN_InitStruct.CAN_ABOM=DISABLE;//����Զ����߹���
	CAN_InitStruct.CAN_NART=DISABLE;//��ֹ�����Զ�����
	CAN_InitStruct.CAN_Mode=CAN_Mode_Normal;//����ģʽ
	CAN_InitStruct.CAN_SJW=CAN_SJW_1tq;//
	CAN_InitStruct.CAN_BS1=CAN_BS1_6tq;//
	CAN_InitStruct.CAN_BS2=CAN_BS2_5tq;//
	CAN_InitStruct.CAN_Prescaler=3;//CAN BaudRate 36/(1+BS1+BS2)/3=1Mbps
	CAN_Init(CAN1,&CAN_InitStruct);
	
	/*************************************��ʼ����������************************************/
	//CAN1�Ĺ��������0-13
	CAN_FilterInitStruct.CAN_FilterNumber = 0;													//ѡ���������0
	CAN_FilterInitStruct.CAN_FilterMode = CAN_FilterMode_IdMask;				//���ñ�ʶ���б�ģʽ
	CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;				//���ù�������0��λ��Ϊ32
	CAN_FilterInitStruct.CAN_FilterIdHigh = 0x0000;											//�������й��˱�ʶ��ID��������
	CAN_FilterInitStruct.CAN_FilterIdLow = 0x0000;										
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0000;									//�������е�ID��Ϊ���ù��ģ�����������
	CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0000;									
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;									//���ù���������һ��FIFO0
	CAN_FilterInitStruct.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStruct);															//�˲�����ʼ��

	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//����0�ж�
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);	//�����ж�
}
/*************************************************************************
������CAN1�Ľ����жϺ���
*************************************************************************/

void USB_LP_CAN1_RX0_IRQHandler(void)
{
		if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
		{  		 
			 CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
       CAN_Receive(CAN1,CAN_FIFO0,&RXMsg);    //CAN��������
			 CAN_Revicer(&RXMsg);
		}
}
void USB_HP_CAN1_TX_IRQHandler(void)
{
		if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
		{
			Real_Monitor.CAN_Send_FrameCounter++;
			LED2_Runsign(30);
			CAN_ClearITPendingBit(CAN1, CAN_IT_TME);
		}
}

