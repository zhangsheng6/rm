#ifndef _can_H_
#define _can_H_

#include "init.h"
//������ݽṹ��
 typedef struct 
{
    uint16_t ecd;           //��������е�Ƕ�
    int16_t speed_rpm;      //ת��_ÿ����ת��
    int16_t actual_current; //ʵ�ʵ���
    uint8_t temperate;      //����¶�
    uint16_t last_ecd;       //�ϴλ�е�Ƕ�
} Motor_Measure_Struct;



void Can1_Init(void);
void Can_Tx_Motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);//����3508����
void CAN_CMD_msg(unsigned char data[]);//������Ҷ��Ϣ


void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);



extern CanRxMsg rx1_message;
extern int16_t am[8];

#endif


