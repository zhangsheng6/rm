#ifndef __MPU9250_READ_ZS_H__
#define __MPU9250_READ_ZS_H__
#include "init.h"


void MPU9250_Read_Data_ZS(void);

extern short TEMP_ej;					//ÎÂ¶È
extern short GYRO_EJ[3];
extern short ACC_EJ[3];
extern short MAG_EJ[3];

#endif


