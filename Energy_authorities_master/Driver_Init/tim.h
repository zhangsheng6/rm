#ifndef _tim_h_
#define _tim_h_

#include"init.h"

void Tim2_Init(u16 arr,u16 psc);
void Tim3_Init(u16 arr,u16 psc);
//void Tim4_Init(u16 arr,u16 psc);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
//void TIM4_IRQHandler(void);

#endif

