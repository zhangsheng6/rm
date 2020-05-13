#ifndef UART_SEND_ZS_H_
#define UART_SEND_ZS_H_

#include "init.h"
#include "UART_Send_ZS.h"

void HEXACSII_ZS(u16 hex, u8* Print);

void UART_Send_Byte_ZS(USART_TypeDef* USARTx,u8 ch);
void UART_Send_ByteArray_ZS(USART_TypeDef* USARTx, u8 *ch, u32 len); 

void xingxing(void);
void jiange_(void);


void UART_Send_Enter_ZS(void);
void UART_Send_Uint16_ZS(u16 num, u8 enter);
void UART_Send_Int16_ZS(int16_t num, u8 enter);
void UART_SendFloat_ZS(float data, u8 enter);


void UART_Data_Learn_ZS(void);

#endif

