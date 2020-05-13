#ifndef _init_h_
#define _init_h_

#include "misc.h"  //NVIC������
#include "delay.h"
#include "stm32f10x.h"

//IO�����ʼ��
#include "led.h"
#include "encoder.h"

//������ʼ��
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "nvic.h"


//����
#include "can_tr.h"


//�����ʼ��
#include "energy_authorities_task.h"

//math
#include "pid.h"

void Init(void);

#endif


