#ifndef _ADC_TASK_H_
#define _ADC_TASK_H_

#include "init.h"


typedef struct 
{
   float Ch1;
	 float Ch2;
	 float Ch3;
	 float Ch4;
	 float Ch_Ref;
	 float Ch_In;//ͨ��֮��
	 float ch_err; //ͨ�������ϵͳ���
}Current;

#define Offest_flag 0x05
#define Count 50   //�ɼ�50�κ�ʼ����

extern Current Real_Current;//ʵ�������ĵ���
extern Current Raw_Current;//ʵ�������ĵ���
extern Current Offest_Current;  //��׼ֵ

void ADC1_Data_processing(void);
#endif



