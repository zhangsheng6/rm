#ifndef __LED_H__
#define __LED_H__

#define 				GREEN_OFF 			GPIO_SetBits(GPIOC,GPIO_Pin_1);
#define 				GREEN_ON 				GPIO_ResetBits(GPIOC,GPIO_Pin_1);
#define 				RED_OFF 				GPIO_SetBits(GPIOC,GPIO_Pin_2);
#define 				RED_ON 					GPIO_ResetBits(GPIOC,GPIO_Pin_2);
#define 				RED_TOGGLE 			GPIO_ToggleBits(GPIOC,GPIO_Pin_2);
#define 				GREEN_TOGGLE 		GPIO_ToggleBits(GPIOC,GPIO_Pin_2);
void LED_Init(void);

#endif 
