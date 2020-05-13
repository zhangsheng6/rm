#include "usart.h"

//#if EN_USART1_RX   //���ʹ���˽���
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

/*
�����ʼ��㹫ʽ��
IntegerDivider = ((APBClock) / (16 * (USART_InitStruct->USART_BaudRate)))
FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5
������A2A3,������USART2��
F103ZET6 �ڶ�����
A2A3 :USART2 TX,RX
A9A10:USART1 TX,RX
*/
void Usart1_Init(u32 bound)
	{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

	USART_DeInit(USART1); //��λ���� 1

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //һ֡�Ĵ��� ����λ����8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ֡�Ľ�β���� ֹͣλ����1λ��0.5��1.5��2
	USART_InitStructure.USART_Parity = USART_Parity_No;//��ż�ԣ�����żУ�顣һ��ʧ�ܣ�����λ���һλΪ��żλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������ģʽ��ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;	

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�����ж�
  USART_Cmd(USART1, ENABLE); 

}


/*
����1�����жϺ�������������ɫ���ݣ���/��
*/
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	  u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;//��ʱֻ����USART_RX_BUF[0]=res
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
     }
		if(USART_RX_BUF[0])
		{
		 color = BLUE;
		}
		else
			color =		RED;
	}


