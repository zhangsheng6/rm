#ifndef __PID_CONTROL_ZS_H__
#define __PID_CONTROL_ZS_H__

#include <stm32f4xx.h>
#include "PID_Control_ZS.h"
#include "init.h"

#define Inter_Max   2000

typedef struct PID_PARAMETER
{
	float ref;
	float fdb;
	float Kp;
	float Ki;
	float Kd;
	float error_now;
	float error_last;
	float error_inter;
	float error_prev;
	float pid_out;
	float proportion;        //占输出总比
	float final_out;				 //最终输出到电机的设定值
 s8 out_sign;					 //输入时的正负标志
}PID;

typedef struct PID_Factor_t
{
	float P;
	float I;
	float D;
}PID_Param_Struct;

void PID_Set(PID* motor_type,	float Kp,	float Ki,	float Kd);
void PID_Control_Position(PID* motor_type); 
void PID_Reset(PID* motor_type);
void PID_Control_Incrementing(PID* motor_type);

void PID_Factor_Init_ZS(void);
void PID_Factor_Sure(PID_Param_Struct* motor_type,	float Kp,	float Ki,	float Kd);

extern PID ChassisCurrentPID;
 
extern PID_Param_Struct CMPID_Speed;
extern PID_Param_Struct CMPID_Follow;
extern PID_Param_Struct CMPID_Dance;
extern PID_Param_Struct CMPID_GYRO;
extern PID_Param_Struct CMPID_Currenr;

extern PID_Param_Struct PokePID_Speed;
extern PID_Param_Struct PokePID_Position;

extern PID_Param_Struct GMPPID_Speed;
extern PID_Param_Struct GMYPID_Speed;
extern PID_Param_Struct GMPPID_Position;
extern PID_Param_Struct GMYPID_Position;

#endif


