#ifndef _GPIO_ZS_H_
#define _GPIO_ZS_H_

#include "init.h"
#include "stm32f4xx.h"                  // Device header

#define 	LED2_OFF 			GPIO_SetBits(GPIOB,GPIO_Pin_15);
#define 	LED2_ON 				GPIO_ResetBits(GPIOB,GPIO_Pin_15);
#define 	LED1_OFF 				GPIO_SetBits(GPIOB,GPIO_Pin_14);
#define 	LED1_ON 					GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define 	LED1_TOGGLE 			GPIO_ToggleBits(GPIOB,GPIO_Pin_14);
#define 	LED2_TOGGLE 		GPIO_ToggleBits(GPIOB,GPIO_Pin_15);
#define   LASER_ON()      GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define   LASER_OFF()     GPIO_ResetBits(GPIOC, GPIO_Pin_15)
void GPIO_Configuration(void) ;

//#define 	DianChi_ON			GPIO_SetBits(GPIOC,GPIO_Pin_10);
//#define 	DianChi_OFF		GPIO_ResetBits(GPIOC,GPIO_Pin_10);

//#define   DianRong_ON      GPIO_SetBits(GPIOC,GPIO_Pin_11);
//#define		DianRong_OFF			GPIO_ResetBits(GPIOC,GPIO_Pin_11);



#endif

