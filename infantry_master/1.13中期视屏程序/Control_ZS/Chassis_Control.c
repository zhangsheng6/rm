#include "init.h"
#include "Chassis_Control.h"
#include "math.h"
int Motor_Pwm;

//底盘PID变量
PID CMRotatePID;
PID CM1SpeedPID;
PID CM2SpeedPID;
PID CM3SpeedPID;
PID CM4SpeedPID;
PID CMGYROPID;

PID ChassisCurrentPID;

SPEED ChassisSpeedParm;     //底盘参数设置   

RampGenLoop_t CMDanceRamp;//猫步斜坡

//ChassisState chassisstate = Chassis_NORAML;//初始状态为正常
ChassisState chassisstate = Chassis_CRUISE;//初始状态为正常



//底盘控制循环  ChassisState
void CMControlLoop(void)
{ 	
	
//底盘正常状态：底盘跟随---------------------------------------------------------	
if(chassisstate==Chassis_NORAML)
{
	 if(WorkState_Flag==Prepare_State) //启动阶段，底盘不旋转
	{
			ChassisSpeedRef.rotate_ref = 0;
	}
  else  
	{
	    //底盘跟随编码器旋转PID计算
	    CMRotatePID.ref = 0;
		
	    CMRotatePID.fdb = GMYawEncoder.ecd_angle;	
		
     	PID_Set(&CMRotatePID,CMPID_Follow.P,CMPID_Follow.I,CMPID_Follow.D);
		
	    PID_Control_Position(&CMRotatePID);
			 
      //			 CMRotateSpeedPID.ref = CMRotatePID.pid_out;
			//			 CMRotateSpeedPID.fdb = -ChassisCenter.Gyro_Z;
			//			 VAL_LIMIT(CMRotateSpeedPID.ref, -650, 650);

			//			 PID_Set(&CMRotateSpeedPID,1.0f,0,0);

			//			 PID_Control(&CMRotateSpeedPID);
			//			 
			//			 VAL_LIMIT(CMRotateSpeedPID.pid_out, -500, 500);

			//			 ChassisSpeedRef.rotate_ref = CMRotateSpeedPID.pid_out;		
	      ChassisSpeedRef.rotate_ref = CMRotatePID.pid_out;
			// ChassisSpeedRef.rotate_ref = GMYawEncoder.ecd_angle;	
			
//漂移	
 ///*
   if(GMYawEncoder.ecd_angle<0)
	 GMYawEncoder.ecd_angle_abs=-GMYawEncoder.ecd_angle;
	 else
	 GMYawEncoder.ecd_angle_abs=GMYawEncoder.ecd_angle;
   if(GMYawEncoder.ecd_angle_abs<10)
	 {
	  CMGYROPID.ref=0;
		//CMGYROPID.fdb=-ChassisCenter.Gyro_Z;//有-号，陀螺仪角速度：顺时钟旋转150，逆时针旋转-150
		CMGYROPID.fdb= -MPU6050_Real_Data.Gyro_X;//有-号，陀螺仪角速度：顺时钟旋转150，逆时针旋转-150
  	PID_Set(&CMGYROPID,1.5f,0,1.0f);
		 PID_Control_Position(&CMGYROPID);	
		VAL_LIMIT(CMGYROPID.pid_out, -350, 350);
	   ChassisSpeedRef.drift_ref = CMGYROPID.pid_out;
	 }
	//	*/ 
	}
}	
	


//底盘不跟随状态------------------------------------------------------------------
else if (chassisstate==Chassis_CRUISE)
{
	  ChassisSpeedRef.rotate_ref = 0;
	/* 必须是底盘的6050
	  CMGYROPID.ref=0;
		CMGYROPID.fdb=-ChassisCenter.Gyro_Z;//有-号，陀螺仪角速度：顺时钟旋转150，逆时针旋转-150
  	PID_Set(&CMGYROPID,CMPID_GYRO.P,CMPID_GYRO.I,CMPID_GYRO.D);
		PID_Control_Position(&CMGYROPID);	
		VAL_LIMIT(CMGYROPID.pid_out, -350, 350);
	  ChassisSpeedRef.drift_ref = CMGYROPID.pid_out;
	*/
}
	
	
//底盘猫步状态--------------------------------------------------------------------------	
	else if(chassisstate==Chassis_DANCE)
	{
		//底盘跟随编码器旋转PID计算  猫步模式
		CMRotatePID.ref = RampCalcLoop(&CMDanceRamp)*ChassisSpeedParm.dance_angle;
		CMRotatePID.fdb = GMYawEncoder.ecd_angle;//加云台旋转量;
		PID_Set(&CMRotatePID,CMPID_Dance.P,CMPID_Dance.I,CMPID_Dance.D);
		PID_Control_Position(&CMRotatePID);  
		
//	  CMRotateSpeedPID.ref = CMRotatePID.pid_out;
// 	  CMRotateSpeedPID.fdb = -ChassisCenter.Gyro_Z;

//	  VAL_LIMIT(CMRotateSpeedPID.ref, -650, 650);

//	  PID_Set(&CMRotateSpeedPID,0.9f,0,0);
		
//		PID_Set(&CMRotateSpeedPID,ChaissisdanceSavedPID.Kp/10.0f,ChaissisdanceSavedPID.Ki/10.0f,ChaissisdanceSavedPID.Kd/10.0f);
//		
//	  PID_Control(&CMRotateSpeedPID);
//		
//		VAL_LIMIT(CMRotateSpeedPID.pid_out, -500, 500);

//	  ChassisSpeedRef.rotate_ref = CMRotateSpeedPID.pid_out;
		
		VAL_LIMIT(CMRotatePID.pid_out, -350, 350);
		ChassisSpeedRef.rotate_ref = CMRotatePID.pid_out;
	}

/*
车向右偏，角速度为-，加上-号，为正，
设定值-实际值，偏差为-，输出-	，
旋转设定值-，车向左
	
*/
	//if(ChassisSpeedRef.rotate_ref<0)
//	ChassisSpeedRef.rotate_ref_abs=-ChassisSpeedRef.rotate_ref;
	//else
	//ChassisSpeedRef.rotate_ref_abs=ChassisSpeedRef.rotate_ref;

/*	
	
//495	
  if(ChassisSpeedRef.rotate_ref_abs<10)
	{  //根据对 前后，左右速度设定的判断确定飘逸PID
	  CMGYROPID.ref=0;
		CMGYROPID.fdb=-ChassisCenter.Gyro_Z;//有-号，陀螺仪角速度：顺时钟旋转150，逆时针旋转-150
  	PID_Set(&CMGYROPID,CMPID_GYRO.P,CMPID_GYRO.I,CMPID_GYRO.D);
		 PID_Control_Position(&CMGYROPID);	
		VAL_LIMIT(CMGYROPID.pid_out, -350, 350);
	   ChassisSpeedRef.drift_ref = CMGYROPID.pid_out;
	}
	else if(ChassisSpeedRef.rotate_ref_abs<100)
	{  //根据对 前后，左右速度设定的判断确定飘逸PID
	  CMGYROPID.ref=0;
		CMGYROPID.fdb=-ChassisCenter.Gyro_Z;//有-号，陀螺仪角速度：顺时钟旋转150，逆时针旋转-150
  	PID_Set(&CMGYROPID,CMPID_GYRO.P,CMPID_GYRO.I,CMPID_GYRO.D);
		 PID_Control_Position(&CMGYROPID);	
		VAL_LIMIT(CMGYROPID.pid_out, -350, 350);
	   ChassisSpeedRef.drift_ref = CMGYROPID.pid_out;
	}
*/
	
//ChassisSpeedRef.left_right_ref =0;
//到黄电机正转 到红反转
	//英雄：轮胎1-4
//	/*
	CM1SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0  +ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0+ ChassisSpeedRef.drift_ref *2.0;
	CM2SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0  +ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0+ ChassisSpeedRef.drift_ref *2.0;
	CM3SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0  -ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0+ ChassisSpeedRef.drift_ref *2.0;
	CM4SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0  -ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0+ ChassisSpeedRef.drift_ref *2.0;
//		*/
		
 /*
 CM1SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0 + ChassisSpeedRef.rotate_ref *2.0;
	CM2SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0 + ChassisSpeedRef.rotate_ref *2.0 ; 
	CM3SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0  + ChassisSpeedRef.rotate_ref *2.0; 
	CM4SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0 + ChassisSpeedRef.rotate_ref *2.0 ;
	*/
	
	//步兵：轮胎1-4，电调id2143
//	CM2SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0  +ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0;
//	CM1SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0  +ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0;
//	CM4SpeedPID.ref =  ChassisSpeedRef.forward_back_ref *2.0  -ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0;
//	CM3SpeedPID.ref = -ChassisSpeedRef.forward_back_ref *2.0  -ChassisSpeedRef.left_right_ref *6.0 + ChassisSpeedRef.rotate_ref *2.0;
	
	CM1SpeedPID.fdb = CM1Encoder.filter_rate;
	CM2SpeedPID.fdb = CM2Encoder.filter_rate;
	CM3SpeedPID.fdb = CM3Encoder.filter_rate;
	CM4SpeedPID.fdb = CM4Encoder.filter_rate;
	
	PID_Set(&CM1SpeedPID,CMPID_Speed.P,CMPID_Speed.I,CMPID_Speed.D);
	PID_Set(&CM2SpeedPID, CMPID_Speed.P,CMPID_Speed.I,CMPID_Speed.D);
	PID_Set(&CM3SpeedPID,CMPID_Speed.P,CMPID_Speed.I,CMPID_Speed.D);
	PID_Set(&CM4SpeedPID,CMPID_Speed.P,CMPID_Speed.I,CMPID_Speed.D);

//前进：遥控660，速度设定660*2=1320，麦轮力抵消，真实速度 前进 设定660*根号2
//	(fabs(CM1SpeedPID.ref)<=560)? PID_Set(&CM1SpeedPID,31.75f,0.8,0):PID_Set(&CM1SpeedPID,26.75f,0.65,0.46);
//	(fabs(CM2SpeedPID.ref)<=560)? PID_Set(&CM2SpeedPID,31.75f,0.8,0):PID_Set(&CM2SpeedPID,26.75f,0.65,0.46);
//	(fabs(CM3SpeedPID.ref)<=560)? PID_Set(&CM3SpeedPID,31.75f,0.8,0):PID_Set(&CM3SpeedPID,26.75f,0.65,0.46);
//	(fabs(CM4SpeedPID.ref)<=560)? PID_Set(&CM4SpeedPID,31.75f,0.8,0):PID_Set(&CM4SpeedPID,26.75f,0.65,0.46);
	
	PID_Control_Position(&CM1SpeedPID);
	PID_Control_Position(&CM2SpeedPID);
	PID_Control_Position(&CM3SpeedPID);
	PID_Control_Position(&CM4SpeedPID);
	
	VAL_LIMIT(CM1SpeedPID.pid_out, -4000, 4000);//实际上最多2000把
	VAL_LIMIT(CM2SpeedPID.pid_out, -4000, 4000);
	VAL_LIMIT(CM3SpeedPID.pid_out, -4000, 4000);
	VAL_LIMIT(CM4SpeedPID.pid_out, -4000, 4000);
	
	// Set_Motor_Speed(CAN1, CHASSIS_SPEED_ATTENUATION * CM1SpeedPID.pid_out, CHASSIS_SPEED_ATTENUATION * CM2SpeedPID.pid_out, CHASSIS_SPEED_ATTENUATION * CM3SpeedPID.pid_out, CHASSIS_SPEED_ATTENUATION * CM4SpeedPID.pid_out);		 
	
//+功率限制PID-------------------------------------------------------------------------------------
//确定电机输出 正反转
  (CM1SpeedPID.pid_out<0)?(CM1SpeedPID.pid_out = -CM1SpeedPID.pid_out,CM1SpeedPID.out_sign = -1):(CM1SpeedPID.out_sign = 1);
	(CM2SpeedPID.pid_out<0)?(CM2SpeedPID.pid_out = -CM2SpeedPID.pid_out,CM2SpeedPID.out_sign = -1):(CM2SpeedPID.out_sign = 1);
	(CM3SpeedPID.pid_out<0)?(CM3SpeedPID.pid_out = -CM3SpeedPID.pid_out,CM3SpeedPID.out_sign = -1):(CM3SpeedPID.out_sign = 1);
	(CM4SpeedPID.pid_out<0)?(CM4SpeedPID.pid_out = -CM4SpeedPID.pid_out,CM4SpeedPID.out_sign = -1):(CM4SpeedPID.out_sign = 1);	

//确定各个电机输出 百分比
	CM1SpeedPID.proportion = CM1SpeedPID.pid_out/(CM1SpeedPID.pid_out+CM2SpeedPID.pid_out+CM3SpeedPID.pid_out+CM4SpeedPID.pid_out);
	CM2SpeedPID.proportion = CM2SpeedPID.pid_out/(CM1SpeedPID.pid_out+CM2SpeedPID.pid_out+CM3SpeedPID.pid_out+CM4SpeedPID.pid_out);
	CM3SpeedPID.proportion = CM3SpeedPID.pid_out/(CM1SpeedPID.pid_out+CM2SpeedPID.pid_out+CM3SpeedPID.pid_out+CM4SpeedPID.pid_out);
	CM4SpeedPID.proportion = CM4SpeedPID.pid_out/(CM1SpeedPID.pid_out+CM2SpeedPID.pid_out+CM3SpeedPID.pid_out+CM4SpeedPID.pid_out);

	 /*
  if(ChassisCenter.Power>60)//快超功率
	{
		ChassisCurrentPID.ref = 70000/ChassisCenter.Voltage;
	  //ChassisCurrentPID.ref = ((CM1SpeedPID.pid_out + CM2SpeedPID.pid_out + CM3SpeedPID.pid_out + CM4SpeedPID.pid_out)/16000)*(95000/ChassisCenter.Voltage);//归一化*3958
 
	  PID_Set(&ChassisCurrentPID,CMPID_Currenr.P,CMPID_Currenr.I,CMPID_Currenr.D);

		ChassisCurrentPID.fdb = ChassisCenter.Current*1000;
		PID_Control_Position(&ChassisCurrentPID);
		VAL_LIMIT(ChassisCurrentPID.pid_out, 0, 8000);	
	}
	
	else if(ChassisCenter.Power>40&ChassisCenter.Power<60)
	{
		ChassisCurrentPID.ref = 70000/ChassisCenter.Voltage;
	 // ChassisCurrentPID.ref = ((CM1SpeedPID.pid_out + CM2SpeedPID.pid_out + CM3SpeedPID.pid_out + CM4SpeedPID.pid_out)/16000)*(105000/ChassisCenter.Voltage);//归一化*4375
	
	  PID_Set(&ChassisCurrentPID,CMPID_Currenr.P,CMPID_Currenr.I,CMPID_Currenr.D);

		ChassisCurrentPID.fdb = ChassisCenter.Current*1000;
		PID_Control_Position(&ChassisCurrentPID);
		VAL_LIMIT(ChassisCurrentPID.pid_out, 0, 24000);		
	}
	else
	{
	*/
	  ChassisCurrentPID.ref=CM1SpeedPID.pid_out+CM2SpeedPID.pid_out+CM3SpeedPID.pid_out+CM4SpeedPID.pid_out;    //16000
	
	PID_Set(&ChassisCurrentPID,1.0f,0.0f,0.0f);
	 	  ChassisCurrentPID.fdb = 0;

	//	VAL_LIMIT(ChassisCurrentPID.ref, 0, 8000);
	
  //		(ChassisCurrentPID.ref<=600)? PID_Set(&ChassisCurrentPID,9.0f,0.1f,1.0f):PID_Set(&ChassisCurrentPID,10.0f,0.1f,1.0f);
 //   PID_Set(&ChassisCurrentPID,9.0f,0.0f,1.0f);

	//  ChassisCurrentPID.fdb = ChassisCenter.Current*1000;
		
		PID_Control_Position(&ChassisCurrentPID);
		
		VAL_LIMIT(ChassisCurrentPID.pid_out, 0, 24000);			
	//}
		
	CM1SpeedPID.final_out =CM1SpeedPID.out_sign*CM1SpeedPID.proportion*ChassisCurrentPID.pid_out;
	CM2SpeedPID.final_out =CM2SpeedPID.out_sign*CM2SpeedPID.proportion*ChassisCurrentPID.pid_out;
	CM3SpeedPID.final_out =CM3SpeedPID.out_sign*CM3SpeedPID.proportion*ChassisCurrentPID.pid_out;
	CM4SpeedPID.final_out =CM4SpeedPID.out_sign*CM4SpeedPID.proportion*ChassisCurrentPID.pid_out;



//Set_Motor_Speed(CAN1,CM1SpeedPID.final_out,CM2SpeedPID.final_out,CM3SpeedPID.final_out,CM4SpeedPID.final_out);		

Set_Motor_Speed(CAN1, CHASSIS_SPEED_ATTENUATION * CM1SpeedPID.final_out, CHASSIS_SPEED_ATTENUATION * CM2SpeedPID.final_out, CHASSIS_SPEED_ATTENUATION * CM3SpeedPID.final_out, CHASSIS_SPEED_ATTENUATION * CM4SpeedPID.final_out);		 


//Set_Motor_Speed(CAN1, 0 , 0, 0, 0);		 




















//Set_Motor_Speed(CAN1, 0, 0, 0, 0);		 
	

}
























////控制任务初始化程序
//void ControtLoopTaskInit(void)
//{
//	PID_Reset(&CMRotatePID);
//	PID_Reset(&CM1SpeedPID);
//	PID_Reset(&CM2SpeedPID);
//	PID_Reset(&CM3SpeedPID);
//	PID_Reset(&CM4SpeedPID);
//}
