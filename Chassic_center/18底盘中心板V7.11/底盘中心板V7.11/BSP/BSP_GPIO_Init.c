#include "BSP_GPIO_Init.h"


void BSP_GPIO_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	LED0_OFF;
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}

void LED0_Runsign(unsigned times)
{
	static uint16_t light=0;
	light++;
	if(light>=times)
	{
		LED0_ON;
		if(light==times*2)
		{
			LED0_OFF;
			light=0;
		}
	}
}

void LED1_Runsign(unsigned times)
{
	static uint16_t light=0;
	light++;
	if(light>=times)
	{
		LED1_ON;
		if(light==times*2)
		{
			LED1_OFF;
			light=0;
		}
	}
}

void LED2_Runsign(unsigned times)
{
	static uint16_t light=0;
	light++;
	if(light>=times)
	{
		LED2_ON;
		if(light==times*2)
		{
			LED2_OFF;
			light=0;
		}
	}
}

void LED3_Runsign(unsigned times)
{
	static uint16_t light=0;
	light++;
	if(light>=times)
	{
		LED3_ON;
		if(light==times*2)
		{
			LED3_OFF;
			light=0;
		}
	}
}
