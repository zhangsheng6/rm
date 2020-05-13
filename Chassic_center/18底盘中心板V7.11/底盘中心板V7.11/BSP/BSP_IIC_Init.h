#ifndef __BSP_IIC_INIT_H_
#define __BSP_IIC_INIT_H_

#include "stm32f10x.h"

void IIC_Configuration(void);
void SDA_IN(void);
void SDA_OUT(void);
void IIC_delay(u16 time);

unsigned char IIC_Start(void);
void IIC_Stop(void);

void IIC_Ack(void);
void IIC_NoAck(void);
unsigned char IIC_WaitAck(void); 	 //����Ϊ:=1��ACK,=0��ACK

void IIC_SendByte(unsigned char SendByte); //���ݴӸ�λ����λ//
u8 IIC_ReadByte(unsigned char ack);



#endif















