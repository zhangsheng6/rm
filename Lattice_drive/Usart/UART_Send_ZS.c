#include "UART_Send_ZS.h"

extern u8	 Shot_Flag_OK;

//发送一个字节----------------------------------------------------------
void UART_Send_Byte_ZS(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx, (u8)ch);//发送一个字节(8位)的数据：0-255，收到的是ASCLL值
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}


//发送一个字节数组----------------------------------------------------------
void UART_Send_ByteArray_ZS(USART_TypeDef* USARTx, u8 *ch, u32 len) //int8  int32
{
  while(len--)
  {
    UART_PutChar(USARTx, *(ch++));	
  }
}

void xingxing(void)
{
	
	for(u8 i=0;i<2;i++)
  UART_Send_Byte_ZS(UART4,42);//ASCLL:45对应*
}

void jiange_(void)
{
	
	for(u8 i=0;i<2;i++)
  UART_Send_Byte_ZS(UART4,45);//ASCLL:45对应-
}



//发送回车------------------------------------------------------------------------------------------
void UART_Send_Enter_ZS(void)
{
	/*
回车 CR  -   \r  -  0x0d   - 移动光标至该行的起始位置
换行 LF  -   \n  -  0x0a   - 换行至下一行行首起始位置
 */
	 UART_Send_Byte_ZS(UART4, 0x0d);//返回行首
	 UART_Send_Byte_ZS(UART4, 0x0a);//转行
}


//数字->ACSII值，UART输出ASCII值------------------------------------------------------------
void HEXACSII_ZS(u16 hex, u8* Print)
{
/*
十进制数字：.   0    
ASCII值   ：46  48
eg：将28转换成要发送的ASCII值，储存在Print结构体里，
Print[6]储存8的ASCII值
Print[5]储存2的ASCII值
Print[4-0]储存0的ASCII值
*/
	u8 hexcheck ;
	u8 TEMP ;
	TEMP = 6 ;
	Print[TEMP ]='\0';
	while(TEMP)
	{
	  	TEMP -- ;
	  	hexcheck  =  hex%10 ;
	  	hex   /=10 ;
	  	Print[TEMP ]  = hexcheck + 0x30 ;//+48
	}
}



//发送u16(无符号2^16)数字------------------------------------------------------------
void UART_Send_Uint16_ZS(u16 num, u8 enter)
{
	u8 *ch1,ch[7], m[7];
  u32 i = 0;

    if (num == 0)
    {
        m[0] = '0';
        m[1] = '\0';
    }
    else
	{
        HEXACSII_ZS(num,ch);
        ch1 =&ch[1];//6位二进制
        while (*ch1 == '0')
        {
            ch1++;
        }
        for (i=0; *ch1 != '\0'; i++)
        {
            m[i] = *ch1;
            ch1++;
        }
        m[i] = '\0';
    }

  UART_Send_ByteArray_ZS(UART4,m, i+1); //显示一串数字

    if (enter)
    {
        UART_Send_Enter_ZS();
    }
}



//UART发送 有符号数 (-32768 ~ 32767)---------------------------
void UART_Send_Int16_ZS(int16_t num, u8 enter)
{
	if (num < 0)
    {
        num = -num;
			 UART_Send_Byte_ZS(UART4,'-');

    }
    UART_Send_Uint16_ZS(num, 0);

    if (enter)
    {
        UART_Send_Enter_ZS();
    }
}






