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
#define CAN_BUS2_MOTOR7_FEEDBACK_MSG_ID           0x207//炮口C610电调 ID
#define CAN_BUS2_CURRENT_FEEDBACK_MSG_ID          0x300//ina260
#define CAN_BUS2_Judge_FEEDBACK_MSG_ID            0x301//裁判系统你
#define CAN_BUS1_ZGYRO_FEEDBACK_MSG_ID   		  		0x302//底盘的6050
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
}ChassisCenter_t;//底盘中心板数据 结构体

typedef struct
{
   float Voltage;  //电池电压 *1000
	 float Power;    //功率
	 float Current;  //电流
	 float PowerBuffer;//缓冲能量
	 u16 Heat0;    //17mm枪口热量
	 u16 Heat1;    //41mm枪口热量
	 u8 Level;     //等级
}JudgeMent;  //裁判系统数据 结构体



void CanReceiveMsgProcess(CanRxMsg * msg);
void Set_Motor_Speed(CAN_TypeDef *CANx, int16_t Motor1_Pwm, int16_t Motor2_Pwm, int16_t Motor3_Pwm, int16_t Motor4_Pwm);
void Set_Holder_Position(CAN_TypeDef *CANx, int16_t yaw, int16_t pitch,int16_t Poke);

#endif
