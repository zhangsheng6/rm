#include"tim.h"

extern 	 unsigned char color;
extern unsigned char send_data[5];
extern unsigned char  time_count;
unsigned char  time_count1=0;
extern	authorities_Status  running_mode;
int  seed;
/*
��ʱʱ����㣺
��ʱ��ʱ��Ƶ��f=ʱ��ԴƵ��/(Ԥ��Ƶֵ+1)=72MHz/ (psc+1)
��ʱ����ʱʱ��=(�Զ���װ������ֵ+1) / ��ʱ��ʱ��Ƶ��=(arr+1) /f=(arr+1) *t
*/
void Tim2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��һ�������¼��� �Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1ʱ��Ƶ�� ������ Ԥ��Ƶֵ����Χ0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //���ϼ�������ж�
	TIM_Cmd(TIM2, ENABLE);			

}

void Tim3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��һ�������¼��� �Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1ʱ��Ƶ�� ������ Ԥ��Ƶֵ����Χ0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 

//	TIM_Cmd(TIM3, ENABLE);		  //����ɹ���ʹ��	


}

/*
TIM2���ϼ�������жϣ����������seed++
*/

void TIM2_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־
			
			seed++;		   //���������
	}
}


/*
TIM3���ϼ�������жϣ�
	����һ��ʱ������ģʽ����actingģʽ������ʼtime_count++;
*/
void TIM3_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־
			if(running_mode == acting)
			{
      time_count++;
//			if(time_count>5)
//			{
//			    running_mode = fail;
//					Data_Integration(color);
//			    CAN_CMD_msg(send_data);//�ӷ��ͺ���
//			}
		 }
			if(running_mode == fail)
			{
				time_count1++;
				if(time_count1>2)
				{
					running_mode = acting;
					time_count1=0;
			  }
			}
			if(running_mode == success)
			{
			  time_count1++;
				if(time_count1>2)
				{
					running_mode = acting;
					time_count1=0;
			  }
			}
		}
}