//float,此函数只保留了3位精度 范围 -3.40E+38 ~ 3.40E+38
void UART_SendFloat_ZS(float data, u8 enter)
{
/*   
整数大小不能超过uint32，小数注意精度
*/
    u8 temp = 3;//小数显示位数
    u32 integer;//存储整数
    float decimals;//存储小数
    u8 decimalsInterger;//小数转换为整数

    if (data < 0)
    {
        data = -data;
				 UART_Send_Byte_ZS(UART4, '-');
    }

    integer = (u32)data;
    decimals = data - (float)integer;

    //发送整数
    if (data > 9999)
    {
			 UART_Send_Uint16_ZS(integer/10000, 0);
    }
		
			 UART_Send_Uint16_ZS(integer%10000, 0); 

    //发送小数
			UART_Send_Byte_ZS(UART4, '.');//转行
    while (temp)
    {
        temp --;
        decimals *= 10;
        decimalsInterger = (u8)decimals + 0x30;
				UART_Send_Byte_ZS(UART4, (char)decimalsInterger);//转行
        decimals = decimals - (float)(decimalsInterger-0x30);
    }

    if (enter)
    {
        UART_Send_Enter_ZS();
    }
}

void UART_Data_Learn_ZS(void)
{
	static u16 Count_Send=0;
	if(Count_Send++>50)
	{
		Count_Send=0;

		
/*
  UART_Send_Int16_ZS(RC_CtrlData.ch0, 1);
  UART_Send_Int16_ZS(RC_CtrlData.ch1, 1);
  UART_Send_Int16_ZS(RC_CtrlData.ch2, 1);
  UART_Send_Int16_ZS(RC_CtrlData.ch3, 1);
*/

//编码器数据,底盘------------------------------------------------------------------------------------
	/*	
		 UART_Send_Int16_ZS(CM1Encoder.filter_rate, 1);//平均原始速度
		UART_Send_Int16_ZS(CM2Encoder.filter_rate, 1);//平均原始速度
		 UART_Send_Int16_ZS(CM3Encoder.filter_rate, 1);//平均原始速度
		 UART_Send_Int16_ZS(CM4Encoder.filter_rate, 1);//平均原始速度
		 UART_Send_Enter_ZS();
*/
		
/*编码器数据  4193 3606 ------------------------------------------------------------------*/
//前进，23编码器速度为正，14为负		
//	  UART_Send_Int16_ZS(CM1Encoder.ecd_bias, 1);//初始偏差  
//	  UART_Send_Int16_ZS(CM2Encoder.ecd_bias, 1);//初始偏差  
//	  UART_Send_Int16_ZS(CM3Encoder.ecd_bias, 1);//初始偏差  
//	  UART_Send_Int16_ZS(CM4Encoder.ecd_bias, 1);//初始偏差  
/*		
   UART_Send_Int16_ZS(CM1Encoder.raw_value, 1);//返回原始值 正转-多到少
//	 UART_Send_Byte_ZS(UART4,61);//-0
   UART_Send_Int16_ZS(CM2Encoder.raw_value, 1);//返回原始值 正转-多到少
//	 UART_Send_Byte_ZS(UART4,61);//-0
  UART_Send_Int16_ZS(CM3Encoder.raw_value, 1);//返回原始值 正转-多到少
//	 UART_Send_Byte_ZS(UART4,61);//-0
   UART_Send_Int16_ZS(CM4Encoder.raw_value, 1);//返回原始值 正转-多到少
	*/	
//	  UART_Send_Int16_ZS(CM1Encoder.ecd_raw_rate, 0);//原始速度  959
//		UART_Send_Byte_ZS(UART4,61);//-0
//		UART_Send_Int16_ZS(CM2Encoder.ecd_raw_rate, 0);//原始速度  959
//		UART_Send_Byte_ZS(UART4,61);//-0 
//		UART_Send_Int16_ZS(CM3Encoder.ecd_raw_rate, 0);//原始速度  959
//		UART_Send_Byte_ZS(UART4,61);//-0
//		UART_Send_Int16_ZS(CM4Encoder.ecd_raw_rate, 1);//原始速度  959

//		 UART_Send_Int16_ZS(CM1Encoder.filter_rate, 0);//平均原始速度
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM2Encoder.filter_rate, 0);//平均原始速度
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM3Encoder.filter_rate, 0);//平均原始速度
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM4Encoder.filter_rate, 1);//平均原始速度

