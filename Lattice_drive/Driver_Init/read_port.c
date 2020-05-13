#include "read_port.h"

/*
端口模式：输入的初始化
端口：B3-5:用作ID
端口：B6:用作颜色确认
*/
void Read_Port_Init(void)
{
   GPIO_InitTypeDef GPIO_StructInit;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_StructInit.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; 
	 GPIO_StructInit.GPIO_Mode = GPIO_Mode_IPU;  
	 GPIO_Init(GPIOB,&GPIO_StructInit);
}
//*函数功能：读取PB口状态
//*输出参数：PB口状态
//	单片机端口：		PB6				PB5				PB4						PB3                 on方向为0   另一侧为1
//	对应拨码开关：	4					3					2							1
//Id 号对应 				PB6为高位，PB5为低位
//例如              PB6  PB5	PB4	 依次为100  则Id为0x304
u16 Read_Port(void)
{
  u16 ID;
	ID=GPIOB->IDR;   //IDR端口输入数据寄存器
	return (ID&0x78);// &0xxx x000  
}
/*
返回：CanID号：1~5
*/
u32 Get_CanID(void)
{
	u32 IDnumber;
	IDnumber=(u32)(((Read_Port())&0x70)>>4);//& 0xxx 0000
	return IDnumber;	//返回 xxx
}
//*函数名：ColourID
//*函数功能：提取ColourID
//*输入参数：无
//*输出参数：CanID号：1:red     0:blue                     //本设计中不用此函数
u16 Get_ColourID(void)
{
	u16 ColourID;
	ColourID=(Read_Port()&0x08>>3);
	return ColourID;
}

