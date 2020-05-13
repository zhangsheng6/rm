#include "can_tr.h"
#include "stm32f10x.h"//u16

/*
 	函数名：	CAN_Tx_Master
	函数功能：给主机发送信息        
	输入参数：击打标志位
						击中正确：			0x01;				
						击打错误：			0x02;
*/	
	void CAN_Tx_Master(u16 CAN_IDN ,u8 hitted)
{
		CanTxMsg  TxMessage;   					//发送信息结构体
		
		TxMessage.StdId=(u16)CAN_IDN;
  	TxMessage.ExtId =0;
		TxMessage.IDE=CAN_ID_STD;						//标准帧
		TxMessage.RTR=CAN_RTR_Data;					//数据帧
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


