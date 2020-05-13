#include "Init_All.h"

void Init_Function(void)
{
	
  GPIO_Configuration();
	delay_ms(800); //�ϵ����ʹ��MPU6050����
		PID_Factor_Init_ZS();
  ControtLoopTaskInit();//���������ʼ�� 

	CAN1_Configuration();///can��ʼ��
	
	 PWM_Out_Init_TIM2(50);  //Ħ���ֵ�� 50HZ��PWM1000
   PWM_Out_Init_TIM3(50);  //Ħ���ֵ�� 50HZ
	 PWM_Out_Init_TIM4(50);  //���

	USART1_Configuration(100000);//ң��DBUS����
  Device_Usart4_ENABLE_Init(115200);//���� �շ�
	
	 MPU_I2C_Configuration();
	 MPU9250_Init(); //MPU_DMP��ʼ��
	
//	MPU_I2C_Configuration();//IIC��ʼ��
//	MPU9250_Init(); //MPU9250��ʼ����9��+�¶�+DMP
	delay_ms(2500);	

	RemoteTaskInit();       //ң�س�ʼֵΪ0
	NvicInitType();

}

