#include "init.h"

static uint32_t can_count = 0;

/*
*Name        : CanReceiveMsgProcess
* Description: This function process the can message representing the encoder data received from the CAN2 bus.
* Arguments  : msg     is a pointer to the can message.
* Returns    : void
* Note(s)    : none
*/
void CanReceiveMsgProcess(CanRxMsg * msg)
{      
    can_count++;
		switch(msg->StdId)
		{
//�����ĸ��������Ϣ			
				case CAN_BUS2_MOTOR1_FEEDBACK_MSG_ID:
				{ 
								//	LED1_ON
					Real_Monitor.ChassisFrameCounter_1++;
					(can_count<=50) ? GetEncoderBias(&CM1Encoder ,msg):EncoderProcess(&CM1Encoder ,msg);       //��ȡ���������ĳ�ʼƫ��ֵ            
                    
				}break;
				
				case CAN_BUS2_MOTOR2_FEEDBACK_MSG_ID:
				{
								//		LED1_ON

					Real_Monitor.ChassisFrameCounter_2++;
					(can_count<=50) ? GetEncoderBias(&CM2Encoder ,msg):EncoderProcess(&CM2Encoder ,msg);
				}break;
				
				case CAN_BUS2_MOTOR3_FEEDBACK_MSG_ID:
				{
								//		LED1_ON

					Real_Monitor.ChassisFrameCounter_3++;
					(can_count<=50) ? GetEncoderBias(&CM3Encoder ,msg):EncoderProcess(&CM3Encoder ,msg);   
				}break;
				
				case CAN_BUS2_MOTOR4_FEEDBACK_MSG_ID:
				{ 
							//	LED1_ON
					Real_Monitor.ChassisFrameCounter_4++;
				 	(can_count<=50) ? GetEncoderBias(&CM4Encoder ,msg):EncoderProcess(&CM4Encoder ,msg);
				}break;
//��̨Y�������Ϣ------------------------------------------------------------							
				case CAN_BUS2_MOTOR5_FEEDBACK_MSG_ID:
				{ 
					//LED1_ON
					Real_Monitor.YawFrameCounter++;
				 //(can_count<=50) ? GetEncoderBias(&GMYawEncoder ,msg):EncoderProcess(&GMYawEncoder ,msg);
				if(can_count<=50) 
					GMYawEncoder.ecd_bias=3700;//������̨��  
					//GMYawEncoder.ecd_bias=3700;//������  		0	 
				else
				 EncoderProcess(&GMYawEncoder ,msg);
					/*
					if(WorkState_Flag==Prepare_State)
					{
					   if((GMYawEncoder.ecd_bias - GMYawEncoder.ecd_value) <-4000)
					   {
							//	GMYawEncoder.ecd_bias = GimbalSavedCaliData.GimbalYawOffset + 8192;
						 }
						 else if((GMYawEncoder.ecd_bias - GMYawEncoder.ecd_value) > 4000)
					  {
							//	GMYawEncoder.ecd_bias = GimbalSavedCaliData.GimbalYawOffset - 8192;
						 }
					}
					*/				
				}break;
//��P�������Ϣ------------------------------------------------------------------------------												
				case CAN_BUS2_MOTOR6_FEEDBACK_MSG_ID:
				{ 
					Real_Monitor.PitchFrameCounter++;
          //     LED2_ON
		if(can_count<=50)
				 GMPitchEncoder.ecd_bias=0;//֮ǰ������̨��
				//GMPitchEncoder.ecd_bias=1200;//������������ error2000
		else
				EncoderProcess(&GMPitchEncoder ,msg);			
		//(can_count<=50) ? GetEncoderBias(&GMPitchEncoder ,msg):EncoderProcess(&GMPitchEncoder ,msg);

				}break;
//��̨�ڿڵ������Ϣ------------------------------------------------------------												
				case CAN_BUS2_MOTOR7_FEEDBACK_MSG_ID:
				{ 
					//	LED1_ON			
				//	(can_count<=50) ? GetEncoderBias(&GMPokeEncoder ,msg):EncoderProcess(&GMPokeEncoder ,msg);
					if(can_count<=50)
					   GetEncoderBias(&GMPokeEncoder ,msg);
					else
					{
						EncoderProcess(&GMPokeEncoder ,msg);
						//GMPokeEncoder.ecd_angle = (float)(GMPokeEncoder.raw_value - GMPokeEncoder.ecd_bias)*360/8192;
          }
				}break;
//���ؽ��յ������İ�������ʵ���Ϣ							
				case CAN_BUS2_CURRENT_FEEDBACK_MSG_ID:
				{
					
					LED2_ON
					ChassisCenter.Voltage=((s16)(msg->Data[0]<<8|msg->Data[1]))*0.001;
					ChassisCenter.Current=((s16)(msg->Data[2]<<8|msg->Data[3]))*0.001;
					ChassisCenter.Power=((s16)(msg->Data[4]<<8|msg->Data[5]))*0.01;
					
				//	ChassisCenter.Voltage=((s16)(msg->Data[0]<<8|msg->Data[1]));
				//	ChassisCenter.Current=((s16)(msg->Data[2]<<8|msg->Data[3]));
				//	ChassisCenter.Power=((s16)(msg->Data[4]<<8|msg->Data[5]));
					
					ChassisCenter.CompareState=msg->Data[6]<<8|msg->Data[7];
				}break;		
//���ؽ��յ������İ���յĲ���ϵͳ����Ϣ											
				case CAN_BUS2_Judge_FEEDBACK_MSG_ID:
				{
					Real_JudgeMent.Voltage = msg->Data[0]<<8|msg->Data[1];
					Real_JudgeMent.Current = msg->Data[2]<<8|msg->Data[3];
					Real_JudgeMent.Power = ((s16)(msg->Data[4]<<8|msg->Data[5]))*0.001;
					Real_JudgeMent.PowerBuffer = ((s16)(msg->Data[6]<<8|msg->Data[7]))*0.01;
					
					/*
					Real_JudgeMent.Heat0 = msg->Data[0]<<8|msg->Data[1];
					Real_JudgeMent.Level = msg->Data[2]<<8|msg->Data[3];
					Real_JudgeMent.Current = ((s16)(msg->Data[4]<<8|msg->Data[5]))*0.001;
					Real_JudgeMent.PowerBuffer = ((s16)(msg->Data[6]<<8|msg->Data[7]))*0.01;
					*/
					
				}break;
//���ؽ��յ������İ��6050����Ϣ															
					case CAN_BUS1_ZGYRO_FEEDBACK_MSG_ID:
				{
										LED1_ON
					ChassisCenter.Gyro_Z = ((s16)(msg->Data[0]<<8|msg->Data[1]))*0.1;
					ChassisCenter.Accel = ((s16)(msg->Data[2]<<8|msg->Data[3]))*0.1;
					ChassisCenter.roll_angle = (s16)(msg->Data[4]<<8|msg->Data[5]);
				}break;			
				
				default:
				{
				}
		}
}






