#ifndef _usart_h_
#define _usart_h_

#include "init.h"

#define USART_REC_LEN  			1  	//�����������ֽ��� 200
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

void Usart1_Init(u32 bound);

#endif


