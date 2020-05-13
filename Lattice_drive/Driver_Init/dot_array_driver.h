#ifndef _dot_array_driver_h_
#define _dot_array_driver_h_

#include "init.h"
#define JP3_A PAout(0)
#define JP3_B PAout(1)
#define JP3_C PAout(2)
#define JP3_SCK PAout(3)
#define JP3_RCK PAout(4)
#define JP3_SI PAout(5)
#define JP3_OE_Blue PAout(6)
#define JP3_OE_Red PAout(7)
#define JP3_OE_Green PAout(8)
#define Blue 0
#define Red 1
#define TimeCountMin 14
typedef unsigned char Bit16;
typedef  struct 
{
	unsigned char row;
	unsigned char *SIDdata;
	unsigned char LoopCount;
}DotArray;


typedef  struct                 
{
	u8 Colour;
	u8 Ready;
	u8 Acting;
	u8 ActingFailed;
	u8 ActingSucess;
	u8 hitted;
	u16 ID;
	u8	HitCount;
	u8  DataTest;
}Status_Flag;


// typedef enum
//{
//	Blue=0,
//	Red,


//}color;


void GPIO_Int(void);

void DataShift(unsigned char Data);
void DataSelect(char SlcNumber);
void  ring_shift_left(unsigned char *data);

void DotArrayShow(Bit16 colour,u8 *data);
void DotArrayShowUp(Bit16 colour);
void DotArrayShowFull(Bit16 colour,u8 State);

void ControlDotArray(u8 CanID);



	

#endif


