#include "GM_Control_ZS.h"
#include "PY_Control_ZS.h"
extern int Serve_ref;


//��̨���Ϳ����ź�
void SetGimbalMotorOutput(void)
{

	//��̨�Ƕ�����
  PYAngleLimit();

//P,Y��������	
 GimbalYaw_PitchControlModeSwitch();
 GMPitchControlLoop();
 GMYawControlLoop();
//�ڿڵ������
	GMPokeControlLoop();            //���������PID����
	
//Ħ���֣��������
 Friction_Servo_control();	
	 //	SetFrictionWheelSpeed(500+200);//Ħ����PWM��������
 //SetServeWheelAngle(250);	

 LASER_ON();
  VAL_LIMIT(GMYSpeedPID.pid_out, -5000, 5000);
	VAL_LIMIT(GMPSpeedPID.pid_out, -5000, 5000);
	
//��̨���Ƶ������								
//Set_Holder_Position(CAN1,(int16_t)GMYSpeedPID.pid_out,(int16_t)GMPSpeedPID.pid_out,(int16_t)GMPokeSpeedPID.pid_out);  
Set_Holder_Position(CAN1,(int16_t)GMYSpeedPID.pid_out,(int16_t)GMPSpeedPID.pid_out,(int16_t)GMPokePositionPID.pid_out);  
 // Set_Holder_Position(CAN1, 0, 0,0);  
}


