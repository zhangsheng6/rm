#include "can_tr.h"
#include "stm32f10x.h"//u16

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


