#ifndef _init_h_
#define _init_h_

#include "misc.h"  //NVIC优先组
#include "stm32f10x.h" //定义u16
#include "delay.h" //定义u16

//IO外设初始化
#include "can.h"
#include "tim.h"
#include "sensor.h"
#include "read_port.h"
#include "led.h"

//驱动初始化
#include "iwdg.h"
#include "nvic.h"

//处理
#include "can_tr.h"
#include "dot_array_driver.h"


//任务初始化
//#include "task.h"


void Init(void);

#endif


