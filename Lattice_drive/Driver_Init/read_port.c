#include "read_port.h"

/*
�˿�ģʽ������ĳ�ʼ��
�˿ڣ�B3-5:����ID
�˿ڣ�B6:������ɫȷ��
*/
void Read_Port_Init(void)
{
   GPIO_InitTypeDef GPIO_StructInit;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_StructInit.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; 
	 GPIO_StructInit.GPIO_Mode = GPIO_Mode_IPU;  
	 GPIO_Init(GPIOB,&GPIO_StructInit);
}
//*�������ܣ���ȡPB��״̬
//*���������PB��״̬
//	��Ƭ���˿ڣ�		PB6				PB5				PB4						PB3                 on����Ϊ0   ��һ��Ϊ1
//	��Ӧ���뿪�أ�	4					3					2							1
//Id �Ŷ�Ӧ 				PB6Ϊ��λ��PB5Ϊ��λ
//����              PB6  PB5	PB4	 ����Ϊ100  ��IdΪ0x304
u16 Read_Port(void)
{
  u16 ID;
	ID=GPIOB->IDR;   //IDR�˿��������ݼĴ���
	return (ID&0x78);// &0xxx x000  
}
/*
���أ�CanID�ţ�1~5
*/
u32 Get_CanID(void)
{
	u32 IDnumber;
	IDnumber=(u32)(((Read_Port())&0x70)>>4);//& 0xxx 0000
	return IDnumber;	//���� xxx
}
//*��������ColourID
//*�������ܣ���ȡColourID
//*�����������
//*���������CanID�ţ�1:red     0:blue                     //������в��ô˺���
u16 Get_ColourID(void)
{
	u16 ColourID;
	ColourID=(Read_Port()&0x08>>3);
	return ColourID;
}

