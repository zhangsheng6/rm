#include "led.h"

/*
A5 6 7 9
B0 1 2 5 6 7
*/
void Led_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}


//控制灯条，A是上面的，B是下面的
void Light_Bar(unsigned char num,unsigned char A,unsigned char B)
{
   switch(num)
	 {
	   case 4:   //PA5 PA6     1
			  PAout(5) = A;
		    PAout(6) = B;
		    break;
		 case 0:   //PA7 PB0			2
			  PAout(7) = A;
		    PBout(0) = B;		
        break;		 
		 case 1:	 //PB1 PB2			3
			  PBout(1) = A;
		    PBout(2) = B;	
        break;		 
     case 2:   //PA8 PB5			4
			  PAout(8) = A;
		    PBout(5) = B;	
		    break;		 
     case 3:   //PB6 PB7			5
			  PBout(6) = A;
		    PBout(7) = B;	
        break;		 
	 }	
}









