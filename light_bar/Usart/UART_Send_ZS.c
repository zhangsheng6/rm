#include "UART_Send_ZS.h"

extern u8	 Shot_Flag_OK;

//����һ���ֽ�----------------------------------------------------------
void UART_Send_Byte_ZS(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx, (u8)ch);//����һ���ֽ�(8λ)�����ݣ�0-255���յ�����ASCLLֵ
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}


//����һ���ֽ�����----------------------------------------------------------
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
  UART_Send_Byte_ZS(UART4,42);//ASCLL:45��Ӧ*
}

void jiange_(void)
{
	
	for(u8 i=0;i<2;i++)
  UART_Send_Byte_ZS(UART4,45);//ASCLL:45��Ӧ-
}



//���ͻس�------------------------------------------------------------------------------------------
void UART_Send_Enter_ZS(void)
{
	/*
�س� CR  -   \r  -  0x0d   - �ƶ���������е���ʼλ��
���� LF  -   \n  -  0x0a   - ��������һ��������ʼλ��
 */
	 UART_Send_Byte_ZS(UART4, 0x0d);//��������
	 UART_Send_Byte_ZS(UART4, 0x0a);//ת��
}


//����->ACSIIֵ��UART���ASCIIֵ------------------------------------------------------------
void HEXACSII_ZS(u16 hex, u8* Print)
{
/*
ʮ�������֣�.   0    
ASCIIֵ   ��46  48
eg����28ת����Ҫ���͵�ASCIIֵ��������Print�ṹ���
Print[6]����8��ASCIIֵ
Print[5]����2��ASCIIֵ
Print[4-0]����0��ASCIIֵ
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



//����u16(�޷���2^16)����------------------------------------------------------------
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
        ch1 =&ch[1];//6λ������
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

  UART_Send_ByteArray_ZS(UART4,m, i+1); //��ʾһ������

    if (enter)
    {
        UART_Send_Enter_ZS();
    }
}



//UART���� �з����� (-32768 ~ 32767)---------------------------
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






//float,�˺���ֻ������3λ���� ��Χ -3.40E+38 ~ 3.40E+38
void UART_SendFloat_ZS(float data, u8 enter)
{
/*   
������С���ܳ���uint32��С��ע�⾫��
*/
    u8 temp = 3;//С����ʾλ��
    u32 integer;//�洢����
    float decimals;//�洢С��
    u8 decimalsInterger;//С��ת��Ϊ����

    if (data < 0)
    {
        data = -data;
				 UART_Send_Byte_ZS(UART4, '-');
    }

    integer = (u32)data;
    decimals = data - (float)integer;

    //��������
    if (data > 9999)
    {
			 UART_Send_Uint16_ZS(integer/10000, 0);
    }
		
			 UART_Send_Uint16_ZS(integer%10000, 0); 

    //����С��
			UART_Send_Byte_ZS(UART4, '.');//ת��
    while (temp)
    {
        temp --;
        decimals *= 10;
        decimalsInterger = (u8)decimals + 0x30;
				UART_Send_Byte_ZS(UART4, (char)decimalsInterger);//ת��
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

//����������,����------------------------------------------------------------------------------------
	/*	
		 UART_Send_Int16_ZS(CM1Encoder.filter_rate, 1);//ƽ��ԭʼ�ٶ�
		UART_Send_Int16_ZS(CM2Encoder.filter_rate, 1);//ƽ��ԭʼ�ٶ�
		 UART_Send_Int16_ZS(CM3Encoder.filter_rate, 1);//ƽ��ԭʼ�ٶ�
		 UART_Send_Int16_ZS(CM4Encoder.filter_rate, 1);//ƽ��ԭʼ�ٶ�
		 UART_Send_Enter_ZS();
*/
		
/*����������  4193 3606 ------------------------------------------------------------------*/
//ǰ����23�������ٶ�Ϊ����14Ϊ��		
//	  UART_Send_Int16_ZS(CM1Encoder.ecd_bias, 1);//��ʼƫ��  
//	  UART_Send_Int16_ZS(CM2Encoder.ecd_bias, 1);//��ʼƫ��  
//	  UART_Send_Int16_ZS(CM3Encoder.ecd_bias, 1);//��ʼƫ��  
//	  UART_Send_Int16_ZS(CM4Encoder.ecd_bias, 1);//��ʼƫ��  
/*		
   UART_Send_Int16_ZS(CM1Encoder.raw_value, 1);//����ԭʼֵ ��ת-�ൽ��
//	 UART_Send_Byte_ZS(UART4,61);//-0
   UART_Send_Int16_ZS(CM2Encoder.raw_value, 1);//����ԭʼֵ ��ת-�ൽ��
//	 UART_Send_Byte_ZS(UART4,61);//-0
  UART_Send_Int16_ZS(CM3Encoder.raw_value, 1);//����ԭʼֵ ��ת-�ൽ��
//	 UART_Send_Byte_ZS(UART4,61);//-0
   UART_Send_Int16_ZS(CM4Encoder.raw_value, 1);//����ԭʼֵ ��ת-�ൽ��
	*/	
//	  UART_Send_Int16_ZS(CM1Encoder.ecd_raw_rate, 0);//ԭʼ�ٶ�  959
//		UART_Send_Byte_ZS(UART4,61);//-0
//		UART_Send_Int16_ZS(CM2Encoder.ecd_raw_rate, 0);//ԭʼ�ٶ�  959
//		UART_Send_Byte_ZS(UART4,61);//-0 
//		UART_Send_Int16_ZS(CM3Encoder.ecd_raw_rate, 0);//ԭʼ�ٶ�  959
//		UART_Send_Byte_ZS(UART4,61);//-0
//		UART_Send_Int16_ZS(CM4Encoder.ecd_raw_rate, 1);//ԭʼ�ٶ�  959

//		 UART_Send_Int16_ZS(CM1Encoder.filter_rate, 0);//ƽ��ԭʼ�ٶ�
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM2Encoder.filter_rate, 0);//ƽ��ԭʼ�ٶ�
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM3Encoder.filter_rate, 0);//ƽ��ԭʼ�ٶ�
//	   UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM4Encoder.filter_rate, 1);//ƽ��ԭʼ�ٶ�

