#include "MPU6050_i2c.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"


#define I2C_Pin_SCL		GPIO_Pin_6
#define I2C_Pin_SDA		GPIO_Pin_7
#define I2C_Pin_SDAN  7
// USE SCL->PB6 SDA->PB7
#define  SDA_IN()   {GPIOB->MODER&=~(3<<(I2C_Pin_SDAN*2));GPIOB->MODER|=0<<(I2C_Pin_SDAN*2);}	//输入模式
#define  SDA_OUT()  {GPIOB->MODER&=~(3<<(I2C_Pin_SDAN*2));GPIOB->MODER|=1<<(I2C_Pin_SDAN*2);}	//输出模式

#define  SCL_H         GPIOB->BSRRL = I2C_Pin_SCL
#define  SCL_L         GPIOB->BSRRH = I2C_Pin_SCL
#define  SDA_H         GPIOB->BSRRL = I2C_Pin_SDA
#define  SDA_L         GPIOB->BSRRH = I2C_Pin_SDA
#define  SDA_read      GPIOB->IDR  & I2C_Pin_SDA

void MPU_I2C_Configuration(void)			
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE );
	
	  GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL| I2C_Pin_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}
unsigned char I2C_Start(void)
{
	SDA_OUT();
	SCL_H;
	SDA_H;
	delay_us(4);
	SDA_L;
	delay_us(4);
	SCL_L;
	return 0;
}

void I2C_Stop(void)
{
	SDA_OUT();
	SCL_L;
	SDA_L;	
	delay_us(4);
	SCL_H;
	SDA_H;
	delay_us(4);
} 

void I2C_Ack(void)
{	
	SCL_L;
	SDA_OUT();
	SDA_L;	
	delay_us(2);
	SCL_H;
	delay_us(2);
	SCL_L;
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{	
  SCL_L;
	SDA_OUT();
	SDA_H;	
	delay_us(2);
	SCL_H;
	delay_us(2);
	SCL_L;	
} 

unsigned char I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	u8 Time_Count=0;
	SDA_IN();
	SDA_H;
	delay_us(1);
	SCL_H;
	delay_us(1);
	while(SDA_read)
	{
		Time_Count++;
		if(Time_Count>250)
		{
			I2C_Stop();
			return 1;
		}
	}
	SCL_L;
	return 0;
}



/*******************************************************************************
* Function Name  : I2C_ReadByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char I2C_ReadByte(u8 ack)  //数据从高位到低位//
{ 
   
  unsigned char ReceiveByte=0;
	u8 i=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
		SCL_L;
		delay_us(2);
		SCL_H;
	
		delay_us(2);
		ReceiveByte<<=1;
		if(SDA_read)	ReceiveByte++;		
		
	}
	if(!ack) I2C_NoAck();
	else			I2C_Ack();	
  return ReceiveByte;
} 
void I2C_SendByte(unsigned char SendByte) //数据从高位到低位//
{
  u8 i=0;
	SDA_OUT();
	SCL_L;	
	delay_us(2);
	for(i=0;i<8;i++)
	{
		if(SendByte&0x80)	//	 10000000	如果最高位位一则返回
		SDA_H;  
		else 
		SDA_L;   
		SendByte<<=1;
		delay_us(2);
		SCL_H;
		delay_us(2);
		SCL_L;	
	}
}
//-------------------------------------------------------------------------MPU9250 专用连续“读”函数
bool i2cReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t* buf)
{
	I2C_Start();
	I2C_SendByte(addr << 1|I2C_Transmitter);
	if(I2C_WaitAck())//接收应答成功返回0，不成功返回1
	{
		I2C_Stop();
		return 0;//0
	}
	I2C_SendByte(reg);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(addr << 1 | I2C_Receiver);
  I2C_WaitAck();
	while (len) 
    {     
        if (len == 1)
        *buf = I2C_ReadByte(0);
        else
        *buf = I2C_ReadByte(1);
        buf++;
        len--;
    }
    I2C_Stop();
    return 1;
}

int8_t i2cread(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	if(i2cReadBuffer(addr,reg,len,buf))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//-------------------------------------------------------------------------MPU9250 专用连续“写”函数
bool i2cWriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
	int i;
	I2C_Start();
	I2C_SendByte(addr << 1|I2C_Transmitter);
	if(I2C_WaitAck())//接收应答成功返回0，不成功返回1
	{
		I2C_Stop();
		return 0;//0
	}
	I2C_SendByte(reg);
	I2C_WaitAck();
	for(i = 0; i < len; i++)
	{
		I2C_SendByte(data[i]);
		if(I2C_WaitAck())//接收应答成功返回0，不成功返回1
		{
			I2C_Stop();
			return 0;//0
		}
	}
	I2C_Stop();
	return 1;//1
}
int8_t i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
{
	if(i2cWriteBuffer(addr,reg,len,data))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
