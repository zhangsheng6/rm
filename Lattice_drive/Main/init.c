#include "init.h"

u8 CanIDValue;
RCC_ClocksTypeDef get_rcc_clock;

void Init()
{
	  NVIC_Init_User();
		Delay_Init();
		GPIO_Int();//A0-8
		Read_Port_Init();//B4-6
	 
		Tim2_Init(499,7199);  //��ʱ��2����ͷ�ƶ�   72Mhz/7200=10000  0.0001*500=0.05s=50ms
		Tim3_Init(499,4799);  //��ʱ��3   ͼ���ۼ�  72Mhz/4800=15000  1/15 *0.001*500=0.0333s=33.3ms
		RCC_GetClocksFreq(&get_rcc_clock); 		//���ز�ͬƬ��ʱ�ӵ�Ƶ�ʣ�  ���龧���Ƿ���ȷ
	
		Can1_Init();
		Sensor_Init_EXTI();
		CanIDValue=Get_CanID();//����1-5��ȷ�����ĸ�����
}
