#include "init.h"
#include "stm32f4xx_exti.h"
uint8_t isMPU6050_is_DRY = 0;   // mpu6050 interrupt中断标志

//中断设置引脚 
#define I2C_Pin_IT  GPIO_Pin_4
#define IT_line   EXTI_Line4
#define GPIO_PinSource   GPIO_PinSource4


void MPU6050_IntConfiguration(void)
{
		GPIO_InitTypeDef    gpio;
    EXTI_InitTypeDef    exti;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE);   
		gpio.GPIO_Pin = I2C_Pin_IT ;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,GPIO_PinSource); 
    exti.EXTI_Line = IT_line;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿中断
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
}

//外部中断 12
uint8_t shoot_flag;
void EXTI4_IRQHandler(void)         //中断频率1KHz
{   
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line4);          
        EXTI_ClearITPendingBit(EXTI_Line4);
			  Real_Monitor.IMUFrameCounter++;
        osSemaphoreRelease(GRYO_Semaphore);	
    }

}

