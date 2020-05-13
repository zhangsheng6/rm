#include "sensor.h"
#include "dot_array_driver.h"

u8 HittedState;                //标志位，指示该扇叶是否被击中  击中：0；未击中：1
extern Status_Flag  mode;

//A9:传感器接口，外部中断 
void Sensor_Init_EXTI(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		GPIO_InitTypeDef GPIO_StructInit;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		GPIO_StructInit.GPIO_Pin =GPIO_Pin_9; 
		GPIO_StructInit.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_Init(GPIOA,&GPIO_StructInit);
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);
		
		//GPIOA.9  中断线以及中断初始化配置 
  	//KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//EXTI线路模式：中断。事件
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI中断请求触发：上升沿
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	
}


/*
外部中断：
通过acting和ready的状态来确定此时某个扇形装甲板的击打信息.hitted
并通过CAN1发送击打信息
*/
void EXTI9_5_IRQHandler(void)
{
		
//		delay_us(10);
//		HittedState=Sensor();
		if(EXTI_GetITStatus(EXTI_Line9)!=RESET)                   
		{
			if(Sensor()==1)
			{
				delay_us(500);
				if(Sensor()==1)                             //第一块，第三块加一层延时，第五块两层，第四块
				{
//					delay_us(200);
				
						if((mode.Acting==1)&&(mode.Ready==1))  
							{
						mode.hitted=1;
							}
						if((mode.Acting==1)&&(mode.Ready==0))  
							{
							mode.hitted=2;
								
							}
						for(int i=0;i<20;i++)
						{ 
							delay_us(50);
							CAN_Tx_Master(mode.ID,mode.hitted);
						}
						
						
				}
				EXTI_ClearITPendingBit(EXTI_Line9);  //清除LINE3上的中断标志位
			}
		}

}

//read PA9  压力传感器接口

u8 Sensor(void)
{
	u8 GetSensor;
	GetSensor=((GPIOA->IDR)&0x0200)>>9;
	return GetSensor;
	

}



