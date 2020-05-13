#ifndef __pid_h__
#define __pid_h__

#include "init.h"

#define Inter_Max   2000
#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\


typedef struct PID_PARAMETER
{
	float ref; //设定值
	float fdb; //实际值
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
}PID_Param_Struct;

typedef struct PID_Factor_t
{
	float P;
	float I;
	float D;
}PID_Factor_Struct;

void PID_Set(PID_Param_Struct* motor_type,	float Kp,	float Ki,	float Kd);
int16_t PID_Control_Position(PID_Param_Struct* motor_type); 
void PID_Param_Reset(PID_Param_Struct* motor_type);
void PID_Control_Incrementing(PID_Param_Struct* motor_type);

void PID_Factor_Init(void);
void PID_Factor_Sure(PID_Param_Struct* motor_type,	float Kp,	float Ki,	float Kd);

extern PID_Param_Struct PID_1;

//extern PID ChassisCurrentPID;
 
//extern PID_Param_Struct CMPID_Speed;

#endif
