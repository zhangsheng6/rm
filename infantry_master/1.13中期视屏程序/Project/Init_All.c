#include "Init_All.h"

void Init_Function(void)
{
	
  GPIO_Configuration();
	delay_ms(800); //上电过程使得MPU6050运行
		PID_Factor_Init_ZS();
  ControtLoopTaskInit();//控制任务初始化 

	CAN1_Configuration();///can初始化
	
	 PWM_Out_Init_TIM2(50);  //摩擦轮电机 50HZ，PWM1000
   PWM_Out_Init_TIM3(50);  //摩擦轮电机 50HZ
	 PWM_Out_Init_TIM4(50);  //舵机

	USART1_Configuration(100000);//遥控DBUS接收
  Device_Usart4_ENABLE_Init(115200);//串口 收发
	
	 MPU_I2C_Configuration();
	 MPU9250_Init(); //MPU_DMP初始化
	
//	MPU_I2C_Configuration();//IIC初始化
//	MPU9250_Init(); //MPU9250初始化：9轴+温度+DMP
	delay_ms(2500);	

	RemoteTaskInit();       //遥控初始值为0
	NvicInitType();

}

