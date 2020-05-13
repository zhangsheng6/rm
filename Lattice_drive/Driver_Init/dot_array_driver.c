#include "dot_array_driver.h"

//CanTxMsg  TxMessage;   
Status_Flag  mode;
u16 TimeToMin;
extern CanRxMsg  RxMessage;
extern u8 HittedState;
extern u8 CanIDValue;

//GPIO INT 
Bit16 Data[8]={0xcf,0xe7,0xf3,0xf9,0xf9,0xf3,0xe7,0xcf}; //for the stady,right move 1 bit
//Bit16 Data[8]={0xcf,0xe7,0xf3,0xf9,0xf9,0xf3,0xef,0xf7}; //             ���������ڲ��ԣ�ԭ��������һ��
Bit16 DataUp[8]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};
Bit16 DataFlag,BoardFlag;
Bit16 Test,TestData;
/*
��������IO�ڣ�A0-A8
*/
void GPIO_Int(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);				 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
		GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
}

/*
����ת��
������
������Ϊ1��1��7��0����  JP3_SI=1��
����				    JP3_SI=0��
*/
void DataShift(unsigned char Data)
{
		unsigned char DataShiftCout=0;
//		JP3_RCK=0;				
	//һ��ѭ��
		for(DataShiftCout=0;DataShiftCout<8;DataShiftCout++)
	{	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
		if(Data&(0x01<<DataShiftCout))//data==��ĳһλ ��1
			JP3_SI=1;
		else 
			JP3_SI=0;
		
	    JP3_SCK=0; 
			delay_us(1);
			JP3_SCK=1;
		delay_us(1);
	}
//		JP3_OE_Blue=0;
//		delay_us(10);
}

/*
����ѡ��
������
			ѡ������=001��JP3_A=1
			ѡ������=010��JP3_B=1
			ѡ������=100��JP3_C=1
			����JP3_A=0��JP3_B=0��JP3_C=0
*/
void DataSelect(char SlcNumber)
{
	if(SlcNumber&0x01)
		JP3_A=1;
	else 
		JP3_A=0;
	if(SlcNumber&0x02)
		JP3_B=1;
	else 
		JP3_B=0;
	if(SlcNumber&0x04)
		JP3_C=1;
	else 
		JP3_C=0;
}

/*
����չʾ
*/
void DotArrayShow(Bit16 colour,u8 *data)
{
	Bit16 RowCount,BoardCount;
	for(RowCount=0;RowCount<8;RowCount++)
	{
	

		for(BoardCount=0;BoardCount<7;BoardCount++)
		{
			DataShift(*(data+RowCount));
//			DataShift(TestData);												//��������

		}
		DataSelect(RowCount);
//		DataSelect(Test);
		JP3_RCK=0;
		delay_us(1);
		JP3_RCK=1;
		delay_us(4);
		switch (colour)
		{
		case 0:JP3_OE_Blue=0;break;
		case 1:JP3_OE_Red=0;break;
		default: break;
		}
		
//			JP3_OE_Green=0;
		
	}
}
void DotArrayShowUp(Bit16 colour)
{
	Bit16 RowCount,BoardCount;
			for(RowCount=0;RowCount<8;RowCount++)
				{
					if(BoardFlag==6)
					{
						DotArrayShowFull(colour,0x00);
						
					}
					else
					{
						for(BoardCount=0;BoardCount<(6-BoardFlag);BoardCount++)
								DataShift(0xff);
					
								DataShift(DataUp[DataFlag]);
						for(BoardCount=0;BoardCount<BoardFlag;BoardCount++)
								DataShift(0x00);	
						DataSelect(RowCount);
						JP3_RCK=0;
						delay_us(1);
						JP3_RCK=1;
					}
				
					delay_us(4);
				
					
						switch (colour)
					{
					case 0:JP3_OE_Blue=0;break;
					case 1:JP3_OE_Red=0;break;
					default: break;
					}
				}				
}
/*
ȷ�ϵ�������IO�ڵ�״̬�õ���ȫ��/��
*/
void DotArrayShowFull(Bit16 colour,u8 State)

