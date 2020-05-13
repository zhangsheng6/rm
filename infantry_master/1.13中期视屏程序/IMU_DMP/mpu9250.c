#include "mpu9250.h"
#include "inv_mpu.h"
#include "MPU6050_i2c.h"
#include "mpu6050_interrupt.h"
#include "delay.h"
#include "PY_Control_ZS.h"

MPU6050_REAL_DATA   MPU6050_Real_Data;
float   yaw_angle,pitch_angle,roll_angle; //使用到的角度值
MPU9250_STATUS MPU9250_Status_Read_Akm8963_ID(void);//返回值: 0：成功  1：失败
//-----------------------------------------------------------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-----------------------------------------------------------------------
//----------------------数据变量定义-------------------------------------
//-----------------------------------------------------------------------
//=======================================================================
//-------------------------------------------------------------------------MPU9250初始化函数
MPU9250_STATUS MPU9250_Init(void)
{
	u8 get_ID=0;			
	MPU9250_Write_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0x80);//复位MPU9250
	delay_ms(100);
	MPU9250_Write_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0x00);//唤醒MPU9250 
	MPU9250_Set_Gyro(3);				//陀螺仪传感器,±250dps;1,±500dps;2,±1000dps;3,±2000dps
	MPU9250_Set_Accel(0);				//加速度传感器,±2g->0 ±4->1 ±8->2
	MPU9250_Set_Rate(50);			//设置采样频率
	MPU9250_Write_Byte(MPU_ADDR,MPU_INT_EN_REG,0x00);		//关闭所有中断
	MPU9250_Write_Byte(MPU_ADDR,MPU_USER_CTRL_REG,0x00);//I2C主模式关闭，HCM588L由主总线驱动
	MPU9250_Write_Byte(MPU_ADDR,MPU_FIFO_EN_REG,0x00);	//关闭FIFO
	MPU9250_Write_Byte(MPU_ADDR,MPU_INTBP_CFG_REG,0x80);//INT引脚低电平有效
	get_ID=MPU9250_Read_Byte(MPU_ADDR,MPU_DEVICE_ID_REG);
	if(get_ID==0x71)
	{
		MPU9250_Write_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0x01);		//设置CLKSEL,PLL X轴为参考
		MPU9250_Write_Byte(MPU_ADDR,MPU_PWR_MGMT2_REG,0x00);		//加速度与陀螺仪都工作
		MPU9250_Set_Rate(50);											//设置采样频率
	}else return MPU9250_FAIL;

	mpu_dmp_init();
	MPU6050_IntConfiguration();
	return MPU9250_OK;
	
}

