#include "GPIO_ZS.h"


void GPIO_Configuration(void)
{
/*
	俩LED灯-----PB14,PB15
	电池--------PC10
	电容--------PC11
	激光--------PC15
	俩外部中断--PA8,PB10
*/	
		GPIO_InitTypeDef GPIO_InitStruct;
   //	EXTI_InitTypeDef    exti;
		/*******************************************使能时钟**********************************************/  
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
  	//GPIO_InitStruct.GPIO_Pin =GPIO_Pin_10|GPIO_Pin_11| GPIO_Pin_15;               //激光+电池+电容
  	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_15;               //激光
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);


		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15 ;//LED
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
//		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;  //外部中断，线8
//		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
//		GPIO_Init(GPIOA, &GPIO_InitStruct);

//		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 ; //外部中断，线10
//		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
//		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,GPIO_PinSource8); 
//	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,GPIO_PinSource10); 
//    exti.EXTI_Line = EXTI_Line8|EXTI_Line10;
//    exti.EXTI_Mode = EXTI_Mode_Interrupt;
//    exti.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿中断
//    exti.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&exti);
		
		
		/*******************************************关闭LED灯**********************************************/
		LED1_OFF
		LED2_OFF
	  	
}

