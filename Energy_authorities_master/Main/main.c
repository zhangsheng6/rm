#include "init.h"
/*
δ���
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
		//ID�����⣬PIDʵ��ֵ��ȡID201��PID���ID200
	  Can_Rx_MotorMessage_Process(&encoder,&rx1_message);//0x201,��õ��pidʵ��ֵ
	  am[0]=PID_Control_Position(&PID_1);
    Can_Tx_Motor(am[0],am[0],am[0],am[0]);	//0x200��
	}

}



