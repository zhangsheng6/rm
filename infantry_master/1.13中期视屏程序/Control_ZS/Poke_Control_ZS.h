#ifndef __POKE_CONTROL_ZS_H_
#define __POKE_CONTROL_ZS_H_

#include "init.h"
#include "PID_Control_ZS.h"

//extern PID GMPPositionPID;      	//pitch轴位置环PID
//extern PID GMPSpeedPID;      		//pitch轴速度换PID
//extern PID GMYPositionPID;			//yaw轴位置环PID
//extern PID GMYSpeedPID;      		//yaw轴速度环PID
extern PID GMPokeSpeedPID;
extern PID GMPokePositionPID;

//extern RampGen_t GMPitchRamp;		//云台pitch轴斜坡
//extern RampGen_t GMYawRamp ;			//云台yaw轴斜坡

//extern u16 Heat0_Limit;   //热量上限
//extern u8	Heat0_reserved;//热量上限余留


//void GMPitchControlLoop(void);
//void GMYawControlLoop(void);
void GMPokeControlLoop(void);

void SetGimbalMotorOutput(void);


#endif

