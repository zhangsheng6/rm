#ifndef _can_tr_h_
#define _can_tr_h_
#include "stm32f10x_can.h"

#define CAN_3508_M1_ID 0x201  
#define CAN_3508_M2_ID 0x202
#define CAN_3508_M3_ID 0x203
#define CAN_3508_M4_ID 0x204//��� ID

#define CAN_flabellum0_ID 0x301  //����װ�װ��ID
#define CAN_flabellum1_ID 0x302
#define CAN_flabellum2_ID 0x303
#define CAN_flabellum3_ID 0x304
#define CAN_flabellum4_ID 0x305

#define CAN_MASTER_ID     0x300

/*CAN�������*/
void CAN_Tx_Master(u16 CAN_IDN ,u8 hitted);
void Can_Tx_Motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
void CAN_CMD_msg(unsigned char data[]); //������Ҷ��Ϣ

/*CAN�������*/
void Can_Hook(CanRxMsg *rx_message);//�������ݴ���

	

#endif


