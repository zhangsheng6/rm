#include "can.h"

CanRxMsg rx1_message;
int16_t  am[8]={0,0,0,0,0,0,0,0};


		
/*
Can1接收中断 
A11can接收
A12can发送
*/
void Can1_Init(void)
{
GPIO_InitTypeDef       GPIO_InitStructure;
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PORTA时钟	                   											 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	CAN_InitStructure.CAN_TTCM=DISABLE;					//时间触发通信模式:失能  
	CAN_InitStructure.CAN_ABOM=DISABLE;					//软件自动离线管理：失能
	CAN_InitStructure.CAN_AWUM=DISABLE;			    //自动唤醒模式：失能。  睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART=DISABLE;					//非自动重传输模式：失能。     是否禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM=ENABLE;					//接收FIFO锁定模式：使能。      报文不锁定,新的覆盖旧的 
	CAN_InitStructure.CAN_TXFP=ENABLE;					//发送FIFO优先级：使能。         由报文标识符决定 
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;	//CAN硬件工作模式： mode:普通模式，静默模式，环回模式静默环回模式
	//设置波特率
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //重新同步跳跃宽度(Tsjw)：为tsjw+1个时间单位  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_6tq; //时间段1的时间单位数目：Tbs1=tbs1+1个时间单位 CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_5tq; //时间段2的时间单位数目：Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=3;     //1个时间单位的长度：1-1024    分频系数(Fdiv)为brp+1	//
	CAN_Init(CAN1, &CAN_InitStructure);   // 初始化CAN1 

	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //待初始化的过滤器：0-13
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //过滤器初始化模式：标识符屏蔽位模式。  标识符列表模式
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //过滤器位宽：1个32位    。  2个16位
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;//过滤器标识符设定，16位时为第1个
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;//             后期设置
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//过滤器标识符/过滤器屏蔽标识符设定：32位MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//过滤器0关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //过滤器：使能
	CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化

	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//邮箱0中断，即FIFO0消息挂号中断屏蔽
//CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);//邮箱0中断
		

	}	


	
	/*
can1接收中断程序：接收扇形击打板被击打信息
	
USB_LP_CAN1_RX0_IRQHandler:因为PA11,12也是USB的引脚
CAN1_RX0_IRQn	：当CAN1引脚为PB8,9重映射引脚
*/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)//FIFO0消息挂号
    {		
			CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
      CAN_Receive(CAN1, CAN_FIFO0, &rx1_message);
      Can_Hook(&rx1_message);
			
    }		  
}
//void USB_HP_CAN1_TX_IRQHandler(void)
//{
//   if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
//	 {
//		 	 CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
//	 }
//}




