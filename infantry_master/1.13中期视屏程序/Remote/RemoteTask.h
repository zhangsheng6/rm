#ifndef _REOMTETASK_H_
#define _REOMTETASK_H_
#include "init.h"
#include "Ramp_Control_ZS.h"

//ң��ֵ��̬ƫ��ֵremote control parameters
#define REMOTE_CONTROLLER_STICK_OFFSET      1024u 		

//ң��ֵϵ��
#define STICK_TO_CHASSIS_SPEED_REF_FACT     0.75f
#define STICK_TO_PITCH_ANGLE_INC_FACT       0.0035f//0.0035
#define STICK_TO_YAW_ANGLE_INC_FACT         0.004f

//���ֵϵ��mouse control parameters
#define MOUSE_TO_PITCH_ANGLE_INC_FACT 		0.12f
#define MOUSE_TO_YAW_ANGLE_INC_FACT 		0.08f
#define REMOTE_SWITCH_VALUE_BUF_DEEP   			16u

#define REMOTE_SWITCH_VALUE_UP         		0x01u  
#define REMOTE_SWITCH_VALUE_DOWN			0x02u
#define REMOTE_SWITCH_VALUE_CENTRAL			0x03u

//б�¼���ֵ
#define FRICTION_RAMP_TICK_COUNT			50//Ħ����
#define MOUSE_LR_RAMP_TICK_COUNT			50//�������
#define MOUSR_FB_RAMP_TICK_COUNT			80//���ǰ��

#define Key_W                         0x01     
#define Key_S                         0x02
#define Key_A                         0x04
#define Key_D                         0x08
#define Key_SHIFT                     0x10
#define Key_CTRL                      0x20
#define Key_Q                         0x40
#define Key_E                         0x80
#define Key_R                         0x100
#define Key_F                         0x200
#define Key_G                         0x400
#define Key_Z                         0x800
#define Key_X                         0x1000
#define Key_C                         0x2000
#define Key_V                         0x4000
#define Key_B                         0x8000	


typedef __packed struct
{
	int16_t ch0;
	int16_t ch1;
	int16_t ch2;
	int16_t ch3;
	int8_t s1;
	int8_t s2;
}Remote;//ң�����ṹ�嶨��


typedef __packed struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t last_press_l;
	uint8_t last_press_r;
	uint8_t press_l;
	uint8_t press_r;
}Mouse;	//���ṹ�嶨��


typedef	__packed struct
{
	uint16_t v;
}Key;//���̽ṹ�嶨��


typedef __packed struct
{
	Remote rc;
	Mouse mouse;
	Key key;
}RC_Ctl_t;





//remote data process type
typedef __packed struct
{
    int16_t forward_back_ref;
    int16_t left_right_ref;
    int16_t rotate_ref;
    int16_t rotate_ref_abs;
    int16_t drift_ref;
}ChassisSpeed_Ref_t;



typedef enum
{
	REMOTE_INPUT = 1,
	KEY_MOUSE_INPUT = 3,
	STOP = 2,
}InputMode_e;//����ģʽö�٣�ң����/�������/ֹͣ����


extern RC_Ctl_t RC_CtrlData;
extern ChassisSpeed_Ref_t ChassisSpeedRef;

extern RampGen_t frictionRamp ;  //Ħ����б��
extern RampGen_t LRSpeedRamp ;   //mouse�����ƶ�б��
extern RampGen_t FBSpeedRamp ;   //mouseǰ���ƶ�б��

extern u8	 Shot_Flag,Shot_Flag_Temp;
extern uint8_t ServoState ;
extern uint8_t FrictionState;
extern u8	 Friction_Flag,Friction_Flag_Temp;
extern u8	 Sero_Flag,Sero_Flag_Temp;

void RemoteDataPrcess(uint8_t *pData);
void RemoteControlProcess(Remote *rc);

void SetInputMode(Remote *rc);
void RemoteTaskInit(void);
void MouseKeyControlProcess(Mouse *mouse, Key *key);
void  MouseShootControl(Mouse *mouse);


#endif










