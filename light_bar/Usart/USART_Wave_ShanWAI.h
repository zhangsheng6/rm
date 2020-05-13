#ifndef USART_Wave_ShanWAI_H_
#define USART_Wave_ShanWAI_H_

#include "init.h"

void vcan_sendware(USART_TypeDef* USARTx);
void UART_PutFloatArr(USART_TypeDef* USARTx, float ch );

void UART_PutChar(USART_TypeDef* USARTx,u8 ch);
void UART_PutCharArr(USART_TypeDef* USARTx, u8 *ch, u32 len);

typedef union xxx
{
char c[4];
float f;
}Data;

extern float DataScope_OutPut_Buffer[8];

#endif

