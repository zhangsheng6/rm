#include "Control_Task.h"
#include "Thread_ZS.h"

char WorkState_Flag = 0;   //开机即准备
int  time_tick_ms = 0;
u8 Error_Flag=0;

//----------------------------------------------
void Control_Task(void)
{
	
	switch(WorkState_Flag)
	{
		
		case Prepare_State:
		{
			Set_Motor_Speed(CAN1, 0,0,0,0);
			if(time_tick_ms++ > PREPARE_TIME_TICK_MS)
			{
				WorkState_Flag = Normal_State;
			}			
		}break;
		
		case Normal_State:
		{
			Control_Task_Normal();
		}break;
		
		case Error_State:
		{
			Control_Task_Stop();
		}break;
		
		case Stop_State: 
		{
			Control_Task_Stop();
		}break;
		
		case Stop_State_ZS: 
		{
			Control_Task_Stop();
		}break;
		
		
		default:break;
		
	}
}








//正常模式------------------------------------------------------------------------
void Control_Task_Normal(void)
{
	  time_tick_ms++; 	

	if(time_tick_ms%2 == 0) 
	{  
/*
速度设定 遥控USART1频率		
实际速度 编码器CAN1接收中断频率		
电流输出 CAN1发送频率
下面的控制处理程序 频率		
*/
	
	Error_Flag=SysErrorStatus&0x0001;//遥控帧监视错误
	if(Error_Flag==1)
	{
  ChassisSpeedRef.forward_back_ref = 0;		
	ChassisSpeedRef.left_right_ref= 0;	 
	ChassisSpeedRef.rotate_ref= 0;		
	GimbalRef.pitch_angle_dynamic_ref= 0;				
	//GimbalRef.yaw_angle_dynamic_ref = 0;//底盘跟随后，实际的角度已经变了	
	}

     CMControlLoop();
	}
	if(time_tick_ms%4 == 0) 
	{
	  SetGimbalMotorOutput();	//设置云台电流输出

	}
	
		if(Error_Flag==1)
	{
 	   //Set_Holder_Position(CAN1, 0, 0,0);  
	   Set_Motor_Speed(CAN1, 0, 0, 0, 0);		 

	}
	if(time_tick_ms == 4000)
	time_tick_ms = 0;
}






//控制任务初始化---------------------------------------------------------------------
void ControtLoopTaskInit(void)
{
	time_tick_ms = 0;
	
/*PY轴控制初始化*/
	//斜坡Y,P初始化:设置计数最大值，计数值清0
	GMPitchRamp.SetScale(&GMPitchRamp, YAW_PITCH_PREPARE_TIME_TICK_MS);
	GMYawRamp.SetScale(&GMYawRamp, YAW_PITCH_PREPARE_TIME_TICK_MS);
	GMPitchRamp.ResetCounter(&GMPitchRamp);
	GMYawRamp.ResetCounter(&GMYawRamp);
  RampInitLoop(&CMDanceRamp,ChassisSpeedParm.dance_time);

	//云台给定角度初始化
	GimbalRef.pitch_angle_dynamic_ref = 0.0f;
	GimbalRef.yaw_angle_dynamic_ref = 0.0f;	
	Set_Motor_Speed(CAN1, 0,0,0,0);
}






//--------------------------------------------------------------------------------------------
void Control_Task_Stop_ZS(void)
{
  static u16 Count_Stop=0;
  Count_Stop++;
 //PID_Factor_Sure(&CMPID_S,37.0f,0,0);
	ChassisSpeedRef.forward_back_ref =0;
  ChassisSpeedRef.left_right_ref   =0; 
  ChassisSpeedRef.rotate_ref       =0; 
    
/*
if(Count_Stop<3000)	AAWWDD
	 time_tick_ms++; 	
	if(time_tick_ms%2 == 0) 
	{  
    CMControlLoop();
	}
	if(time_tick_ms == 4000)
	time_tick_ms = 0;
}	
else	
	*/
	 Set_Motor_Speed(CAN1, 0,0,0,0);         //底盘输出为0
   Set_Holder_Position(CAN1, 0, 0,0);  

   osDelay(3);
}






//错误模式---------------------------------------------------------------------
void Control_Task_Stop(void)
{
	
	 Set_Motor_Speed(CAN1, 0,0,0,0);         //底盘输出为0	

   osDelay(3);
}


