#include "main.h"

uint32_t Upload_Speed = 1;   //�����ϴ��ٶ�  ��λ Hz
#define upload_time (1000000/Upload_Speed)  //�����ϴ���ʱ�䡣��λΪus
uint32_t system_micrsecond;   //ϵͳʱ�� ��λms

int main(void)
{     			
	ControtLoopTaskInit();   //app init
	RemoteTaskInit();    
	BSP_Init();	
	delay_ms(500);
	system_micrsecond = Get_Time_Micros();	
	while(1)
	{
		IMU_getYawPitchRoll(angle);//�����Ƿ��жϱ�־�����¸���������ݲ�������̬�ں�

		if((Get_Time_Micros() - system_micrsecond) > upload_time)
		{
//			printf("CM1Encoder.raw_value = %d/r/n",GMYawEncoder.raw_value);
			system_micrsecond = Get_Time_Micros();
			UploadParameter();   //upload data to the PC			
			delay_ms(1);
		}
  }
}
