#include"tim.h"

extern 	 unsigned char color;
extern unsigned char send_data[5];
extern unsigned char  time_count;
unsigned char  time_count1=0;
extern	authorities_Status  running_mode;
int  seed;
/*
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
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //向上计数溢出中断
	TIM_Cmd(TIM2, ENABLE);			

}

void Tim3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = arr; //下一个更新事件的 自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //TIM1时钟频率 除数的 预分频值。范围0x0000-0xFFFF
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 

//	TIM_Cmd(TIM3, ENABLE);		  //激活成功那使能	


}

/*
TIM2向上计数溢出中断：随机数种子seed++
*/

void TIM2_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志
			
			seed++;		   //随机数种子
	}
}


/*
TIM3向上计数溢出中断：
	计数一定时间运行模式进入acting模式，并开始time_count++;
*/
void TIM3_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志
			if(running_mode == acting)
			{
      time_count++;
//			if(time_count>5)
//			{
//			    running_mode = fail;
//					Data_Integration(color);
//			    CAN_CMD_msg(send_data);//加发送函数
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


