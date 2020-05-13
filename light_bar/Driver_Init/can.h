#ifndef _can_H_
#define _can_H_

#include "init.h"
//������ݽṹ��
 typedef struct 
{
    uint16_t ecd;           //��е�Ƕ�
    int16_t speed_rpm;      //ת��
    int16_t actual_current; //��������
    uint8_t temperate;      //����¶�
    uint16_t last_ecd;       //�ϴλ�е�Ƕ�
} motor_measure_t;


#define CAN_flabellum0_ID 0x301  //���λ����ID
#define CAN_flabellum1_ID 0x302
#define CAN_flabellum2_ID 0x303
#define CAN_flabellum3_ID 0x304
#define CAN_flabellum4_ID 0x305

#define CAN_MASTER_ID     0x300

void Can1_Init(void);
void CAN_CMD_3508(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);//����3508����
void CAN_CMD_msg(unsigned char data[]);//������Ҷ��Ϣ


void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);


void Can_Hook(CanRxMsg *rx_message);//�������ݴ���


#endif


