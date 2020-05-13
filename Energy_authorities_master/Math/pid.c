#include "pid.h"

PID_Param_Struct PID_1;

//PID_Param_Struct CMPID_Speed;
//PID_Param_Struct PokePID_Speed;
//PID_Param_Struct PokePID_Position;


/***********pid系数确定***********************/
void PID_Factor_Init(void)
{
	  PID_Factor_Sure(&PID_1,60,0.2,0);

}

/***********位置pid***********************/
int16_t PID_Control_Position(PID_Param_Struct* motor_type)
{
//  float error_position;
	motor_type->error_last=motor_type->error_now;
	motor_type->error_now = motor_type->ref - motor_type->fdb;
	motor_type->error_inter += motor_type->error_now;
	// limit intergration of pid
	if(motor_type->error_inter>Inter_Max)
		  motor_type->error_inter = Inter_Max;
	if(motor_type->error_inter<-Inter_Max)
		  motor_type->error_inter = -Inter_Max;
	
	motor_type->pid_out = motor_type->Kp * motor_type->error_now + motor_type->Ki * motor_type->error_inter +	motor_type->Kd * (motor_type->error_now-motor_type->error_last);
	VAL_LIMIT(motor_type->pid_out, -32767, 32767);
	return (int16_t)motor_type->pid_out;

}
/*********************增量式PID******************************/

void PID_Control_Incrementing(PID_Param_Struct* motor_type)
{
	 
	 if(motor_type->ref<4&&motor_type->ref>-4)
	 {
	   motor_type->ref=0; 
	 }
    motor_type->error_now = motor_type->ref - motor_type->fdb;
 
    motor_type->pid_out = motor_type->pid_out + motor_type->Kp * motor_type->error_now               //E[k]
              - motor_type->Ki   * motor_type->error_last     //E[k-1]
              + motor_type->Kd * motor_type->error_prev;   //E[k-2]
  
		
    motor_type->error_prev = motor_type->error_last;
    motor_type->error_last = motor_type->error_now;
}


void PID_Param_Reset(PID_Param_Struct* motor_type)
{
	motor_type->ref = 0;
	motor_type->fdb = 0;
	motor_type->Kp = 0;
	motor_type->Ki = 0;
	motor_type->Kd = 0;
	motor_type->error_last = 0;
	motor_type->error_now = 0;
	motor_type->error_inter = 0;
	motor_type->error_prev=0;
	motor_type->pid_out = 0;
}



void PID_Factor_Sure(PID_Param_Struct* motor_type,	float Kp,	float Ki,	float Kd)
{
	motor_type->Kp = Kp;
	motor_type->Ki = Ki;
	motor_type->Kp = Kd;
}
