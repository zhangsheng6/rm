#ifndef _CANTASK_SEND_H_
#define _CANTASK_SEND_H_
#include "stm32f4xx.h"                  // Device header
#include "init.h"

typedef struct
{
    CAN_TypeDef     *CANx;               //CAN���     1 CAN1      2 CAN2
    CanTxMsg    SendCanTxMsg;       //��������
}CanSend_Type;

void Task_CANSend(void const *argument);



#endif
