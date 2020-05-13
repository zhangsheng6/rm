#include "delay.h"
static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
	
/*
ʹ��SysTick����ͨ����ģʽ���ӳٽ��й����ʺ�STM32F10xϵ�У�
����Delay_Ms,delay_ms
����ԭ��@ALIENTEK
������̳:www.openedv.com
��������:2010/1/1
�汾��V1.8
*/

/*
SysTick��Cortexϵͳ��ʱ��
*/
void Delay_Init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ϵͳʱ��Դ��AHBʱ��Դ/8��ѡ���ⲿʱ��  
	fac_us=SystemCoreClock/8000000;				//   =ϵͳʱ��72Mhz/8   
	fac_ms=(u16)fac_us*1000;					//��OS��,����ÿ��ms��Ҫ��systickʱ����   
}			

//����OSʱ   
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void Delay_Us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}


//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void Delay_Ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  	    
} 


