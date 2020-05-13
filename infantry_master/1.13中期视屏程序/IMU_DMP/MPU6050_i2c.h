#ifndef _MPU6050_I2C_H_
#define _MPU6050_I2C_H_
#include "stm32f4xx.h"

void MPU_I2C_Configuration(void);
unsigned char I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
unsigned char I2C_WaitAck(void);
void I2C_SendByte(unsigned char SendByte);
unsigned char I2C_ReadByte(u8 ack);
int8_t i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data);
int8_t i2cread(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
//0表示写
#define	I2C_Transmitter   0
//１表示读
#define	I2C_Receiver      1	

#define true 1
#define false 0 
#define bool  uint8_t


#define TRUE  0
#define FALSE -1

#endif
