#include "Control_Task.h"
#include "Thread_ZS.h"

char WorkState_Flag = 0;   //������׼��
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








//����ģʽ------------------------------------------------------------------------
void Control_Task_Normal(void)
{
	  time_tick_ms++; 	

	if(time_tick_ms%2 == 0) 
	{  
/*
�ٶ��趨 ң��USART1Ƶ��		
ʵ���ٶ� ������CAN1�����ж�Ƶ��		
������� CAN1����Ƶ��
����Ŀ��ƴ������ Ƶ��		
*/
	
	Error_Flag=SysErrorStatus&0x0001;//ң��֡���Ӵ���
	if(Error_Flag==1)
	{
  ChassisSpeedRef.forward_back_ref = 0;		
	ChassisSpeedRef.left_right_ref= 0;	 
	ChassisSpeedRef.rotate_ref= 0;		
	GimbalRef.pitch_angle_dynamic_ref= 0;				
	//GimbalRef.yaw_angle_dynamic_ref = 0;//���̸����ʵ�ʵĽǶ��Ѿ�����	
	}

     CMControlLoop();
	}
	if(time_tick_ms%4 == 0) 
	{
	  SetGimbalMotorOutput();	//������̨�������

	}
	
		if(Error_Flag==1)
	{
 	   //Set_Holder_Position(CAN1, 0, 0,0);  
	   Set_Motor_Speed(CAN1, 0, 0, 0, 0);		 

	}
	if(time_tick_ms == 4000)
	time_tick_ms = 0;
}






//���������ʼ��---------------------------------------------------------------------
void ControtLoopTaskInit(void)
{
	time_tick_ms = 0;
	
/*PY����Ƴ�ʼ��*/
	//б��Y,P��ʼ��:���ü������ֵ������ֵ��0
	GMPitchRamp.SetScale(&GMPitchRamp, YAW_PITCH_PREPARE_TIME_TICK_MS);
	GMYawRamp.SetScale(&GMYawRamp, YAW_PITCH_PREPARE_TIME_TICK_MS);
	GMPitchRamp.ResetCounter(&GMPitchRamp);
	GMYawRamp.ResetCounter(&GMYawRamp);
  RampInitLoop(&CMDanceRamp,ChassisSpeedParm.dance_time);

	//��̨�����Ƕȳ�ʼ��
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
	 Set_Motor_Speed(CAN1, 0,0,0,0);         //�������Ϊ0
   Set_Holder_Position(CAN1, 0, 0,0);  

   osDelay(3);
}






//����ģʽ---------------------------------------------------------------------
void Control_Task_Stop(void)
{
	
	 Set_Motor_Speed(CAN1, 0,0,0,0);         //�������Ϊ0	

   osDelay(3);
}


