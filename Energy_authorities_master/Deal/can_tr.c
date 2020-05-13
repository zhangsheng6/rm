#include "can_tr.h"
#include "energy_authorities_task.h"

extern Armour_Status_Struct  Flabellum_Armour[5];
Motor_Measure_Struct  motor[4];
/*
CAN���յ�ID�ǵ����IDʱ
Data[0]Data[1]����������е�Ƕ�
Data[2]Data[3]���ٶ�_ÿ����ת��
Data[4]Data[5]��ʵ�ʵ���ֵ
Data[6]������¶�

*/
#define   get_motor_measure(ptr, rx_message)                                                    \
    {                                                                                           \
(ptr)->last_ecd = (ptr)->ecd;                                                           \
(ptr)->ecd = (uint16_t)((rx_message)->Data[0] << 8 | (rx_message)->Data[1]);            \
(ptr)->speed_rpm = (uint16_t)((rx_message)->Data[2] << 8 | (rx_message)->Data[3]);      \
(ptr)->actual_current = (uint16_t)((rx_message)->Data[4] << 8 | (rx_message)->Data[5]); \
(ptr)->temperate = (rx_message)->Data[6];                                               \
    }
		
	
/*
 	��������	CAN_Tx_Master
	�������ܣ�������������Ϣ        
	��������������־λ
						������ȷ��			0x01;				
						�������			0x02;
*/	
	void CAN_Tx_Master(u16 CAN_IDN ,u8 hitted)
{
		CanTxMsg  TxMessage;   					//������Ϣ�ṹ��
		
		TxMessage.StdId=(u16)CAN_IDN;
  	TxMessage.ExtId =0;
		TxMessage.IDE=CAN_ID_STD;						//��׼֡
		TxMessage.RTR=CAN_RTR_Data;					//����֡
		TxMessage.DLC = 0x08;
   
		
   TxMessage.Data[0]= hitted;//(hitted&0x03);
	 TxMessage.Data[1] = 0x00;
   TxMessage.Data[2] = 0x00;
	 TxMessage.Data[3] = 0x00;
   TxMessage.Data[4] = 0x00;
	 TxMessage.Data[5] = 0x00;
   TxMessage.Data[6] = 0x00;
	 TxMessage.Data[7] = 0x00;
	CAN_Transmit(CAN1,&TxMessage);
	
}


/*
CAN1��������
ID:0x200,3508���
Data[]:pid.out����������ֵ
*/
void Can_Tx_Motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
    CanTxMsg TxMessage;
    TxMessage.StdId = 0x200;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 0x08;
    TxMessage.Data[0] = motor1 >> 8;
    TxMessage.Data[1] = motor1;
    TxMessage.Data[2] = motor2 >> 8;
    TxMessage.Data[3] = motor2;
    TxMessage.Data[4] = motor3 >> 8;
    TxMessage.Data[5] = motor3;
    TxMessage.Data[6] = motor4 >> 8;
    TxMessage.Data[7] = motor4;

    CAN_Transmit(CAN1, &TxMessage);
}

/*
CAN1��������
ID:0x300,
Data[]: 5�����εģ���ɫ|׼��״̬|����ģʽ
*/
void CAN_CMD_msg(unsigned char data[]) //������Ҷ��Ϣ
{
    CanTxMsg TxMessage;
    TxMessage.StdId = 0x300;
	//  TxMessage.ExtId = 0 ;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
  	TxMessage.DLC = 0x08;        
    TxMessage.Data[0] = data[0];
    TxMessage.Data[1] = data[1];
    TxMessage.Data[2] = data[2];
    TxMessage.Data[3] = data[3];
    TxMessage.Data[4] = data[4];
    TxMessage.Data[5] = 0;
    TxMessage.Data[6] = 0;
    TxMessage.Data[7] = 0;
	
    CAN_Transmit(CAN1, &TxMessage);
}



/*
CAN�ҹ�:
����5������װ�װ�Ļ�����Ϣ��ID:0x301-305
Data[0]��0δ����  1������ȷ   2������� 

����1���糵�������Ϣ:ID:0x204
Data[0]Data[1]����������е�Ƕ�
Data[2]Data[3]���ٶ�_ÿ����ת��
Data[4]Data[5]��ʵ�ʵ���ֵ
Data[7]������¶�

*/
void Can_Hook(CanRxMsg *rx_message)
{
    switch (rx_message->StdId)
    { 
			case CAN_flabellum0_ID:
			{
			Flabellum_Armour[0].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum1_ID:
							{
			Flabellum_Armour[1].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum2_ID:
							{
			Flabellum_Armour[2].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum3_ID:
							{
			Flabellum_Armour[3].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
			case CAN_flabellum4_ID:
							{
			Flabellum_Armour[4].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
			} break;
//					{
//						 static uint8_t num = 0;
//						 num = rx_message->StdId - CAN_flabellum0_ID; 
//						 Flabellum_Armour[num].hitted = (rx_message)->Data[0]; // 0:δ����  1��������ȷ   2���������
//					}break;
					
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
					{
							static uint8_t i = 0;
							//������ID��
							i = rx_message->StdId - CAN_3508_M1_ID;//i=3
							//���������ݺ꺯��
							get_motor_measure(&motor[i], rx_message);    
					}   break;


    }
		
}


	