//		 UART_Send_Int16_ZS(CM2Encoder.ecd_value, 0	 );//ԭʼֵ�ۼ����
//		 UART_Send_Byte_ZS(UART4,61);//-0
//		 UART_Send_Int16_ZS(CM2Encoder.ecd_angle, 1);//��ԽǶȣ�ÿת1Ȧ+360��


/*
��ֹ��0����  100-300��仯   22����
���������+4000�࣬-6000�࣬  �����ͷ���仯��ȷ������ֵ�仯һֱ�䣬ûɶ��
      �¶Ȳ���21-23����������
*/
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_zhuansu, 0	 );//ԭʼֵ�ۼ����
//	 UART_Send_Byte_ZS(UART4,61);//-0
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_dianliu, 0	 );//ԭʼֵ�ۼ����
//	 UART_Send_Byte_ZS(UART4,61);//-0
//	 UART_Send_Int16_ZS(CM2Encoder.encoder_wendu, 1);//��ԽǶȣ�ÿת1Ȧ+360��



	// UART_Send_Int16_ZS(GMPokeSpeedPID.pid_out, 1);//�ڿ����

/*



*/

//����9250ŷ����---------------------------------------------------------------------------------
  /*
	//�����Ϊɶ��̨����Y��ǶȻ���yaw�ǣ���P����ƵĽǶȻ��ñ������Ƕȣ�����pitch��
	//��Ϊyaw�б仯��Χ�󣬿��ƾ�ȷ�����ã���pitch�Ǳ仯��Χ����5�ȣ������Ʋ���ȷ��������
	 UART_SendFloat_ZS(yaw_angle, 0);/-129��90��
	 		 xingxing();
	 UART_SendFloat_ZS(pitch_angle, 0);//-2��3�ȱ仯��
	 		 xingxing();
	 UART_SendFloat_ZS(roll_angle,1);
  */

//���ԣ���̨���ƣ����+9250+ң���Ҹ��趨�Ƕ�---------------------------------------------------
//ֻ���޸ı�������ʼƫ��ֵ����

