#ifndef _INIT_H_
#define _INIT_H_

#include "cmsis_os.h"
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"

#include "String.h"
#include "mydelay.h"
#include "judgement_info.h"
#include "protocol.h"

#include "BSP_GPIO_Init.h"
#include "BSP_SuperCapacitor_Init.h"
#include "BSP_USART_Init.h"
#include "BSP_CAN_Init.h"
#include "BSP_IIC_Init.h"
#include "INA260_Driver.h"
#include "mpu6050_interrupt.h"
#include "mpu6050.h"

#include "CAN_Task.h"
#include "Judge_Task.h"
#include "Monitor_Task.h"
#include "PowerSupply_Task.h"

void KernelTaskInit(void);
void NVIC_StateInit(void );

extern osSemaphoreId_t GRYO_Semaphore;


#endif




