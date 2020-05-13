#include "usart.h"

//#if EN_USART1_RX   //如果使能了接收
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

/*
波特率计算公式：
IntegerDivider = ((APBClock) / (16 * (USART_InitStruct->USART_BaudRate)))
FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5
本来是A2A3,但那是USART2的
F103ZET6 第二功能
A2A3 :USART2 TX,RX
A9A10:USART1 TX,RX
*/
void Usart1_Init(u32 bound)
	{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

	USART_DeInit(USART1); //复位串口 1

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //一帧的传输 数据位数：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一帧的结尾传输 停止位数：1位。0.5，1.5，2
	USART_InitStructure.USART_Parity = USART_Parity_No;//奇偶性：无奇偶校验。一旦失能，数据位最后一位为奇偶位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制模式：失能
	USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;	

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //接收中断
  USART_Cmd(USART1, ENABLE); 

}


/*
串口1接受中断函数：仅接收颜色数据：红/蓝
*/
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	  u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;//此时只能是USART_RX_BUF[0]=res
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
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


