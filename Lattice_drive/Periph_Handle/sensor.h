#ifndef _sensor_h_
#define _sensor_h_

#include "can_tr.h"
#include "init.h"

void CAN_Tx_Master(u16 CAN_IDN ,u8 hitted);
void Sensor_Init_EXTI(void);
u8 Sensor(void);

#endif


