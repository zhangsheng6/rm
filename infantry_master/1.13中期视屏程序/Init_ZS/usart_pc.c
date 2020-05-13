#include "usart_pc.h"

u8  PC_Buffer[2][11];
float x=0.0f , y=0.0f;
double hight = 0;
float Pitch_Change = 0.0f,Yaw_Change = 0.0f;
uint8_t Pitch_Flag,Yaw_Flag;
#define header_1 0xff
#define header_2 0xfe
#define tail_1 0xee
u32 USART6_RX_STA=0;

uint8_t Fire_Flag = 0;            //开火标志位
uint16_t ShootPrepare_Time = 0;						//射击时间

USART6_Recive USART6_Memory;

/*
	 USART6_TX->PC6		USART6_RX->PC7
// function: USB转串口初始端口
*/
void Usart6_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;
		DMA_InitTypeDef DMA_InitStructure;

		USART_StructInit(&USART_InitStructure);
		USART_ClockStructInit(&USART_ClockInitStruct);
	
    //开启USART6时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC ,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为 8 位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx; //收模式
    USART_Init(USART6, &USART_InitStructure); //初始化串口

    USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //时钟低电平活动
    USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK引脚上时钟输出的极性->低电平
    USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //时钟第二个边沿进行数据捕获
    USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出
    USART_ClockInit(USART6, &USART_ClockInitStruct);
		
		USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
		 
    DMA_DeInit(DMA2_Stream1);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_Channel = DMA_Channel_5;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART6->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&PC_Buffer[0];
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 20;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream1, &DMA_InitStructure);
		
		DMA_DoubleBufferModeConfig(DMA2_Stream1, (uint32_t)&PC_Buffer[0], DMA_Memory_0);   //first used memory configuration
    DMA_DoubleBufferModeCmd(DMA2_Stream1, ENABLE);
    
    DMA_Cmd(DMA2_Stream1, ENABLE);
    
		USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);        //usart IDLE line interrupt  enabled
    USART_Cmd(USART6, ENABLE);
}





void USART6_IRQHandler(void)
{
	static uint32_t this_time_rx_len = 0;
	
	static Angle Yaw_Angle,Pitch_Angle;
	
	if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
		
		//clear the idle pending flag 
		(void)USART6->SR;
		(void)USART6->DR;

		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream1) == 0)
		{
			DMA_Cmd(DMA2_Stream1, DISABLE);
			this_time_rx_len = 20 - DMA_GetCurrDataCounter(DMA2_Stream1);
			DMA2_Stream1->NDTR = (uint16_t)20;     //relocate the dma memory pointer to the beginning position
			DMA2_Stream1->CR |= (uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 1
			DMA_Cmd(DMA2_Stream1, ENABLE);
      if(this_time_rx_len == 11)
			{
			  USART6_Memory=MeMory1; 
				if(PC_Buffer[USART6_Memory][0]==header_1 && PC_Buffer[USART6_Memory][1]==header_2 && PC_Buffer[USART6_Memory][10]==tail_1)
				{							
					Yaw_Angle.d[0] = PC_Buffer[USART6_Memory][2];
					Yaw_Angle.d[1] = PC_Buffer[USART6_Memory][3];
					Yaw_Angle.d[2] = PC_Buffer[USART6_Memory][4];
					Yaw_Angle.d[3] = PC_Buffer[USART6_Memory][5];
					
					Pitch_Angle.d[0] = PC_Buffer[USART6_Memory][6];
					Pitch_Angle.d[1] = PC_Buffer[USART6_Memory][7];
					Pitch_Angle.d[2] = PC_Buffer[USART6_Memory][8];
					Pitch_Angle.d[3] = PC_Buffer[USART6_Memory][9];
					
					Yaw_Change = Yaw_Angle.D;
					Pitch_Change = Pitch_Angle.D;	
					
					VAL_LIMIT(Yaw_Change,-10,10);
					VAL_LIMIT(Pitch_Change,-7,7);		

					PC_Buffer[USART6_Memory][0] = 0x66;					
				}
			}
		}
		//Target is Memory1
		else
			{
				DMA_Cmd(DMA2_Stream1, DISABLE);
				this_time_rx_len = 20 - DMA_GetCurrDataCounter(DMA2_Stream1);
				DMA2_Stream1->NDTR = (uint16_t)20;      //relocate the dma memory pointer to the beginning position
				DMA2_Stream1->CR  &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
				DMA_Cmd(DMA2_Stream1, ENABLE);
				if(this_time_rx_len == 11)
				{
					USART6_Memory=MeMory2;
					if(PC_Buffer[USART6_Memory][0]==header_1 && PC_Buffer[USART6_Memory][1]==header_2 && PC_Buffer[USART6_Memory][10]==tail_1)
					{
						Yaw_Angle.d[0] = PC_Buffer[USART6_Memory][2];
						Yaw_Angle.d[1] = PC_Buffer[USART6_Memory][3];
						Yaw_Angle.d[2] = PC_Buffer[USART6_Memory][4];
						Yaw_Angle.d[3] = PC_Buffer[USART6_Memory][5];
						
						Pitch_Angle.d[0] = PC_Buffer[USART6_Memory][6];
						Pitch_Angle.d[1] = PC_Buffer[USART6_Memory][7];
						Pitch_Angle.d[2] = PC_Buffer[USART6_Memory][8];
						Pitch_Angle.d[3] = PC_Buffer[USART6_Memory][9];
						
						Yaw_Change = Yaw_Angle.D*0.5f;
						Pitch_Change = Pitch_Angle.D*0.5f;
						
						VAL_LIMIT(Yaw_Change,-10,10);
						VAL_LIMIT(Pitch_Change,-7,7);	

						PC_Buffer[USART6_Memory][0] = 0x66;
					}
			 }
		}
 	}
}




