#ifndef __PY_CONTROL_ZS_H_
#define __PY_CONTROL_ZS_H_

#include "init.h"

#define YAW_PITCH_PREPARE_TIME_TICK_MS 2000      //prapare time in ms

#define PITCH_MAX 0.0f
#define YAW_MAX 20.0f



typedef struct
{	
    float pitch_angle_dynamic_ref;			
    float yaw_angle_dynamic_ref;
    float pitch_speed_ref;
    float yaw_speed_ref;
}Gimbal_Ref_t;




extern Gimbal_Ref_t GimbalRef;

extern PID GMPPositionPID;
extern PID GMYPositionPID;

extern PID GMPSpeedPID;
extern PID GMYSpeedPID;

extern  RampGen_t GMPitchRamp ;		//‘∆Ã®pitch÷·–±∆¬
extern RampGen_t GMYawRamp;			//‘∆Ã®yaw÷·–±∆¬
extern u8 yaw_ready;
extern void GimbalYaw_PitchControlModeSwitch(void);





void GMPitchControlLoop(void);
void GMYawControlLoop(void);

void PYAngleLimit(void);



#endif