//-------------------------------------------------------------------------MPU9250 读取AKM8963器件ID
MPU9250_STATUS MPU9250_Status_Read_Akm8963_ID(void)//返回值: 0：成功  1：失败
{
	u8 id=0;
	MPU9250_Write_Byte(MPU_ADDR,MPU_INTBP_CFG_REG,0x02);
	delay_ms(10);	
	MPU9250_Write_Byte(MAG_ADDRESS,AKM8963_CNTL1_REG,0x01);
	delay_ms(10);
  id=MPU9250_Read_Byte(MPU_ADDR,AKM8963_DEVICE_ID_REG);
	if(id  == 0x48)
	{
		return  MPU9250_OK;
	}
	else
	{
		return  MPU9250_FAIL;
	}	
}
//=========================================================================================
//*******************************MPU9250各轴数据********************************************
//=========================================================================================
//-------------------------------------------------------------------------MPU9250 温度函数
MPU9250_STATUS MPU9250_Get_Temperature(float *temp)
{
	u8 buf[2];
	short raw;
	MPU9250_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf);
	raw=(buf[0]<<8)|buf[1];
	//temp=36.53+((double)raw)/340;
	*temp=21+((double)raw)/333.87;
	return MPU9250_OK;
}
//-------------------------------------------------------------------------MPU9250 陀螺仪函数
MPU9250_STATUS MPU9250_Get_Gyroscope(short *gx,short *gy,short *gz)
{
	u8 buf[6];
	if(MPU9250_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf))
	{
		return MPU9250_FAIL;
	}
	else
	{
		*gx=((u16)buf[0]<<8)|buf[1];
		*gy=((u16)buf[2]<<8)|buf[3];
		*gz=((u16)buf[4]<<8)|buf[5];
	}
	return MPU9250_OK;
}
//-------------------------------------------------------------------------MPU9250 加速度计函数
MPU9250_STATUS MPU9250_Get_Accelerometer(short *ax,short *ay,short *az)
{
	u8  buf[6];
	if(MPU9250_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf))
	{
		return MPU9250_FAIL;
	}
	else
	{
		*ax=((u16)buf[0]<<8)|buf[1];
		*ay=((u16)buf[2]<<8)|buf[3];
		*az=((u16)buf[4]<<8)|buf[5];
	}
	return MPU9250_OK;
}
//-------------------------------------------------------------------------MPU9250 磁力计函数
MPU9250_STATUS MPU9250_Get_Mag(short *mx,short *my,short *mz)
{
	u8 buf[6];
	MPU9250_Write_Byte(MPU_ADDR,MPU_INTBP_CFG_REG,0x02);
	delay_ms(10);
	MPU9250_Write_Byte(MAG_ADDRESS,AKM8963_CNTL1_REG,0x01);
	delay_ms(10);
	if(MPU9250_Read_Len(MAG_ADDRESS,AKM8963_MAG_XOUTL_REG,6,buf))
	{
		return MPU9250_FAIL;
	}
	else
	{
		*mx=((u16)buf[1]<<8)|buf[0];
		*my=((u16)buf[3]<<8)|buf[2];
		*mz=((u16)buf[5]<<8)|buf[4];
	}
	return MPU9250_OK;
}

//=========================================================================================
//*******************************MPU6050设置***********************************************
//=========================================================================================
//-------------------------------------------------------------------------MPU9250 陀螺仪范围设置函数
MPU9250_STATUS MPU9250_Set_Gyro(u8 fsr)	//0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
{
	return MPU9250_Write_Byte(MPU_ADDR,MPU_GYRO_CFG_REG,fsr<<3); //根据写函数 返回0成功
}
//-------------------------------------------------------------------------MPU9250 加速度计范围设置函数
MPU9250_STATUS MPU9250_Set_Accel(u8 fsr) //0,±2g;1,±4g;2,±8g;3,±16g
{
	return MPU9250_Write_Byte(MPU_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}
//-------------------------------------------------------------------------MPU9250 设置数字低通滤波器
MPU9250_STATUS MPU9250_Set_LPF(u8 lpf)
{
	u8 data=0;
	if(lpf>184)			data=1;
	else if(lpf>92) data=2;
	else if(lpf>41) data=3;
	else if(lpf>20) data=4;
	else if(lpf>10) data=5;
	else 						data=6;
	return MPU9250_Write_Byte(MPU_ADDR,MPU_CFG_REG,data);
}
//-------------------------------------------------------------------------MPU9250 采样频率设置函数
MPU9250_STATUS MPU9250_Set_Rate(u16 rate)
{
	u8 data=0;
	if(rate>1000) rate=1000;
	if(rate<4) 		rate=4;
	data=1000/rate-1;
	data=MPU9250_Write_Byte(MPU_ADDR,MPU_SAMPLE_RATE_REG,data);
	return MPU9250_Set_LPF(rate/2);      //**自动设置数字低通滤波为采样频率的一半
}
//=========================================================================================
//*******************************MPU9250 IIC函数*******************************************
//=========================================================================================
//-------------------------------------------------------------------------MPU9250连续读函数
// addr MPU9250地址
// reg  MPU9250寄存器地址
// len  读取长度
// *buf 数据存储区
MPU9250_STATUS MPU9250_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	I2C_Start();
	I2C_SendByte(addr);
	if(I2C_WaitAck())
	{
		I2C_Stop();
		return MPU9250_FAIL;
	}
	I2C_SendByte(reg);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(addr+1);
	I2C_WaitAck();
	while(len)
	{
		if(len == 1)//len=1表示只读取一个寄存器
		{
			*buf = I2C_ReadByte(0);//读取一个字节并回发NACK
		}
		else
		{
			*buf = I2C_ReadByte(1);//读取一个字节并回发ACK
		}		
		buf++;
		len--;
	}
	I2C_Stop();
	return MPU9250_OK;
}

