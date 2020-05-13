#ifndef _CANBUS_H_
#define _CANBUS_H_

#include "init.h"
#include "stm32f4xx_can.h"

/* CAN Bus 2 */  
#define CAN_BUS2_MOTOR1_FEEDBACK_MSG_ID           0x201
#define CAN_BUS2_MOTOR2_FEEDBACK_MSG_ID           0x202 
#define CAN_BUS2_MOTOR3_FEEDBACK_MSG_ID           0x203
#define CAN_BUS2_MOTOR4_FEEDBACK_MSG_ID           0x204
#define CAN_BUS2_MOTOR5_FEEDBACK_MSG_ID           0x205
#define CAN_BUS2_MOTOR6_FEEDBACK_MSG_ID           0x206
#define CAN_BUS2_MOTOR7_FEEDBACK_MSG_ID           0x207//�ڿ�C610��� ID
#define CAN_BUS2_CURRENT_FEEDBACK_MSG_ID          0x300//ina260
#define CAN_BUS2_Judge_FEEDBACK_MSG_ID            0x301//����ϵͳ��
#define CAN_BUS1_ZGYRO_FEEDBACK_MSG_ID   		  		0x302//���̵�6050
#define CAN_BUS2_Control_FEEDBACK_MSG_ID   		  	0x303

#define RATE_BUF_SIZE 6

typedef struct 
{
   float Voltage; //*1000
	 float Current;
	 float Power;
	 int16_t CompareState;
	 
	 float Gyro_Z;
	 float Accel;
	 float roll_angle;
}ChassisCenter_t;//�������İ����� �ṹ��

typedef struct
{
   float Voltage;  //��ص�ѹ *1000
	 float Power;    //����
	 float Current;  //����
	 float PowerBuffer;//��������
	 u16 Heat0;    //17mmǹ������
	 u16 Heat1;    //41mmǹ������
	 u8 Level;     //�ȼ�
}JudgeMent;  //����ϵͳ���� �ṹ��



void CanReceiveMsgProcess(CanRxMsg * msg);
void Set_Motor_Speed(CAN_TypeDef *CANx, int16_t Motor1_Pwm, int16_t Motor2_Pwm, int16_t Motor3_Pwm, int16_t Motor4_Pwm);
void Set_Holder_Position(CAN_TypeDef *CANx, int16_t yaw, int16_t pitch,int16_t Poke);

#endif
