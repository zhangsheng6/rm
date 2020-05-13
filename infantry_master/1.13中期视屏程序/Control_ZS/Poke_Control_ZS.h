#ifndef __POKE_CONTROL_ZS_H_
#define __POKE_CONTROL_ZS_H_

#include "init.h"
#include "PID_Control_ZS.h"

//extern PID GMPPositionPID;      	//pitch��λ�û�PID
//extern PID GMPSpeedPID;      		//pitch���ٶȻ�PID
//extern PID GMYPositionPID;			//yaw��λ�û�PID
//extern PID GMYSpeedPID;      		//yaw���ٶȻ�PID
extern PID GMPokeSpeedPID;
extern PID GMPokePositionPID;

//extern RampGen_t GMPitchRamp;		//��̨pitch��б��
//extern RampGen_t GMYawRamp ;			//��̨yaw��б��

//extern u16 Heat0_Limit;   //��������
//extern u8	Heat0_reserved;//������������


//void GMPitchControlLoop(void);
//void GMYawControlLoop(void);
void GMPokeControlLoop(void);

void SetGimbalMotorOutput(void);


#endif

