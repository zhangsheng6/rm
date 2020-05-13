#include "main.h"

uint32_t Upload_Speed = 1;   //数据上传速度  单位 Hz
#define upload_time (1000000/Upload_Speed)  //计算上传的时间。单位为us
uint32_t system_micrsecond;   //系统时间 单位ms

int main(void)
{     			
	ControtLoopTaskInit();   //app init
	RemoteTaskInit();    
	BSP_Init();	
	delay_ms(500);
	system_micrsecond = Get_Time_Micros();	
	while(1)
	{
		IMU_getYawPitchRoll(angle);//根据是否中断标志来更新各数组的数据并进行姿态融合

		if((Get_Time_Micros() - system_micrsecond) > upload_time)
		{
//			printf("CM1Encoder.raw_value = %d/r/n",GMYawEncoder.raw_value);
			system_micrsecond = Get_Time_Micros();
			UploadParameter();   //upload data to the PC			
			delay_ms(1);
		}
  }
}