//		 UART_Send_Int16_ZS(CM2Encoder.ecd_value, 0	 );//原始值累加输出
//		 UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM2Encoder.ecd_angle, 1);//相对角度，每转1圈+360度


/*
静止：0不变  100-300多变化   22不变
操作：最大+4000多，-6000多，  电流就方向变化正确，电流值变化一直变，没啥用
      温度操作21-23，基本不变
*/
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_zhuansu, 0	 );//原始值累加输出
//	 UART_Send_Byte_ZS(UART4,61);//-0
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_dianliu, 0	 );//原始值累加输出
//	 UART_Send_Byte_ZS(UART4,61);//-0
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_wendu, 1);//相对角度，每转1圈+360度



	// UART_Send_Int16_ZS(GMPokeSpeedPID.pid_out, 1);//炮口输出

/*



*/

//测试9250欧拉角---------------------------------------------------------------------------------
  /*
	//这就是为啥云台控制Y轴角度环用yaw角，而P轴控制的角度环用编码器角度，不用pitch角
	//因为yaw叫变化范围大，控制精确可以用，而pitch角变化范围不到5度，，控制不精确，不好用
	 UART_SendFloat_ZS(yaw_angle, 0);/-129到90度
	 		 xingxing();
	 UART_SendFloat_ZS(pitch_angle, 0);//-2到3度变化，
	 		 xingxing();
	 UART_SendFloat_ZS(roll_angle,1);
  */

//测试：云台控制：电机+9250+遥控右杆设定角度---------------------------------------------------
//只需修改编码器初始偏差值即可

/*
UART_SendFloat_ZS(yaw_angle, 0);//云台控制外环角度
   	 		 xingxing();	
UART_SendFloat_ZS(GMYawEncoder.ecd_angle , 0);//外环角度实际值：编码器角度累积
   	 		 xingxing();	
  UART_SendFloat_ZS(GimbalRef.yaw_angle_dynamic_ref ,1);//外环角度实际值：编码器角度
*/

/*
UART_Send_Int16_ZS( -GMYawEncoder.raw_value, 0	 );//Y轴编码器原始输出值：确定初始偏差值2157
  	 		 xingxing();	
UART_SendFloat_ZS(-GMYawEncoder.ecd_angle , 0);//外环角度实际值：编码器角度累积
 	 		 xingxing();
 UART_Send_Int16_ZS( -MPU6050_Real_Data.Gyro_Z, 1	 );//内环角速度实际值，云台往右正
 
UART_Send_Int16_ZS( GMPitchEncoder.raw_value, 0	);//内环角速度实际值  1280
   	 		 xingxing();	
 UART_SendFloat_ZS(-GMPitchEncoder.ecd_angle , 0);//外环角度实际值：编码器角度
   	 		 xingxing();	//低头13度，抬头-31度
 UART_Send_Int16_ZS( -MPU6050_Real_Data.Gyro_X, 1	 );//内环角速度实际值 云台往下正

  UART_SendFloat_ZS(GimbalRef.yaw_angle_dynamic_ref ,0);//外环角度实际值：编码器角度
	   	 		 xingxing();	
  UART_SendFloat_ZS(GimbalRef.pitch_angle_dynamic_ref  ,1);//外环角度实际值：编码器角度
                   //往上拨-
*/
//测试：炮口电机------------------------------------------------------------------------------------------------------------
  /*
 UART_Send_Int16_ZS( GMPokeEncoder.ecd_bias, 0	 );//内环角速度实际值
   xingxing();	
 UART_Send_Int16_ZS( GMPokeEncoder.raw_value, 0 );//炮口编码器原始值
  xingxing();	
 UART_Send_Int16_ZS( GMPokeEncoder.ecd_angle, 1 );//炮口编码器原始值1451  3715   5669 8134

// UART_Send_Int16_ZS( Shot_Flag, 0 );//
 // xingxing();	
	//UART_Send_Int16_ZS( Shot_Flag_OK, 0 );//
//  xingxing();	
 UART_Send_Int16_ZS(  GMPokePositionPID.ref, 0	 );//
   xingxing();	
 UART_Send_Int16_ZS( GMPokePositionPID.fdb , 1 );//
 //  */
