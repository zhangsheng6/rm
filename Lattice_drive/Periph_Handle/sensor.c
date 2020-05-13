#include "sensor.h"
#include "dot_array_driver.h"

u8 HittedState;                //��־λ��ָʾ����Ҷ�Ƿ񱻻���  ���У�0��δ���У�1
extern Status_Flag  mode;

//A9:�������ӿڣ��ⲿ�ж� 
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
		
		//GPIOA.9  �ж����Լ��жϳ�ʼ������ 
  	//KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//EXTI��·ģʽ���жϡ��¼�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI�ж����󴥷���������
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
}


/*
�ⲿ�жϣ�
ͨ��acting��ready��״̬��ȷ����ʱĳ������װ�װ�Ļ�����Ϣ.hitted
��ͨ��CAN1���ͻ�����Ϣ
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
				if(Sensor()==1)                             //��һ�飬�������һ����ʱ����������㣬���Ŀ�
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
				EXTI_ClearITPendingBit(EXTI_Line9);  //���LINE3�ϵ��жϱ�־λ
			}
		}

}

//read PA9  ѹ���������ӿ�

u8 Sensor(void)
{
	u8 GetSensor;
	GetSensor=((GPIOA->IDR)&0x0200)>>9;
	return GetSensor;
	

}



