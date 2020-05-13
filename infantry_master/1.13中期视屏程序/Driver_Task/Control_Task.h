#ifndef __CONTROL_TASK_H_
#define __CONTROL_TASK_H_

#include "init.h"

#define  Prepare_State 0  //准备模式
#define  Normal_State  1  //正常模式
#define  Error_State   2  //错误模式
#define	 Stop_State    3  //停止模式
#define	 Stop_State_ZS 4  //急停
#define  PREPARE_TIME_TICK_MS 500  //准备时间


extern char WorkState_Flag;
extern u8 Error_Flag;

void Control_Task(void);
void ControtLoopTaskInit(void);
void Control_Task_Stop(void);
void Control_Task_Stop_ZS(void);
void Control_Task_Normal(void);





#endif