/*
UART_SendFloat_ZS(yaw_angle, 0);//��̨�����⻷�Ƕ�
   	 		 xingxing();	
UART_SendFloat_ZS(GMYawEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ��ۻ�
   	 		 xingxing();	
  UART_SendFloat_ZS(GimbalRef.yaw_angle_dynamic_ref ,1);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
*/

/*
UART_Send_Int16_ZS( -GMYawEncoder.raw_value, 0	 );//Y�������ԭʼ���ֵ��ȷ����ʼƫ��ֵ2157
  	 		 xingxing();	
UART_SendFloat_ZS(-GMYawEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ��ۻ�
 	 		 xingxing();
 UART_Send_Int16_ZS( -MPU6050_Real_Data.Gyro_Z, 1	 );//�ڻ����ٶ�ʵ��ֵ����̨������
 
UART_Send_Int16_ZS( GMPitchEncoder.raw_value, 0	);//�ڻ����ٶ�ʵ��ֵ  1280
   	 		 xingxing();	
 UART_SendFloat_ZS(-GMPitchEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
   	 		 xingxing();	//��ͷ13�ȣ�̧ͷ-31��
 UART_Send_Int16_ZS( -MPU6050_Real_Data.Gyro_X, 1	 );//�ڻ����ٶ�ʵ��ֵ ��̨������

  UART_SendFloat_ZS(GimbalRef.yaw_angle_dynamic_ref ,0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
	   	 		 xingxing();	
  UART_SendFloat_ZS(GimbalRef.pitch_angle_dynamic_ref  ,1);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
                   //���ϲ�-
*/
//���ԣ��ڿڵ��------------------------------------------------------------------------------------------------------------
  /*
 UART_Send_Int16_ZS( GMPokeEncoder.ecd_bias, 0	 );//�ڻ����ٶ�ʵ��ֵ
   xingxing();	
 UART_Send_Int16_ZS( GMPokeEncoder.raw_value, 0 );//�ڿڱ�����ԭʼֵ
  xingxing();	
 UART_Send_Int16_ZS( GMPokeEncoder.ecd_angle, 1 );//�ڿڱ�����ԭʼֵ1451  3715   5669 8134

// UART_Send_Int16_ZS( Shot_Flag, 0 );//
 // xingxing();	
	//UART_Send_Int16_ZS( Shot_Flag_OK, 0 );//
//  xingxing();	
 UART_Send_Int16_ZS(  GMPokePositionPID.ref, 0	 );//
   xingxing();	
 UART_Send_Int16_ZS( GMPokePositionPID.fdb , 1 );//
 //  */
//���ԣ�����6050------------------------------------------------------------------------------------------------------------
 /*
//  ����6050�������ǽ��ٶȣ�˳ʱ����ת-150����ʱ����ת+150
  UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 0 );
   xingxing();	
 //  ����6050����������Ϊ�������ٶȺ�ŷ���ǣ������������£����º��м�ʮ�ĽǶȣ����Ӵ�ֱ90��
	 UART_Send_Int16_ZS( ChassisCenter.Accel, 0 );//
   xingxing();
	 UART_Send_Int16_ZS( ChassisCenter.roll_angle, 1 );//
   xingxing();	
  */
	//�����ң����ٶȸ�����ת�趨ֵ��	
//  UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 0 );
 //  xingxing();	
 //  ����6050����������Ϊ�������ٶȺ�ŷ���ǣ������������£����º��м�ʮ�ĽǶȣ����Ӵ�ֱ90��
//	 UART_Send_Int16_ZS( ChassisCenter.Accel, 0 );//
  // xingxing();
	// UART_Send_Int16_ZS( ChassisCenter.roll_angle, 1 );//

	//	 UART_Send_Int16_ZS(ChassisSpeedRef.rotate_ref	 , 1);//ƽ��ԭʼ�ٶ�


	 //UART_Send_Int16_ZS( ChassisCenter.CompareState, 1 );//
//	 UART_Send_Int16_ZS( ChassisCenter.Gyro_Z, 1 );//
//	 UART_Send_Enter_ZS(); 


