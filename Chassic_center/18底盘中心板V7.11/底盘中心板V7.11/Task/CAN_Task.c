#include "init.h"

#define INFANTRY 1
#define HERO 2
#define ENGINEER 3
uint8_t RobotType;
JudgementType Judgement;
SendToJudgementDataType SendToJudgementData;

u32 systick_ms=0;
extern u8 flag;

void CAN_Revicer(CanRxMsg* RxMessage)
{
	if(RxMessage->StdId==0x3ff)
	{
		Real_Monitor.CAN_Recive_FrameCounter++;
		
		SendToJudgementData.ShootLevel = ((s16)(RxMessage->Data[0]<<8|RxMessage->Data[1]));
		SendToJudgementData.SuperCapacitorComment = ((s16)(RxMessage->Data[2]<<8|RxMessage->Data[3]));
		SendToJudgementData.data3 = ((s16)(RxMessage->Data[4]<<8|RxMessage->Data[5]));
		SendToJudgementData.State_Mask = ((s16)(RxMessage->Data[6]<<8|RxMessage->Data[7]));
	}
}

void CAN1_Send_16bitMessage(u32 ID,int16_t DATA1,int16_t DATA2,int16_t DATA3,int16_t DATA4)
{
	CanTxMsg CAN_TxMessage;
	union SendData{
			uint8_t c[2];
			int16_t i;
	}Data1,Data2,Data3,Data4;

	Data1.i=DATA1;
	Data2.i=DATA2;
	Data3.i=DATA3;
	Data4.i=DATA4;

	CAN_TxMessage.StdId=ID;
	CAN_TxMessage.RTR=CAN_RTR_DATA;
	CAN_TxMessage.IDE=CAN_ID_STD;
	CAN_TxMessage.DLC=0x08;
	CAN_TxMessage.Data[0]=Data1.c[1];
	CAN_TxMessage.Data[1]=Data1.c[0];
	CAN_TxMessage.Data[2]=Data2.c[1];
	CAN_TxMessage.Data[3]=Data2.c[0];
	CAN_TxMessage.Data[4]=Data3.c[1];
	CAN_TxMessage.Data[5]=Data3.c[0];
	CAN_TxMessage.Data[6]=Data4.c[1];
	CAN_TxMessage.Data[7]=Data4.c[0];
	
	CAN_Transmit(CAN1,&CAN_TxMessage);
}

  void CAN1_SendData_Update()
{
	if(ReadJudgementState)//�������ϵͳ��������ȡ״̬
	{
		if(RobotType==0)//�ϵ�ʱ�ж�һ�����Ѫ����ȷ�������˱���
		{
			if(judge_rece_mesg.game_information.max_hp==1000)
			{
				RobotType=INFANTRY;
			}
			else if(judge_rece_mesg.game_information.max_hp==2000)
			{
				RobotType=HERO;
			}
			else if(judge_rece_mesg.game_information.max_hp==5000)
			{
				RobotType=ENGINEER;
			}
		}
		
		Judgement.Voltage =(int16_t)(judge_rece_mesg.real_powerheat_data.chassisVolt*1000);
		Judgement.Current =(int16_t)(judge_rece_mesg.real_powerheat_data.chassisCurrent*1000);
		Judgement.Power = (int16_t)(judge_rece_mesg.real_powerheat_data.chassisPower*100);
		Judgement.PowerBuffer =(int16_t)(judge_rece_mesg.real_powerheat_data.chassisPowerBuffer*100);     //��������
		
		if(RobotType==INFANTRY)
		{
			switch(judge_rece_mesg.game_information.max_hp)
			{
				case 1000:
					Judgement.level = 1;
				break;
				
				case 1250:
					Judgement.level = 2;
				break;
				
				case 1500:
					Judgement.level = 3;
				break;
			}
			Judgement.ShooterHeat_17mm = judge_rece_mesg.real_powerheat_data.shooterHeat0;
		}
		else if(RobotType==HERO)
		{
			switch(judge_rece_mesg.game_information.max_hp)
			{
				case 2000:
					Judgement.level = 1;
				break;
				
				case 2500:
					Judgement.level = 2;
				break;
				
				case 3500:
					Judgement.level = 3;
				break;
			}
			Judgement.ShooterHeat_17mm = judge_rece_mesg.real_powerheat_data.shooterHeat0;
			Judgement.ShooterHeat_42mm = judge_rece_mesg.real_powerheat_data.shooterHeat1;
		}
		else
    {
			
		}
	}
	else
	{
		RobotType=0;
		Judgement.Voltage=25;
		Judgement.ShooterHeat_17mm=0;
		Judgement.ShooterHeat_42mm=0;
		Judgement.level=1;//Ĭ�ϵȼ�Ϊ1
		Judgement.PowerBuffer=0;
	}
}

void CAN_TxMssage(void)
{
	systick_ms++;
	CAN1_SendData_Update();
	//���� ��ѹ ���� ����
	if(systick_ms==1)
	{
		CAN1_Send_16bitMessage(0x300,INAReal_Data.voltage,INAReal_Data.current,INAReal_Data.power,SuperCapacitor_CompareState);
	}
	/*
	if(systick_ms==2)
	{
		if(RobotType==INFANTRY)
		{
			//������17mmǹ������/�ȼ�/����/���幦��
			CAN1_Send_16bitMessage(0x301,Judgement.ShooterHeat_17mm,Judgement.level,Judgement.Current,Judgement.PowerBuffer);
		}
		else if(RobotType==HERO)
		{
			//Ӣ�ۣ�42mmǹ������/�ȼ�/����/���幦��
			CAN1_Send_16bitMessage(0x301,Judgement.ShooterHeat_42mm,Judgement.level,Judgement.Current,Judgement.PowerBuffer);
		}
		else if(RobotType==ENGINEER)
		{
			//���̣���ѹ/����/����/���幦��
			CAN1_Send_16bitMessage(0x301,Judgement.Voltage,Judgement.Current,Judgement.Power,Judgement.PowerBuffer);
		}
	}
	*/
CAN1_Send_16bitMessage(0x301,Judgement.Voltage,Judgement.Current,Judgement.Power,Judgement.PowerBuffer);
	
	
	//���� ������ת���ٶ�  �˶�������ٶ�  �����Ƕ�
	if(systick_ms==3)
	{
	  CAN1_Send_16bitMessage(0x302,MPU6050_Real_Data.Gyro_Z*10,MPU6050_Real_Data.Accel*10,roll_angle,0);
		systick_ms=0;
	}
}

