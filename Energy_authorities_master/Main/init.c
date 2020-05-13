#include "init.h"
#define speed 34

void Init()
{
  NVIC_Init_User();
  Can1_Init();
  Usart1_Init(9600);
	Delay_Init();
	Tim2_Init(999,7199);  //移位定时器初始化    72Mhz/7200=10000  0.0001*1000=0.1s=100ms
  Tim3_Init(6999,7199); //计算时间击打能量机关(500ms)	 要求2.5s内击中   0.0001*7000=0.7s=700ms
	Led_Init();
	
  running_mode =acting; //得改  
	
  PID_Factor_Init();

	am[0] = speed;//右前
	PID_1.ref=am[0];

}


