#ifndef _CAN_TASK_H_
#define _CAN_TASK_H_

#include "stm32f10x.h"                  // Device header
#include "judgement_info.h"

typedef struct
{
	int16_t Voltage;
	int16_t Current;
	int16_t ShooterHeat_17mm;
	int16_t ShooterHeat_42mm;
	int16_t Power;
	int16_t PowerBuffer;
	u8 level;
}JudgementType;

typedef struct
{
	int16_t ShootLevel;
	int16_t SuperCapacitorComment;
	float data3;
	u8 State_Mask;

}SendToJudgementDataType;

extern SendToJudgementDataType SendToJudgementData;
extern JudgementType Judgement;

void CAN1_Send_16bitMessage(u32 ID,int16_t DATA1,int16_t DATA2,int16_t DATA3,int16_t DATA4);

void CAN1_SendData_Update(void);

void CAN_Revicer(CanRxMsg* RxMessage);
void CAN_TxMssage(void);
#endif


