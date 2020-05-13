#ifndef _CHASSIS_CONTROL_H_
#define _CHASSIS_CONTROL_H_
#include "PID_Control_ZS.h"
#include "init.h"
#define CHASSIS_SPEED_ATTENUATION   1.0f

typedef __packed struct 
{
	uint8_t forward_back_SPEED; //�����ٶ�
	uint8_t left_right_SPEED;
	uint8_t rotate_SPEED;
	
	uint16_t dance_angle;//��ת�Ƕ�
	uint16_t dance_speed;//��ת�ٶ�
	uint16_t dance_time;//��תʱ��
	
	uint16_t normal;
	uint16_t high;
	uint16_t low;
}SPEED;   

typedef enum
{
  Chassis_NORAML=0,
	Chassis_DANCE,//è������
	Chassis_CRUISE, //Ѳ��ģʽ
	Chassis_ATTACK,//����ģʽ
}ChassisState;   //��������ģʽ 

extern ChassisState chassisstate ; 			

extern PID CM1SpeedPID;				 //���̵���ٶȻ�PID
extern PID CM2SpeedPID;
extern PID CM3SpeedPID;
extern PID CM4SpeedPID;

extern RampGenLoop_t CMDanceRamp;//è��б��

extern SPEED ChassisSpeedParm;     //���̲�������                  

extern ChassisState chassisstate ;//��ʼ״̬Ϊ����

void CMControlLoop(void);
void ControtLoopTaskInit(void);

#endif