//-------------------------------------------------------------------------MPU9250连续写函数
MPU9250_STATUS MPU9250_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i=0;
	I2C_Start();
	I2C_SendByte(addr);
	if(I2C_WaitAck())
	{	
		I2C_Stop();
		return MPU9250_FAIL;	
	}
	I2C_SendByte(reg);
	I2C_WaitAck();
	for(i=0;i<len;i++)
	{
		I2C_SendByte(buf[i]);
		if(I2C_WaitAck())
		{	
			I2C_Stop();
			return MPU9250_FAIL;	
		}	
	}
	I2C_Stop();
	return MPU9250_OK;
}

//==========================================================================================
//-------------------------------------------------------------------------MPU9250读一字节函数
u8 MPU9250_Read_Byte(u8 addr,u8 reg)
{
	u8 Return;
	I2C_Start();
	I2C_SendByte(addr);
	I2C_WaitAck();
	I2C_SendByte(reg);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(addr+1);
	I2C_WaitAck();
	Return=I2C_ReadByte(0);//读取数据
	I2C_Stop();		
	return Return;
}
//-------------------------------------------------------------------------MPU6050写一字节函数
MPU9250_STATUS MPU9250_Write_Byte(u8 addr,u8 reg,u8 data)
{
	I2C_Start();
	I2C_SendByte(addr);
	if(I2C_WaitAck())
	{
		I2C_Stop();
		return MPU9250_FAIL;		
	}
	I2C_SendByte(reg);
	I2C_WaitAck();
	I2C_SendByte(data); //发送数据
	if(I2C_WaitAck())
	{
		I2C_Stop();
		return MPU9250_FAIL;			
	}
	I2C_Stop();
	return MPU9250_OK;
}
void IMU_Update(void)
{
  float PRY[3];//欧拉角
	short  APRY[3];//角速度：1s n度*16.4
	static int count,flag;
	
	static float	yaw_temp,last_yaw_temp;
	if(flag>500)   //大概6S,防止SB
	{
		 flag=0;
		 mpu_set_dmp_state(0);
		 mpu_set_dmp_state(1);
	}
	if( mpu_mpl_get_data(&PRY[0],&PRY[1],&PRY[2],APRY)==0)
	{
		
		 MPU6050_Real_Data.Gyro_X  =  (float)(APRY[0]/16.4f);  //转成度每秒，这里已经将量程改成了 1000度每秒  16.4 对应 1度每秒
		 MPU6050_Real_Data.Gyro_Y  =  (float)(APRY[1]/16.4f);
		 MPU6050_Real_Data.Gyro_Z  =  (float)(APRY[2]/16.4f);;
		
		 last_yaw_temp = yaw_temp;
		 yaw_temp = PRY[2];
	//if(yaw_ready==1)
	//{
		 if(yaw_temp-last_yaw_temp>=330)  //yaw轴角度经过处理后变成连续的
		 {
				count--;
		 }
		 else if (yaw_temp-last_yaw_temp<=-330)
		 {
				count++;
		 }
			yaw_angle = PRY[2] + count*360;  //yaw轴角度
	// }
			pitch_angle =  PRY[0];
			roll_angle  =  PRY[1];
	 
  }
}