{
	Bit16 RowCount,BoardCount;
	for(RowCount=0;RowCount<8;RowCount++)//�м���
	{
	
		for(BoardCount=0;BoardCount<7;BoardCount++)
		{
			DataShift(State);//������Ϊ1��1��7��0����  JP3_SI=1��

		}
		DataSelect(RowCount);//RowCount=1��2��4��JP3_A/B/C=1
		JP3_RCK=0;
		delay_us(1);
		JP3_RCK=1;
		delay_us(4);
		switch (colour)
		{
		case 0:JP3_OE_Blue=0;break;
		case 1:JP3_OE_Red=0;break;
		default: break;
		}
//		JP3_OE_Blue=0;
//		JP3_OE_Red=0;
//			JP3_OE_Green=0;
	}

}

/*
����8������:��ÿ�����ݵ����λ���������λ
data��12345678
data=01234567|80000000
data=81234567
*/
void  ring_shift_left(unsigned char *data)
{ 
	int ShifCount;
	for(ShifCount=0;ShifCount<8;ShifCount++)
	{
	 *data = (*data>> 1) | (*data<<7);	//ԭ�����������Ƶ���
		data++;
	}
}






/*
�������ܣ�ʵ�ֶ�5������װ�װ��Ӧ�ĵƵ���Ŀ���
���Ƶ�CANID:0X301--0X305
��������������־λhitted		������ȷ��			0x01;			�������			0x02;	
*/					
void ControlDotArray(u8 CanID)
{
	
	mode.ID=(int16_t)(0x301+CanID);//��ID1-5,��ʱ��Ӧ����0x300ô
//�տ�ʼ����������LEDȫ��
	if((mode.ActingFailed==0)&&(mode.ActingSucess==0)&&(mode.Ready==0))
	{
		DotArrayShowFull(mode.Colour,0xff);//��������LEDȫ��
	}

//�ܵĻ���״̬������ɹ���������LEDȫ��	����������������LEDȫ��	
	switch(mode.hitted)
	{
		case 1:DotArrayShowFull(mode.Colour,0x00);break;
		case 2:DotArrayShowFull(mode.Colour,0xFF);break;
		default:break;
	}
//������󣺵�������LEDȫ��	������ģʽ��0			
	if(mode.ActingFailed==1)																											//���������ػ���ʧ�ܣ�ȫ��
		
		{
			DotArrayShowFull(mode.Colour,0xff);
			mode.Acting=0;
			mode.hitted=0x00;	

		}
//����ɹ���TIM3ʹ�ܣ���������LED Up	������ģʽ��0					
		if(mode.ActingSucess==1)																										//���������ػ��ɹ����ۼ�֮��ȫ��
		{
			TIM_Cmd(TIM3, ENABLE); 
			DotArrayShowUp(mode.Colour);
			mode.Acting=0;
			mode.hitted=0x00;	
		}
//��������У�û���У�TIM3ʹ�ܣ�	DataFlag=BoardFlag=0;				
		if(mode.ActingSucess==0)
		{
			DataFlag=BoardFlag=0;
			TIM_Cmd(TIM3,DISABLE);
			
		}

		if((mode.Acting==1)&&(mode.Ready==1)&&(mode.hitted==0))                    //��ѡ�� ready=1,�������ڼ���״̬
		{
				
//					TIM_Cmd(TIM2, ENABLE);  																																	//ʹ��TIM2	
					DotArrayShow(mode.Colour,Data);
//						mode.hitted=0x00;
				
		}
		if(mode.Ready==0&&mode.hitted==0)
		{
			DotArrayShowFull(mode.Colour,0xff);
		}
		
		
//			TIM_Cmd(TIM3, ENABLE); 
//			DotArrayShowUp(mode.Colour);
//	DotArrayShowFull(Blue,0x00);
//	delay_us(500);
		
}


