#ifndef _init_h_
#define _init_h_

#include "misc.h"  //NVIC优先组

//外设IO初始化
#include "can.h"
#include "led.h"

//驱动初始化
#include "nvic.h"
#include "delay.h"

//任务初始化
#include "energy_authorities_task.h"

void Init(void);

#endif


