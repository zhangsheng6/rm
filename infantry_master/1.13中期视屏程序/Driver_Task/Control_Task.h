#ifndef __CONTROL_TASK_H_
#define __CONTROL_TASK_H_

#include "init.h"

#define  Prepare_State 0  //׼��ģʽ
#define  Normal_State  1  //����ģʽ
#define  Error_State   2  //����ģʽ
#define	 Stop_State    3  //ֹͣģʽ
#define	 Stop_State_ZS 4  //��ͣ
#define  PREPARE_TIME_TICK_MS 500  //׼��ʱ��


extern char WorkState_Flag;
extern u8 Error_Flag;

void Control_Task(void);
void ControtLoopTaskInit(void);
void Control_Task_Stop(void);
void Control_Task_Stop_ZS(void);
void Control_Task_Normal(void);





#endif


