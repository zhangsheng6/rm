#include"tim.h"

extern u16 TimeToMin;
extern Status_Flag  mode;
extern Bit16 Data[8]; //for the stady,right move 1 bit
extern Bit16 DataFlag,BoardFlag;

/*
Time2 用于箭头的移动
输入参数 ：arr，psc     
计算公式：Tout=((arr+1)*(psc+1))/Tclk
stm32F1xx系列:Tclk调整
定时时间计算：
定时器时钟频率f=时钟源频率/(预分频值+1)=72MHz/ (psc+1)
定时器定时时间=(自动重装载周期值+1) / 定时器时钟频率=(arr+1) /f=(arr+1) *t
*/
void Tim2_Init(u16 arr,u16 psc)
{
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
  TIM_TimeBaseStructure.TIM_Period = arr; //下一个更新事件的 自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1时钟频率 除数的 预分频值。范围0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx			

}

//Timer3 for dotarray up show 
//set two flag:"DataFlag" for DataUp move;"BoardFlag" for Board'pictures move
//set Tout=0.1s     具体调整
void Tim3_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
  TIM_TimeBaseStructure.TIM_Period = arr; //下一个更新事件的 自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1时钟频率 除数的 预分频值。范围0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
	


//	TIM_Cmd(TIM3, ENABLE);  //使能TIMx			

}


/*
用于点阵驱动：
每隔一定时间后，点阵驱动板通过can发送击打信息
				点阵驱动LED数据移动，用于图形移动
*/
void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TimeToMin++;
			if((TimeToMin==TimeCountMin)&&(mode.ActingSucess==1))
			{
				TimeToMin=0;
				CAN_Tx_Master(mode.ID,mode.hitted);
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
			ring_shift_left(Data);
		}
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
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

