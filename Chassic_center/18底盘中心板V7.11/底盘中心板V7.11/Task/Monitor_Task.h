#ifndef _MONITOR_TASK_H_
#define _MONITOR_TASK_H_

#include "stm32f10x.h"                  // Device header
typedef struct SystemMonitor{
  u16 CAN_Send_FrameCounter;    //CAN��������֡
  u16 CAN_Recive_FrameCounter;				 //������������֡
  u16 Judgement_Recive_FrameCounter;	 //���ղ���ϵͳ����֡
  u16 IMUFrameCounter;                 //MPU6050��̬����֡
  u16 INA260FrameCounter;              //INA260����֡
}SystemMonitor;

extern SystemMonitor Real_Monitor;
extern SystemMonitor Rate_Monitor;
extern  uint16_t SysErrorStatus;
void Monitor_Thread1 (void const *argument);



#endif
