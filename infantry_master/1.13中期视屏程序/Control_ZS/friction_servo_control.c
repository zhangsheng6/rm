#include "friction_servo_control.h"
u8	 Friction_Flag_OK=0;
u8	 Sero_Flag_OK=0;
u16 Friction_PWM=500;
u16 Sero_PWM=250;
void Friction_Servo_control(void)
{
//舵机	
	Sero_Flag=Sero_Flag_Temp;
	
	if(Sero_Flag==1)
	{
		if(Sero_Flag_OK==1)
		{
	   	Sero_Flag_OK=0;
	  	 ServoState++;
			 if(ServoState>1)
				 ServoState=0;
		}
	}
	else if(Sero_Flag==2)
	{
		Sero_Flag_OK=1;
	}
//摩擦轮
	
	Friction_Flag=Friction_Flag_Temp;
	
	if(Friction_Flag==1)
	{
		if(Friction_Flag_OK==1)
		{
	   	Friction_Flag_OK=0;
	  	 FrictionState++;
			 if(FrictionState>2)
				 FrictionState=0;
		}
	}
	else if(Friction_Flag==2)
	{
		Friction_Flag_OK=1;
	}
	

	
	
	
	
	if(FrictionState>1)//2
	{
		 Friction_PWM=500+350;
	}
	else if(FrictionState>0)//1
	{
	   Friction_PWM=500+300;
	}
	else
	{
	   Friction_PWM=500+0;
	}
	
	
	
	if(ServoState>0)
	{
//0,500一样，开半个 ；250shun全开；750顺时针开点；1000ni时针全开
		Sero_PWM=250;
	}
	else
	{
		Sero_PWM=600;

	}
	

//俩摩擦轮电机控制	

	
SetFrictionWheelSpeed(Friction_PWM);//摩擦轮PWM开环调节
 SetServeWheelAngle(Sero_PWM);	


}




