#include "init.h"
#include "PID_Control_ZS.h"

PID_Param_Struct CMPID_Speed;
PID_Param_Struct CMPID_Follow;
PID_Param_Struct CMPID_Dance;
PID_Param_Struct CMPID_GYRO;
PID_Param_Struct CMPID_Currenr;


PID_Param_Struct PokePID_Speed;
PID_Param_Struct PokePID_Position;

PID_Param_Struct GMPPID_Speed;
PID_Param_Struct GMYPID_Speed;
PID_Param_Struct GMPPID_Position;
PID_Param_Struct GMYPID_Position;

/***********pid系数确定***********************/
void PID_Factor_Init_ZS(void)
{
//底盘参数设定	
  PID_Factor_Sure(&CMPID_Speed,30.0f,0,0);//速度PID  
  PID_Factor_Sure(&CMPID_Follow,12.5f,0,0);//旋转PID
  PID_Factor_Sure(&CMPID_Dance,12.5f,0,0);//旋转PID
 PID_Factor_Sure(&CMPID_GYRO,2.0f,0,2.0f);//旋转PID
 PID_Factor_Sure(&CMPID_Currenr,12.0f,0,0);//旋转PID   30

//云台炮口参数设定		
  PID_Factor_Sure(&PokePID_Speed,31.75f,0.8,0);//速度PID
  PID_Factor_Sure(&PokePID_Position,0.6f,0.0,30);//位置PID
//云台P轴参数设定		
  PID_Factor_Sure(&GMPPID_Position,15.0f,0.0,0);//位置PID
	PID_Factor_Sure(&GMPPID_Speed,10.0f,0.0,0.0);//速度PID
//云台Y轴参数设定		

  PID_Factor_Sure(&GMYPID_Position,15.0f,0.0,0.0);//位置PID
  PID_Factor_Sure(&GMYPID_Speed,10.0f,0.0,0.0);//速度PID

//------------------------------------------	
	//猫步
	ChassisSpeedParm.dance_angle=70;
	ChassisSpeedParm.dance_time=100;
	//高低速
	ChassisSpeedParm.high=600;
	ChassisSpeedParm.low=200;
	ChassisSpeedParm.normal=400;	
}

/***********位置pid***********************/
void PID_Control_Position(PID* motor_type)
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
	//
}
/*********************增量式PID******************************/

void PID_Control_Incrementing(PID* motor_type)
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


void PID_Reset(PID* motor_type)
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

void PID_Set(PID* motor_type,	float Kp,	float Ki,	float Kd)
{
	motor_type->Kp = Kp;
	motor_type->Ki = Ki;
	motor_type->Kd = Kd;
}

void PID_Factor_Sure(PID_Param_Struct* motor_type,	float Kp,	float Ki,	float Kd)
{
	motor_type->P = Kp;
	motor_type->I = Ki;
	motor_type->D = Kd;
}

