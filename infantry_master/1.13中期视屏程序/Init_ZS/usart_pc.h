#ifndef _BSP_USART_INIT_H_
#define _BSP_USART_INIT_H_

#include "init.h"                  // Device header

#define DMA_BUFFER_SIZE 6

void Usart6_Init(u32 bound);

extern float x,y;
extern double hight;




typedef enum
{
	MeMory1 = 0,
	MeMory2 = 1
}USART6_Recive;


typedef union Float
{
	float D;
	char d[4];
}Angle;

#endif


