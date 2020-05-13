#ifndef _can_H_
#define _can_H_

#include "init.h"
//电机数据结构体
 typedef struct 
{
    uint16_t ecd;           //编码器机械角度
    int16_t speed_rpm;      //转速_每分钟转数
    int16_t actual_current; //实际电流
    uint8_t temperate;      //电机温度
    uint16_t last_ecd;       //上次机械角度
} Motor_Measure_Struct;



void Can1_Init(void);
void Can_Tx_Motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);//发送3508电流
void CAN_CMD_msg(unsigned char data[]);//发送扇叶信息


void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);



extern CanRxMsg rx1_message;
extern int16_t am[8];

#endif


