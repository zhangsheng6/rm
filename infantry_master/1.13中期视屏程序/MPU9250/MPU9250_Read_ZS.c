#include "MPU9250_Read_ZS.h"


short TEMP_EJ;					//ÎÂ¶È

short GYRO_EJ[3];
short ACC_EJ[3];
short MAG_EJ[3];

void MPU9250_Read_Data_ZS(void)
{


MPU9250_Get_Gyroscope( &GYRO_EJ[0], &GYRO_EJ[1], &GYRO_EJ[2]);
MPU9250_Get_Accelerometer( &ACC_EJ[0], &ACC_EJ[1], &ACC_EJ[2]);
 //MPU9250_Get_Mag( &MAG_EJ[0], &MAG_EJ[1], &MAG_EJ[2]);


}


