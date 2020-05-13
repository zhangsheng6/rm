#include "can_tr.h"
#include "energy_authorities_task.h"

extern Armour_Status_Struct  Flabellum_Armour[5];
Motor_Measure_Struct  motor[4];
/*
CAN接收的ID是电机的ID时
Data[0]Data[1]：编码器机械角度
Data[2]Data[3]：速度_每分钟转数
Data[4]Data[5]：实际电流值
Data[6]：电机温度

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


/*
CAN1发送数据
ID:0x200,3508电机
Data[]:pid.out电机输出电流值
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
CAN1发送数据
ID:0x300,
Data[]: 5个扇形的：颜色|准备状态|运行模式
*/
void CAN_CMD_msg(unsigned char data[]) //发送扇叶信息
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
CAN挂钩:
接收5个扇形装甲板的击打信息：ID:0x301-305
Data[0]：0未击中  1击打正确   2击打错误 

接收1个风车电机的信息:ID:0x204
Data[0]Data[1]：编码器机械角度
Data[2]Data[3]：速度_每分钟转数
Data[4]Data[5]：实际电流值
Data[7]：电机温度

*/
void Can_Hook(CanRxMsg *rx_message)
{
    switch (rx_message->StdId)
    { 
			case CAN_flabellum0_ID:
			{
			Flabellum_Armour[0].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
			} break;
			case CAN_flabellum1_ID:
							{
			Flabellum_Armour[1].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
			} break;
			case CAN_flabellum2_ID:
							{
			Flabellum_Armour[2].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
			} break;
			case CAN_flabellum3_ID:
							{
			Flabellum_Armour[3].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
			} break;
			case CAN_flabellum4_ID:
							{
			Flabellum_Armour[4].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
			} break;
//					{
//						 static uint8_t num = 0;
//						 num = rx_message->StdId - CAN_flabellum0_ID; 
//						 Flabellum_Armour[num].hitted = (rx_message)->Data[0]; // 0:未击中  1：击打正确   2：击打错误
//					}break;
					
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
					{
							static uint8_t i = 0;
							//处理电机ID号
							i = rx_message->StdId - CAN_3508_M1_ID;//i=3
							//处理电机数据宏函数
							get_motor_measure(&motor[i], rx_message);    
					}   break;


    }
		
}


	