//���ԣ�����ina260------------------------------------------------------------------------------------------------------------

/*

��ֹ
��ѹ 23.1
���� 0.126
����  3

���
22.5
2.5
50

*/	 

/*
��ֹ
����3
�����趨ֵ 0
����ʵ��ֵ 128

��
����          6.5 
�����趨ֵ    665
����ʵ��ֵ    285

����					14
�����趨ֵ 		201
����ʵ��ֵ    665

����        9.5
�����趨ֵ  161
����ʵ��ֵ  421

����         54
�����趨ֵ   318
����ʵ��ֵ   2428

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

   //UART_Send_Int16_ZS(GMYawEncoder.raw_value, 1);//����ԭʼֵ ��ת-�ൽ��


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
��ֹ ����
+-100��





��ֹ��
�趨������ʵ�ʵ�����
0,130     0A,0.13A
ƫ�� -130�� PID�������-1300����ѵ�����õ�ת��㷴�����Ա������Ƶ����������СΪ0��һ������Ϊ��


���ص���
900**237     1.1A   0.237A
ƫ� 650     ��   ���õ�������ܴ󣬴���

���ظ���
1350  1939    1.65A,   1.939A

�������
1170**2585    1.43A,2.585A
1200**2287    1.46A,
1020**2447    1.24


����

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
���򣺲������̹������ƣ�80W,�����ѹ30V

��ѹ  ����  ����  
23     0     2     
22     2     52
21     5      48
23     0	    62
22900 126  290
22350 1900 4500

���̵���˶�Խ��Խ���ң���� ��ѹ���ͣ��������󣬹�������
״̬ 0����IO����ڵ͵�ƽ����������û��	
״̬ 1����IO����ڸߵ�ƽ�����������е�	
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

 
//P����ԣ���ѧ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
/*
//̧ͷ���ʱ555���м�0����ͷ���ʱ7618��
 //UART_Send_Int16_ZS( GMPitchEncoder.raw_value, 1	 );//�ڻ����ٶ�ʵ��ֵ
// ̧ͷ0�ȣ���ͷ-50��
//UART_SendFloat_ZS(GMPitchEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
 	// 		 xingxing();			 
// UART_SendFloat_ZS(pitch_angle, 1);//̧ͷ 1�ȣ���ͷ3��
 	 	//	 xingxing();
//���ְڶ���̧ͷ��+200����ͷ-200
// UART_Send_Int16_ZS( MPU6050_Real_Data.Gyro_X, 1	 );//�ڻ����ٶ�ʵ��ֵ
	//    GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle;
	
//UART_SendFloat_ZS(GMPitchEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
 //	 		 xingxing();
//UART_SendFloat_ZS(GMPPositionPID.fdb , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
 //	 		 xingxing();
//UART_Send_Int16_ZS( GMPPositionPID.ref, 1	 );//�ڻ����ٶ�ʵ��ֵ
//ң�ؿ������ֵ  0��35
*/

/*
ң����ǰ����ң�ؽǶ�35�ȣ��Ƕ�ʵ��ֵ25
ң����󲦣�ң�ؽǶ�0�ȣ� �Ƕ�ʵ��ֵ0
*/
//Y����ԣ���ѧ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
/*
UART_SendFloat_ZS(GMYawEncoder.ecd_angle , 0);//�⻷�Ƕ�ʵ��ֵ���������Ƕ�
 	 		 xingxing();
UART_SendFloat_ZS(yaw_angle, 0);//̧ͷ 1�ȣ���ͷ3��
 	 		 xingxing();
 UART_Send_Int16_ZS( MPU6050_Real_Data.Gyro_Z, 1	 );//�ڻ����ٶ�ʵ��ֵ�����Ҹ�
  	 		 xingxing();
 UART_Send_Int16_ZS( GMYawEncoder.raw_value, 0	 );//�ڻ����ٶ�ʵ��ֵ
  	 		 xingxing();		 
 UART_Send_Int16_ZS( GMYawEncoder.ecd_bias, 1	 );//�ڻ����ٶ�ʵ��ֵ����ʼƫ��
*/







