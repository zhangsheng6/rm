#ifndef _THREAD_ZS_H_
#define _THREAD_ZS_H_
#include "stm32f4xx.h"                  // Device header
#include "init.h"

#include "Thread_ZS.h"

typedef struct SystemMonitor{
  u16 DBUSFrameCounter;  //遥控信号帧
	u16 PitchFrameCounter;  //云台电机帧
  u16 YawFrameCounter;
	u16 ChassisFrameCounter_1;  //底盘电机帧
  u16 ChassisFrameCounter_2;
	u16 ChassisFrameCounter_3;
	u16 ChassisFrameCounter_4;
  u16 IMUFrameCounter;        //姿态数据帧
}SystemMonitor;


extern SystemMonitor Real_Monitor;
extern uint16_t SysErrorStatus;   


void Usart_Send_Thread1(void const *argument);
void Control_Thread1 (void const *argument);
void IMU_Thread1 (void const *argument);
void Monitor_Thread1 (void const *argument);
void Calibrate_Thread1 (void const *argument);


#endif