//测试：底盘6050------------------------------------------------------------------------------------------------------------
 /*
//  底盘6050：陀螺仪角速度：顺时钟旋转-150，逆时针旋转+150
  UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 0 );
   xingxing();	
 //  底盘6050：以下俩个为重力加速度和欧拉角，用来测量上坡，上坡后有几十的角度，板子垂直90度
	 UART_Send_Int16_ZS( ChassisCenter.Accel, 0 );//
   xingxing();
	 UART_Send_Int16_ZS( ChassisCenter.roll_angle, 1 );//
   xingxing();	
  */
	//车向右，角速度负，旋转设定值正	
//  UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 0 );
 //  xingxing();	
 //  底盘6050：以下俩个为重力加速度和欧拉角，用来测量上坡，上坡后有几十的角度，板子垂直90度
//	 UART_Send_Int16_ZS( ChassisCenter.Accel, 0 );//
  // xingxing();
	// UART_Send_Int16_ZS( ChassisCenter.roll_angle, 1 );//

	//	 UART_Send_Int16_ZS(ChassisSpeedRef.rotate_ref	 , 1);//平均原始速度


	 //UART_Send_Int16_ZS( ChassisCenter.CompareState, 1 );//
//	 UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 1 );//
//	 UART_Send_Enter_ZS(); 


//测试：底盘ina260------------------------------------------------------------------------------------------------------------

/*

静止
电压 23.1
电流 0.126
功率  3

最大
22.5
2.5
50

*/	 

/*
静止
功率3
电流设定值 0
电流实际值 128

动
功率          6.5 
电流设定值    665
电流实际值    285

功率					14
电流设定值 		201
电流实际值    665

功率        9.5
电流设定值  161
电流实际值  421

功率         54
电流设定值   318
电流实际值   2428

23.520
365**1040

29.969
378**1328

36.470
502**1652

42.909
275**1915

49.470
329**2217

62.299
562**2810

*/



/*
UART_SendFloat_ZS(ChassisCenter.Voltage, 0 );
   xingxing();	
UART_SendFloat_ZS(ChassisCenter.Current, 0 );
   xingxing();
	 */
	 
	   //UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 0 );
	//   UART_Send_Int16_ZS( MPU6050_Real_Data.Gyro_X, 0 );
//   xingxing();

UART_SendFloat_ZS(ChassisCenter.Power, 1 );
//UART_SendFloat_ZS(Real_JudgeMent.Power, 1 );
UART_Send_Enter_ZS();

   //UART_Send_Int16_ZS(GMYawEncoder.raw_value, 1);//返回原始值 正转-多到少


/*

	 UART_Send_Int16_ZS( ChassisCurrentPID.ref, 0 );//
	    xingxing();	
	// UART_Send_Int16_ZS( ChassisCurrentPID.fdb, 1 );// ChassisCenter.Current*1000
	 UART_Send_Int16_ZS( ChassisCenter.Current*1000, 1);// 
	 
 
	 UART_Send_Int16_ZS( CM1Encoder.encoder_dianliu, 0 );// 
	 	  xingxing();
			UART_Send_Int16_ZS( CM1Encoder.encoder_dianliu, 0 );// 
	 	  xingxing();		
			UART_Send_Int16_ZS( CM1Encoder.encoder_dianliu, 0 );// 
	 	  xingxing();		
			UART_Send_Int16_ZS( CM1Encoder.encoder_dianliu, 1 );// 


UART_Send_Enter_ZS();*/

