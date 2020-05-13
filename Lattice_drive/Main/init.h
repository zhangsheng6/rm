#ifndef _init_h_
#define _init_h_

#include "misc.h"  //NVIC������
#include "stm32f10x.h" //����u16
#include "delay.h" //����u16

//IO�����ʼ��
#include "can.h"
#include "tim.h"
#include "sensor.h"
#include "read_port.h"
#include "led.h"

//������ʼ��
#include "iwdg.h"
#include "nvic.h"

//����
#include "can_tr.h"
#include "dot_array_driver.h"


//�����ʼ��
//#include "task.h"


void Init(void);

#endif