/*************************************************************************
�������ƣ�Set_Motor_Speed
�������������͵��̵����������ֵ( -32768~32767)
���������CANx	Motor1_Pwm	Motor2_Pwm	Motor3_Pwm	Motor4_Pwm
*************************************************************************/
void Set_Motor_Speed(CAN_TypeDef *CANx, int16_t Motor1_Pwm, int16_t Motor2_Pwm, int16_t Motor3_Pwm, int16_t Motor4_Pwm)
{
	  CanSend_Type   SendData;
	  SendData.CANx=CANx;
    SendData.SendCanTxMsg.StdId = 0x200;										//��׼IDֵ
    SendData.SendCanTxMsg.IDE = CAN_Id_Standard;						//��׼IDģʽ
    SendData.SendCanTxMsg.RTR = CAN_RTR_Data;							//����֡
    SendData.SendCanTxMsg.DLC = 0x08;											//���ݳ���8
    
    SendData.SendCanTxMsg.Data[0] = (uint8_t)(Motor1_Pwm >> 8);
    SendData.SendCanTxMsg.Data[1] = (uint8_t)Motor1_Pwm;
    SendData.SendCanTxMsg.Data[2] = (uint8_t)(Motor2_Pwm >> 8);
    SendData.SendCanTxMsg.Data[3] = (uint8_t)Motor2_Pwm;
    SendData.SendCanTxMsg.Data[4] = (uint8_t)(Motor3_Pwm >> 8);
    SendData.SendCanTxMsg.Data[5] = (uint8_t)Motor3_Pwm;
    SendData.SendCanTxMsg.Data[6] = (uint8_t)(Motor4_Pwm >> 8);
    SendData.SendCanTxMsg.Data[7] = (uint8_t)Motor4_Pwm;
	
    osMessageQueuePut(CanSend_MessageQueue,&SendData,osPriorityLow1,1);//��Ϣ���з�������
}


/*************************************************************************
�������ƣ�Set_Holder_Position
����������������̨�����������ֵ��-5000~+5000��
���������CANx	yaw	pitch Poke
*************************************************************************/
void Set_Holder_Position(CAN_TypeDef *CANx, int16_t yaw, int16_t pitch,int16_t Poke)
{ 
	  CanSend_Type   SendData;
	  SendData.CANx=CANx;
	 
    SendData.SendCanTxMsg.StdId = 0x1FF;
    SendData.SendCanTxMsg.IDE = CAN_Id_Standard;
    SendData.SendCanTxMsg.RTR = CAN_RTR_Data;
    SendData.SendCanTxMsg.DLC = 0x08;
    SendData.SendCanTxMsg.Data[0] = (unsigned char)(yaw >> 8);
    SendData.SendCanTxMsg.Data[1] = (unsigned char)yaw;
    SendData.SendCanTxMsg.Data[2] = (unsigned char)(pitch >> 8);
    SendData.SendCanTxMsg.Data[3] = (unsigned char)pitch;
    SendData.SendCanTxMsg.Data[4] = (unsigned char)(Poke >> 8);
    SendData.SendCanTxMsg.Data[5] =  (unsigned char)Poke ;
    SendData.SendCanTxMsg.Data[6] = 0x00;
    SendData.SendCanTxMsg.Data[7] = 0x00;

	  osMessageQueuePut(CanSend_MessageQueue,&SendData,osPriorityLow1,1);//��Ϣ���з�������
}


/*************************************************************************
�������ƣ�Set_Center_State
�������������͵��̿������İ�����
���������CANx	buff
*************************************************************************/
void Set_Center_State(CAN_TypeDef *CANx, char data1,char data2,char data3,char data4)
{ 
	  CanSend_Type   SendData;
	  SendData.CANx=CANx;
	 
    SendData.SendCanTxMsg.StdId = 0x3FF;
    SendData.SendCanTxMsg.IDE = CAN_Id_Standard;
    SendData.SendCanTxMsg.RTR = CAN_RTR_Data;
    SendData.SendCanTxMsg.DLC = 0x04;
    SendData.SendCanTxMsg.Data[0] = data1;
    SendData.SendCanTxMsg.Data[1] = data2;
    SendData.SendCanTxMsg.Data[2] = data3;
    SendData.SendCanTxMsg.Data[3] = data4;
	  osMessageQueuePut(CanSend_MessageQueue,&SendData,osPriorityLow1,1);//��Ϣ���з�������
}
