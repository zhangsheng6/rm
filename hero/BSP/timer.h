#ifndef __TIMER_H__
#define __TIMER_H__
#include "main.h"

void TIM2_Configuration(void);
void TIM6_Start(void);
void TIM6_Configuration(void);
uint32_t Get_Time_Micros(void);

#endif