/*
taitou  -26   27
静止 电流
+-100内





静止：
设定电流，实际电流：
0,130     0A,0.13A
偏差 -130， PID电流输出-1300，会把电机本该的转向搞反，所以必须限制电流环输出最小为0，一定不能为负


空载低速
900**237     1.1A   0.237A
偏差： 650     ，   会让电流输出很大，错误

空载高速
1350  1939    1.65A,   1.939A

空载最高
1170**2585    1.43A,2.585A
1200**2287    1.46A,
1020**2447    1.24


地上

3990**832  
16000**3496     19.5A   
9480**2830
9800**5516
16000**4071    
16000**8825
*/

/*	

//


	UART_Send_Int16_ZS( ChassisCenter.Voltage, 0 );//
   xingxing();	
	 UART_Send_Int16_ZS( ChassisCenter.Current, 0 );//
   xingxing();
	 UART_Send_Int16_ZS( ChassisCenter.Power, 0 );//
   xingxing();	 
	 //UART_Send_Int16_ZS( ChassisCenter.CompareState, 1 );//
	 UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 1 );//
	 UART_Send_Enter_ZS();
	 */
	/*
规则：步兵底盘功率限制：80W,供电电压30V

电压  电流  功率  
23     0     2     
22     2     52
21     5      48
23     0	    62
22900 126  290
22350 1900 4500

底盘电机运动越来越剧烈，电机 电压降低，电流增大，功率增大
状态 0：（IO输入口低电平）超级电容没电	
状态 1：（IO输入口高电平）超级电容有电	
	*/
	/*
	 UART_Send_Int16_ZS( ChassisCenter.Voltage, 0 );//
   xingxing();	
	 UART_Send_Int16_ZS( ChassisCenter.Current, 0 );//
   xingxing();
	 UART_Send_Int16_ZS( ChassisCenter.Power, 0 );//
   xingxing();	 
	 UART_Send_Int16_ZS( ChassisCenter.CompareState, 1 );//
	 UART_Send_Enter_ZS();
	
	 */
	}

}

 
//P轴配对：初学------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
/*
//抬头最高时555，中间0，低头最低时7618，
 //UART_Send_Int16_ZS( GMPitchEncoder.raw_value, 1	 );//内环角速度实际值
// 抬头0度，低头-50度
//UART_SendFloat_ZS(GMPitchEncoder.ecd_angle , 0);//外环角度实际值：编码器角度
 	// 		 xingxing();			 
// UART_SendFloat_ZS(pitch_angle, 1);//抬头 1度，低头3度
 	 	//	 xingxing();
//拿手摆动，抬头快+200，低头-200
// UART_Send_Int16_ZS( MPU6050_Real_Data.Gyro_X, 1	 );//内环角速度实际值
	//    GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle;
	
//UART_SendFloat_ZS(GMPitchEncoder.ecd_angle , 0);//外环角度实际值：编码器角度
 //	 		 xingxing();
//UART_SendFloat_ZS(GMPPositionPID.fdb , 0);//外环角度实际值：编码器角度
 //	 		 xingxing();
//UART_Send_Int16_ZS( GMPPositionPID.ref, 1	 );//内环角速度实际值
//遥控控制最后值  0到35
*/

/*
遥控向前拨，遥控角度35度，角度实际值25
遥控向后拨，遥控角度0度， 角度实际值0
*/
//Y轴配对：初学------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
/*
UART_SendFloat_ZS(GMYawEncoder.ecd_angle , 0);//外环角度实际值：编码器角度
 	 		 xingxing();
UART_SendFloat_ZS(yaw_angle, 0);//抬头 1度，低头3度
 	 		 xingxing();
 UART_Send_Int16_ZS( MPU6050_Real_Data.Gyro_Z, 1	 );//内环角速度实际值，往右负
  	 		 xingxing();
 UART_Send_Int16_ZS( GMYawEncoder.raw_value, 0	 );//内环角速度实际值
  	 		 xingxing();		 
 UART_Send_Int16_ZS( GMYawEncoder.ecd_bias, 1	 );//内环角速度实际值，初始偏差
*/







