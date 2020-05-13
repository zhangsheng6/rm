#include "can.h"
#include "energy_authorities_task.h"

CanRxMsg rx1_message;

/*
Can1�����ж� 
A11can����
A12can����
*/
void Can1_Init(void)
{
GPIO_InitTypeDef       GPIO_InitStructure;
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	CAN_InitStructure.CAN_TTCM=DISABLE;					//ʱ�䴥��ͨ��ģʽ:ʧ��  
	CAN_InitStructure.CAN_ABOM=DISABLE;					//����Զ����߹���ʧ��
	CAN_InitStructure.CAN_AWUM=DISABLE;			    //�Զ�����ģʽ��ʧ�ܡ�  ˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART=DISABLE;					//���Զ��ش���ģʽ��ʧ�ܡ�     �Ƿ��ֹ�����Զ����� 
	CAN_InitStructure.CAN_RFLM=ENABLE;					//����FIFO����ģʽ��ʹ�ܡ�      ���Ĳ�����,�µĸ��Ǿɵ� 
	CAN_InitStructure.CAN_TXFP=ENABLE;					//����FIFO���ȼ���ʹ�ܡ�         �ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;	//CANӲ������ģʽ�� mode:��ͨģʽ����Ĭģʽ������ģʽ��Ĭ����ģʽ
	//���ò�����
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //����ͬ����Ծ���(Tsjw)��Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_6tq; //ʱ���1��ʱ�䵥λ��Ŀ��Tbs1=tbs1+1��ʱ�䵥λ CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_5tq; //ʱ���2��ʱ�䵥λ��Ŀ��Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=3;     //1��ʱ�䵥λ�ĳ��ȣ�1-1024    ��Ƶϵ��(Fdiv)Ϊbrp+1	//
	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 

	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //����ʼ���Ĺ�������0-13
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //��������ʼ��ģʽ����ʶ������λģʽ��  ��ʶ���б�ģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //������λ��1��32λ    ��  2��16λ
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;//��������ʶ���趨��16λʱΪ��1��
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;//             ��������
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//��������ʶ��/���������α�ʶ���趨��32λMASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //��������ʹ��
	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��

	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//����0�жϣ���FIFO0��Ϣ�Һ��ж�����
//CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);//����0�ж�
		

	}	


	
//can1�����жϳ��򣺽������λ���屻������Ϣ
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {		
			CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
      CAN_Receive(CAN1, CAN_FIFO0, &rx1_message);
      Can_Hook(&rx1_message);
			
    }		  
}

//CAN�ҹ�
void Can_Hook(CanRxMsg *rx_message)
{
    switch (rx_message->StdId)
    { 
			case CAN_flabellum0_ID:  //���λ����ID
			{
			flabellum[0].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum1_ID:
							{
			flabellum[1].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum2_ID:
							{
			flabellum[2].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum3_ID:
							{
			flabellum[3].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum4_ID:
							{
			flabellum[4].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
//					{
//						 static uint8_t num = 0;
//						 num = rx_message->StdId - CAN_flabellum0_ID; 
//						 flabellum[num].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������

//					}break;
			case CAN_MASTER_ID:
					{
						 uint8_t num1 = 0;
						running_mode = ((rx_message)->Data[0]&0x0F);
						for(;num1<5;num1++)
						{	 
						 flabellum[num1].ready =  ((rx_message)->Data[num1]&0x10)>>4;//5������װ�װ��׼��״̬ready
						}
					}

    }
		
}



























