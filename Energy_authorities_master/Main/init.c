#include "init.h"
#define speed 34

void Init()
{
  NVIC_Init_User();
  Can1_Init();
  Usart1_Init(9600);
	Delay_Init();
	Tim2_Init(999,7199);  //��λ��ʱ����ʼ��    72Mhz/7200=10000  0.0001*1000=0.1s=100ms
  Tim3_Init(6999,7199); //����ʱ�������������(500ms)	 Ҫ��2.5s�ڻ���   0.0001*7000=0.7s=700ms
	Led_Init();
	
  running_mode =acting; //�ø�  
	
  PID_Factor_Init();

	am[0] = speed;//��ǰ
	PID_1.ref=am[0];

}


