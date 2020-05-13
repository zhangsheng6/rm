#ifndef _init_h_
#define _init_h_

#include "misc.h"  //NVIC优先组
#include "delay.h"
#include "stm32f10x.h"

//IO外设初始化
#include "led.h"
#include "encoder.h"

//驱动初始化
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "nvic.h"


//处理
#include "can_tr.h"


//任务初始化
#include "energy_authorities_task.h"

//math
#include "pid.h"

void Init(void);

#endif


