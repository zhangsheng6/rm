#ifndef _INIT_H__
#define _INIT_H__

//ϵͳ����
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "misc.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"

//zs------------------------------------------------------------------------------------
//ң��
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

//�ж�
#include "NVIC_ZS.h"

//�߳�
#include "Thread_ZS.h"

//IO
#include "GPIO_ZS.h"
#include "Init_All.h"

//��ѧ����
#include "PID_Control_ZS.h"
#include "Ramp_Control_ZS.h"

/*-------����------*/
#include "Control_Task.h"
//���� ����
#include "Chassis_Control.h"
//��̨   ����
#include "GM_Control_ZS.h"
#include "Poke_Control_ZS.h"//�ڿڿ���
#include "PY_Control_ZS.h"//PY����
#include "friction_servo_control.h"
//������
#include "Encoder_ZS.h"

//��ʱ�� PWM
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

//��ʱ
#include "delay.h"








void Init(void);




extern osSemaphoreId_t GRYO_Semaphore;
extern osSemaphoreId_t Calibrate_Semaphore; //У׼����

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


