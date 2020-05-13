#include "init.h"

u8 CanIDValue;
RCC_ClocksTypeDef get_rcc_clock;

void Init()
{
	  NVIC_Init_User();
		Delay_Init();
		GPIO_Int();//A0-8
		Read_Port_Init();//B4-6
	 
		Tim2_Init(499,7199);  //定时器2，箭头移动   72Mhz/7200=10000  0.0001*500=0.05s=50ms
		Tim3_Init(499,4799);  //定时器3   图形累加  72Mhz/4800=15000  1/15 *0.001*500=0.0333s=33.3ms
		RCC_GetClocksFreq(&get_rcc_clock); 		//返回不同片上时钟的频率：  检验晶振是否正确
	
		Can1_Init();
		Sensor_Init_EXTI();
		CanIDValue=Get_CanID();//返回1-5，确认是哪个扇形
}
