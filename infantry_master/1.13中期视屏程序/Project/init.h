#ifndef _INIT_H__
#define _INIT_H__

//系统函数
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "misc.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"

//zs------------------------------------------------------------------------------------
//遥控
#include "RemoteTask.h"

//USART
#include "USART_ZS.h"
#include "USART_Wave_ShanWAI.h"
#include "UART_Send_ZS.h"
#include "UART_Data_ZS.h"
#include "UsartRevicer.h"
#include "usart_pc.h"
//CAN
#include "Can_Task.h"
#include "Can1_Init.h"
#include "Can2_Init.h"
#include "CanBus.h"

//中断
#include "NVIC_ZS.h"

//线程
#include "Thread_ZS.h"

//IO
#include "GPIO_ZS.h"
#include "Init_All.h"

//数学控制
#include "PID_Control_ZS.h"
#include "Ramp_Control_ZS.h"

/*-------控制------*/
#include "Control_Task.h"
//底盘 控制
#include "Chassis_Control.h"
//云台   控制
#include "GM_Control_ZS.h"
#include "Poke_Control_ZS.h"//炮口控制
#include "PY_Control_ZS.h"//PY控制
#include "friction_servo_control.h"
//编码器
#include "Encoder_ZS.h"

//定时器 PWM
#include "PWM_Init_ZS.h"

//mpu9250
#include "MPU6050_i2c.h"
#include "mpu9250.h"
#include "MPU9250_Read_ZS.h"

//#include "IIC_Config_ZS.h"
//#include "MPU9250_Interrupt_ZS.h"
//#include "MPU9250_Config_ZS.h"
//mpu9250_DMP
#include "inv_mpu.h"
#include "fusion_9axis.h"

//延时
#include "delay.h"








void Init(void);




extern osSemaphoreId_t GRYO_Semaphore;
extern osSemaphoreId_t Calibrate_Semaphore; //校准任务

extern osMessageQueueId_t CanSend_MessageQueue;



#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\




#endif


