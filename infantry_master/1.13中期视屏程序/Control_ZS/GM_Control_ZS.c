#include "GM_Control_ZS.h"
#include "PY_Control_ZS.h"
extern int Serve_ref;


//云台发送控制信号
void SetGimbalMotorOutput(void)
{

	//云台角度限制
  PYAngleLimit();

//P,Y轴电机控制	
 GimbalYaw_PitchControlModeSwitch();
 GMPitchControlLoop();
 GMYawControlLoop();
//炮口电机控制
	GMPokeControlLoop();            //拨弹电机的PID调节
	
//摩擦轮，舵机控制
 Friction_Servo_control();	
	 //	SetFrictionWheelSpeed(500+200);//摩擦轮PWM开环调节
 //SetServeWheelAngle(250);	

 LASER_ON();
  VAL_LIMIT(GMYSpeedPID.pid_out, -5000, 5000);
	VAL_LIMIT(GMPSpeedPID.pid_out, -5000, 5000);
	
//云台控制电流输出								
//Set_Holder_Position(CAN1,(int16_t)GMYSpeedPID.pid_out,(int16_t)GMPSpeedPID.pid_out,(int16_t)GMPokeSpeedPID.pid_out);  
Set_Holder_Position(CAN1,(int16_t)GMYSpeedPID.pid_out,(int16_t)GMPSpeedPID.pid_out,(int16_t)GMPokePositionPID.pid_out);  
 // Set_Holder_Position(CAN1, 0, 0,0);  
}


