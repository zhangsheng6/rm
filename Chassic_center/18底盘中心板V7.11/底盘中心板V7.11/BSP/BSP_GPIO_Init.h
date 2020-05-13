#ifndef _BSP_GPIO_INIT_H_
#define _BSP_GPIO_INIT_H_


#include "stm32f10x.h"                  // Device header


#define LED0_ON   GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define LED0_OFF  GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define LED1_ON     GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define LED1_OFF    GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define LED2_ON     GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define LED2_OFF    GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LED3_ON   GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define LED3_OFF  GPIO_ResetBits(GPIOB,GPIO_Pin_1)


void BSP_GPIO_Init(void);
void LED0_Runsign(unsigned times);
void LED1_Runsign(unsigned times);
void LED2_Runsign(unsigned times);
void LED3_Runsign(unsigned times);

#endif

