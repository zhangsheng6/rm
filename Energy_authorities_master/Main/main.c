#include "init.h"
/*
未解决
Systik
acting
ID
*/
int main(void)
{
	
	Init();

  while(1)
	{
	  Delay_Ms(500);
		Energy_Authorities();
		//ID有问题，PID实际值获取ID201，PID输出ID200
	  Can_Rx_MotorMessage_Process(&encoder,&rx1_message);//0x201,获得电机pid实际值
	  am[0]=PID_Control_Position(&PID_1);
    Can_Tx_Motor(am[0],am[0],am[0],am[0]);	//0x200，
	}

}



