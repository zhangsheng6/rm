#ifndef __APP_H__
#define __APP_H__
#include <stm32f4xx.h>


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
	float pid_out;
}PID;
void PID_Set(PID* motor_type,	float Kp,	float Ki,	float Kd);
void PID_Control(PID* motor_type); 
void PID_Reset(PID* motor_type);
#endif
