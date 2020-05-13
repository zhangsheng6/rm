#ifndef _CHASSIS_CONTROL_H_
#define _CHASSIS_CONTROL_H_
#include "PID_Control_ZS.h"
#include "init.h"
#define CHASSIS_SPEED_ATTENUATION   1.0f

typedef __packed struct 
{
	uint8_t forward_back_SPEED; //底盘速度
	uint8_t left_right_SPEED;
	uint8_t rotate_SPEED;
	
	uint16_t dance_angle;//旋转角度
	uint16_t dance_speed;//旋转速度
	uint16_t dance_time;//旋转时间
	
	uint16_t normal;
	uint16_t high;
	uint16_t low;
}SPEED;   

typedef enum
{
  Chassis_NORAML=0,
	Chassis_DANCE,//猫步运行
	Chassis_CRUISE, //巡航模式
	Chassis_ATTACK,//攻击模式
}ChassisState;   //底盘运行模式 

extern ChassisState chassisstate ; 			

extern PID CM1SpeedPID;				 //底盘电机速度环PID
extern PID CM2SpeedPID;
extern PID CM3SpeedPID;
extern PID CM4SpeedPID;

extern RampGenLoop_t CMDanceRamp;//猫步斜坡

extern SPEED ChassisSpeedParm;     //底盘参数设置                  

extern ChassisState chassisstate ;//初始状态为正常

void CMControlLoop(void);
void ControtLoopTaskInit(void);

#endif
