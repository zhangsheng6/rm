
#include "init.h"
#include "stm32f4xx.h"                  // Device header


/*
	UART4_TX->PC10		UART4_RX->PC11
  串口 收发 数据
*/
void Device_Usart4_ENABLE_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef UART_InitStructure;

	
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);
	
	  GPIO_StructInit(&GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	  USART_DeInit(UART4);
		USART_StructInit(&UART_InitStructure);

	  UART_InitStructure.USART_BaudRate = bound;//波特率
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据
    UART_InitStructure.USART_StopBits = USART_StopBits_1;   //在帧结尾传输1个停止位
    UART_InitStructure.USART_Parity = USART_Parity_No;    //禁用奇偶校验
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    UART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送、接收使能
    USART_Init(UART4, &UART_InitStructure);
	
    USART_Cmd(UART4, ENABLE);
}


/*?????????????????????????

///串口6初始化,PC机接口
void USART6_Configuration(void)
{
    USART_InitTypeDef usart6;
    GPIO_InitTypeDef  gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);

    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); 

    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//TX  RX
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC,&gpio);

    usart6.USART_BaudRate = 115200;          // speed 10byte/ms
    usart6.USART_WordLength = USART_WordLength_8b;
    usart6.USART_StopBits = USART_StopBits_1;
    usart6.USART_Parity = USART_Parity_No;
    usart6.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart6.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART6,&usart6);

  // USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART6,ENABLE);
}

void USART6_IRQHandler(void)
{  
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	
  }
}

*/

























