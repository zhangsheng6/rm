#ifndef _encoder_h_
#define _encoder_h_

#include "init.h"


/*****CAN Bus 1*****/
#define CAN_BUS1_MOTOR1_FEEDBACK_MSG_ID  0x201
#define CAN_BUS1_MOTOR2_FEEDBACK_MSG_ID  0x202
#define CAN_BUS1_MOTOR3_FEEDBACK_MSG_ID  0x203
#define CAN_BUS1_MOTOR4_FEEDBACK_MSG_ID  0x204

#define  RATE_BUF_SIZE 6
typedef struct{
	int16_t	 	speed_rpm;    // 速度实际值
    int16_t  	real_current;
    int16_t  	given_current;
    uint8_t  	hall;
	uint16_t 	angle;				//abs angle range:[0,8191]
	uint16_t 	last_angle;	//abs angle range:[0,8191]
	uint16_t	offset_angle;
	int32_t		round_cnt;
	int32_t		total_angle;
	u8			buf_idx;
	u16			angle_buf[RATE_BUF_SIZE];
	u16			fited_angle;
	u32			msg_cnt;
}Encoder;

float Get_Motor_Message(Encoder *ptr, CanRxMsg* msg);


void Can_Rx_MotorMessage_Process(Encoder *ptr,CanRxMsg *msg);

extern  Encoder encoder; 

#endif


