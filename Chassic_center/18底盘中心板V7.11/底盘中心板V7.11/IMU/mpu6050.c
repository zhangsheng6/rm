#include "mpu6050.h"
#include "mydelay.h"
#include "inv_mpu.h"
#include "mpu6050_interrupt.h"
#include "math.h"
MPU6050_REAL_DATA   MPU6050_Real_Data;
MPU6050_OFFEST_DATA  MPU6050_Offest_Data;
float   yaw_angle,pitch_angle,roll_angle; //ʹ�õ��ĽǶ�ֵ

//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Init(void)
{
	u8 res;
	MPU6050_Offest_Data.offest_flag=1;
	MPU_IIC_Init();//��ʼ��IIC����
	MPU6050_IntConfiguration();
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
  delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);							//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	while(mpu_dmp_init())
	{
	
	}	
	return 0;
}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
  MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		MPU_IIC_Send_Byte(buf[i]);	//��������
		if(MPU_IIC_Wait_Ack())		//�ȴ�ACK
		{
			MPU_IIC_Stop();	 
			return 1;		 
		}		
	}    
    MPU_IIC_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=MPU_IIC_Read_Byte(0);//������,����nACK 
		else *buf=MPU_IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    MPU_IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
  MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	MPU_IIC_Send_Byte(data);//��������
	if(MPU_IIC_Wait_Ack())	//�ȴ�ACK
	{
		MPU_IIC_Stop();	 
		return 1;		 
	}		 
    MPU_IIC_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
  MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
  MPU_IIC_Start();
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|1);//����������ַ+������	
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=MPU_IIC_Read_Byte(0);//��ȡ����,����nACK 
  MPU_IIC_Stop();			//����һ��ֹͣ���� 
	return res;		
}

void IMU_Update(void)
{
	float PRY[3];
	short  APRY[3];  //���ٶ�
	short  GPRY[3];  //���ٶ�
	float  data1,data2,data3;
	static int count;
	static float	yaw_temp,last_yaw_temp;
	
	if(mpu_dmp_get_data(&PRY[0],&PRY[1],&PRY[2])==0)
	{
		
		 MPU_Get_Accelerometer(&APRY[0],&APRY[1],&APRY[2]);	//�õ����ٶȴ���������
		 MPU_Get_Gyroscope(&GPRY[0],&GPRY[1],&GPRY[2]);	//�õ�����������
		 if(MPU6050_Offest_Data.offest_flag)
		 {
		    MPU6050_Offest_Data.offest_flag=0;

        MPU6050_Offest_Data.garo_X_offest=GPRY[0];
			  MPU6050_Offest_Data.garo_Y_offest=GPRY[1];
			  MPU6050_Offest_Data.garo_Z_offest=GPRY[2];
			  MPU6050_Offest_Data.pitch_offest=PRY[0];
			  MPU6050_Offest_Data.roll_offest=PRY[1];
			  MPU6050_Offest_Data.yaw_offest=PRY[2];
			 
		 }
		 //���ٶ�����ת��
     MPU6050_Real_Data.Accel_X=(float)(APRY[0]*0.005981f);   //ת�ɷ���ÿ��  
		 MPU6050_Real_Data.Accel_Y=(float)(APRY[1]*0.005981f);
		 MPU6050_Real_Data.Accel_Z=(float)(APRY[2]*0.005981f);
		 
		 data1=fabs( MPU6050_Real_Data.Accel_X);
		 data2=fabs( MPU6050_Real_Data.Accel_Y);
		 
		 data3=((MPU6050_Real_Data.Accel_X>0)?pow(data1,2):-pow(data1,2))+((MPU6050_Real_Data.Accel_Y>0)?pow(data2,2):-pow(data2,2));		 
		 data3=fabs(data3);
		 MPU6050_Real_Data.Accel=sqrt(data3);
		 
		 
		 //���ٶ�����ת��
		 MPU6050_Real_Data.Gyro_X  =  (float)((GPRY[0]-MPU6050_Offest_Data.garo_X_offest)/16.4f);  //ת�ɶ�ÿ�룬�����Ѿ������̸ĳ��� 1000��ÿ��  16.4 ��Ӧ 1��ÿ��
		 MPU6050_Real_Data.Gyro_Y  =  (float)((GPRY[1]-MPU6050_Offest_Data.garo_Y_offest)/16.4f);
		 MPU6050_Real_Data.Gyro_Z  =  (float)((GPRY[2]-MPU6050_Offest_Data.garo_Z_offest)/16.4f);
		
		 last_yaw_temp = yaw_temp;
		 yaw_temp = PRY[2]-MPU6050_Offest_Data.yaw_offest;
		 if(yaw_temp-last_yaw_temp>=330)  //yaw��ǶȾ����������������
		 {
				count--;
		 }
		 else if (yaw_temp-last_yaw_temp<=-330)
		 {
				count++;
		 }
			yaw_angle = PRY[2] + count*360;  //yaw��Ƕ�
			pitch_angle =  PRY[0]-MPU6050_Offest_Data.pitch_offest;
			roll_angle  =  PRY[1]-MPU6050_Offest_Data.roll_offest;
  }
	else
	{
	}
}
