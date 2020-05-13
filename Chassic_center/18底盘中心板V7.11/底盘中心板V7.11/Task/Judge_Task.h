#ifndef _JUDGE_TASK_H_
#define _JUDGE_TASK_H_

#include "stm32f10x.h"                  // Device header
#include "judgement_info.h"
#include "protocol.h"

typedef enum
{
	NONE_STATE=0,//δ��ȡ������ϵͳ����״̬
	NORMAL_STATE,//������ȡ״̬
}ReadJudgementState_e;

extern	ReadJudgementState_e	ReadJudgementState;
extern client_show_data_t Client_Show_Data;

void Judge_DataVerify(u8 *Buff);
void Send_FrameData(judge_data_id_e cmdid, uint8_t * pchMessage,uint8_t dwLength);
void Send_Judge_Update(void);

#endif


