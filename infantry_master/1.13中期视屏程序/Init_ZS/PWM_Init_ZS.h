#ifndef __BSP_PWMINIT_H__
#define __BSP_PWMINIT_H__

#ifndef FRICTION_WHEEL
#define FRICTION_WHEEL
#endif 

#if defined(FRICTION_WHEEL)

#define PWM1  TIM3->CCR4
#define PWM2  TIM2->CCR2
#define PWM3_1 TIM4->CCR3
#define PWM3_2 TIM4->CCR4

#define InitFrictionWheel()     \
        PWM1 = 500;             \
        PWM2 = 500;
#define SetFrictionWheelSpeed(x) \
        PWM1 = x;                \
        PWM2 = x;
#define SetServeWheelAngle(x) \
        PWM3_1=x;             \
				PWM3_2=x;
			
#endif 

//u8 PWM_Out_Init_TIM1(uint16_t hz);
u8 PWM_Out_Init_TIM2(uint16_t hz);
u8 PWM_Out_Init_TIM3(uint16_t hz);
u8 PWM_Out_Init_TIM4(uint16_t hz); 
#endif /* __GUN_H__*/





