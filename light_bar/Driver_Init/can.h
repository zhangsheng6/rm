#ifndef _can_H_
#define _can_H_

#include "init.h"
//电机数据结构体
 typedef struct 
{
    uint16_t ecd;           //机械角度
    int16_t speed_rpm;      //转速
    int16_t actual_current; //给定电流
    uint8_t temperate;      //电机温度
    uint16_t last_ecd;       //上次机械角度
} motor_measure_t;


#define CAN_flabellum0_ID 0x301  //扇形击打板ID
#define CAN_flabellum1_ID 0x302
#define CAN_flabellum2_ID 0x303
#define CAN_flabellum3_ID 0x304
#define CAN_flabellum4_ID 0x305

#define CAN_MASTER_ID     0x300

void Can1_Init(void);
void CAN_CMD_3508(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);//发送3508电流
void CAN_CMD_msg(unsigned char data[]);//发送扇叶信息


void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);


void Can_Hook(CanRxMsg *rx_message);//接收数据处理


#endif


