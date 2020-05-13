#include "encoder.h"
 Encoder encoder; 

/*
ͨ��can���յ���Ϣ ���� ��������Ϣ
��е�Ƕ�=Data[0]Data[1]
ʵ�ʵ���ֵ=Data[2]Data[3]
ÿ���ת��ֵ=ʵ�ʵ���ֵ
PID����ʵ��ֵ=ʵ�ʵ���ֵ/10
*/
float Get_Motor_Message(Encoder *ptr, CanRxMsg* msg)
{   
	ptr->last_angle = ptr->angle;
	ptr->angle = (uint16_t)(msg->Data[0]<<8 |msg->Data[1]) ;
	ptr->real_current  = (int16_t)(msg->Data[2]<<8 | msg->Data[3]);
	ptr->speed_rpm = ptr->real_current;	
//	ptr->given_current = (int16_t)(msg->Data[4]<<8 | msg->Data[5])/-5;
//	ptr->hall = msg->Data[6];
	if(ptr->angle - ptr->last_angle > 4200)
		ptr->round_cnt --;
	else if (ptr->angle - ptr->last_angle < -4200)
		ptr->round_cnt ++;
	ptr->total_angle = ptr->round_cnt * 8191 + ptr->angle - ptr->offset_angle;
    return 	ptr->real_current/10.0f;
	//
}

 
/*
����can�������ݣ�
ID:0X201
��ã�PID����ʵ��ֵ
*/
void Can_Rx_MotorMessage_Process(Encoder *ptr,CanRxMsg *msg)
{
	switch(msg->StdId)
	{
		case CAN_BUS1_MOTOR1_FEEDBACK_MSG_ID:
		{
		PID_1.fdb =Get_Motor_Message( ptr,  msg);//
			
		}break;
//		case CAN_BUS1_MOTOR2_FEEDBACK_MSG_ID:
//		{
//		PID2.fdb =Get_Motor_Message(ptr, msg);//(msg->Data[2]<<8)|msg->Data[3];
//		}break;
//		case CAN_BUS1_MOTOR3_FEEDBACK_MSG_ID:
//		{
//		PID3.fdb =Get_Motor_Message(ptr, msg);//(msg->Data[2]<<8)|msg->Data[3];
//		}break;
//		case CAN_BUS1_MOTOR4_FEEDBACK_MSG_ID:
//		{ 
//		PID4.fdb =Get_Motor_Message(ptr,  msg);//(msg->Data[2]<<8)|msg->Data[3];	
//		}break;
		default:
		{
			
		}break;	
	}
}





