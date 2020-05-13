#include"tim.h"

extern u16 TimeToMin;
extern Status_Flag  mode;
extern Bit16 Data[8]; //for the stady,right move 1 bit
extern Bit16 DataFlag,BoardFlag;

/*
Time2 ���ڼ�ͷ���ƶ�
������� ��arr��psc     
���㹫ʽ��Tout=((arr+1)*(psc+1))/Tclk
stm32F1xxϵ��:Tclk����
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
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx			

}

//Timer3 for dotarray up show 
//set two flag:"DataFlag" for DataUp move;"BoardFlag" for Board'pictures move
//set Tout=0.1s     �������
void Tim3_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
  TIM_TimeBaseStructure.TIM_Period = arr; //��һ�������¼��� �Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1ʱ��Ƶ�� ������ Ԥ��Ƶֵ����Χ0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
	


//	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx			

}


/*
���ڵ���������
ÿ��һ��ʱ��󣬵���������ͨ��can���ͻ�����Ϣ
				��������LED�����ƶ�������ͼ���ƶ�
*/
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TimeToMin++;
			if((TimeToMin==TimeCountMin)&&(mode.ActingSucess==1))
			{
				TimeToMin=0;
				CAN_Tx_Master(mode.ID,mode.hitted);
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			ring_shift_left(Data);
		}
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			DataFlag++;
			if(DataFlag==8)
			{
				DataFlag=0;
//				DataFlag=7;
				BoardFlag++;
				if(BoardFlag==7)
				{
//					DotArrayShowFull(Red);
					BoardFlag=6;
					DataFlag=7;
			
				}
			}
		}
		
}

