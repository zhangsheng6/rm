#include "PY_Control_ZS.h"

PID GMPPositionPID;
PID GMYPositionPID;

PID GMPSpeedPID;
PID GMYSpeedPID;

RampGen_t GMPitchRamp = RAMP_GEN_DAFAULT;		//云台pitch轴斜坡
RampGen_t GMYawRamp = RAMP_GEN_DAFAULT;			//云台yaw轴斜坡
u16 guodu_count=0;

Gimbal_Ref_t GimbalRef;

u8 yaw_ready=0;
/****************************************************************/	
//PY轴 准备模式进入正常模式+确认位置PID的期望值和实际值-------------------------------------------------------------------
/****************************************************************/
void GimbalYaw_PitchControlModeSwitch(void)
{
static uint8_t normalFlag = 0;   //正常工作模式标志
static uint8_t prepareFlag = 1;  //IMU工作模式标志
static float angleSave = 0.0f;    //用于切换模式时保存切换前的角度值，用于角度给定值切换
	
	switch(WorkState_Flag)
	{
		
	  case  Prepare_State :
		{		
			if(prepareFlag == 1)
			{
				prepareFlag = 0;														
				normalFlag = 1;
			}
			
		  GMYPositionPID.ref = 0.0f;
			GMPPositionPID.ref = 0.0f;
			
			                  //不加斜坡，可能刚开始角度太大，调节太大，会旋转过冲或震荡
			                    //编码器角度 *斜坡归一值(经过500ms,从0增至1) 
			//往右实际值+
			GMYPositionPID.fdb =- GMYawEncoder.ecd_angle*GMYawRamp.Calc(&GMYawRamp);
			//往下低头，设定值+
			GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle * GMPitchRamp.Calc(&GMPitchRamp); 
						
			angleSave = yaw_angle;

		}		
		break;
		
		
		case   Normal_State :
		{
			//		LED1_ON
       //   LED2_ON			
			if(normalFlag == 1)										
			{
				prepareFlag = 1;														
				normalFlag = 0;
				//准备状态刚过来，往右角度设定值为+
				GimbalRef.yaw_angle_dynamic_ref = angleSave;   //修改设定值为STANDBY状态下记录的最后一个ZGYROMODULEAngle值，平稳过渡				
		   //GMPitchRamp.ResetCounter(&GMPitchRamp);
	    // GMYawRamp.ResetCounter(&GMYawRamp);
			}

	
			GMYPositionPID.ref = GimbalRef.yaw_angle_dynamic_ref;   //设定给定值
			GMPPositionPID.ref = GimbalRef.pitch_angle_dynamic_ref;
			
			//缓冲过程--------------------------------------------------
			if(guodu_count++<2000)
			{
 			GMYPositionPID.fdb =yaw_angle*GMYawRamp.Calc(&GMYawRamp);
			GMPPositionPID.fdb = - GMPitchEncoder.ecd_angle * GMPitchRamp.Calc(&GMPitchRamp); 
				//yaw_ready=1;
			}
			else
			{
			//往右，实际值
	   // GMYPositionPID.fdb = -GMYawEncoder.ecd_angle;//取块的时候 实际值 用的编码器角度
	    //往右，实际值+			
			GMYPositionPID.fdb = yaw_angle;//其他时候用的欧拉角
			//往下低头，设定值+
	    GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle;
					
			}
			
			
						angleSave = yaw_angle;

/*
	 Y轴通过单片机复位后的最初单片机位置确定 0角度
	 P轴通过已设定的编码器初始角度确定 0角度
*/	
		}		
		break;	

		case   Stop_State_ZS :
		{
		
		}		
		break;
			
	 default:
	 break;

	}

}

/*
由上述函数得：
GMPositionPID的：
  车刚复位时的准备状态：
	    设定值=0；期望值=编码器角度*斜坡归一系数(从0增至1，就一次) 
车运行时的正常状态：
	    设定值=遥控处理值；
      Y轴期望值=9250的yaw角度值
      P轴期望值=编码器角度
*/
/****************************************************************/	
//云台pitch轴控制程序-------------------------------------------------------------------
/****************************************************************/
void GMPitchControlLoop(void)
{
/*
低头设定值13角度度 实际0角度   外环输出13
内环设定13角速度   实际角速度0 pwm13
	
低头设定值13角度度 实际3角度   外环输出10
内环设定10角速度   实际角速度3 pwm7
eg：
内环设定0角速度   实际角速度13 pwm-13
遥控下拨，遥控角度设定正
云台低头，编码器角度正
云台低头，9259角度正
*/
	PID_Set(&GMPPositionPID,GMPPID_Position.P,GMPPID_Position.I,GMPPID_Position.D);	
	PID_Control_Position(&GMPPositionPID);   //得到pitch轴位置环输出控制量
	
	//pitch speed control  
	GMPSpeedPID.ref = GMPPositionPID.pid_out;//速度PID的实际值=位置PID的输出	
	//往下低头，设定值-
	GMPSpeedPID.fdb = -MPU6050_Real_Data.Gyro_X;//
  PID_Set(&GMPSpeedPID,GMPPID_Speed.P,GMPPID_Speed.I,GMPPID_Speed.D);
	PID_Control_Position(&GMPSpeedPID); 
}

/****************************************************************/	
//云台YAW控制输出13000+-  -------------------------------------------------------------------
/****************************************************************/
void GMYawControlLoop(void)
{
  PID_Set(&GMYPositionPID,GMYPID_Position.P,GMYPID_Position.I,GMYPID_Position.D);
	PID_Control_Position(&GMYPositionPID);

	//yaw speed control	
	GMYSpeedPID.ref = GMYPositionPID.pid_out;	
	//实际值 往右正
	GMYSpeedPID.fdb = -MPU6050_Real_Data.Gyro_Z;
	PID_Set(&GMYSpeedPID,GMYPID_Speed.P,GMYPID_Speed.I,GMYPID_Speed.D);
	PID_Control_Position(&GMYSpeedPID);			
}


/****************************************************************/	
//遥控器输入值设置,限制最大最小值-------------------------------------------------------------------
/*P轴
杨洋：
     遥控设置角度0度到35度
     编码器角度：云台低头为0度，云台中间17.5度，抬头35度 
zs: 
      遥控设置角度-35度到35度
     编码器角度：中间0度，云台抬头35度，云台低头-35度 
遥控一直拨到最前面，云台35度，云台低头
遥控一直拨到最后面，云台-35度，云台抬头
*/
/****************************************************************/

void PYAngleLimit(void)
{
/*
P轴：
 目前编码器极限角度在 -33度到13度之间变化
 若程序略微改变编码器初始偏差值	，角度发生改变，下述极限值改变
 若机械出问题/换了车/云台， 程序里的初始偏差值可能大大改变，
Y轴：	
	目前9250极限角度 在223度范围之间
	单片机复位初始化9250进入IMU线程之后的初始值便为yaw角的0度角
	云台在不同方向启动后，初始的位置为0度角，所以这里 他们之前 没有设置Y轴极限角度
*/
	//0到35度
  //VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -PITCH_MAX-35, PITCH_MAX+15);	//去年整车步兵	
  VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -PITCH_MAX-27, PITCH_MAX+27.5f);	//今年整车步兵	
  //极限不能超过当前角度的20度
	VAL_LIMIT(GimbalRef.yaw_angle_dynamic_ref, GMYPositionPID.fdb -YAW_MAX, GMYPositionPID.fdb+ YAW_MAX);	
  //可屏蔽  
	//屏蔽的话，底盘一直极限 旋转云台抖动
	//VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -230, 230);		

}










