#ifndef _tim_h_
#define _tim_h_

#include "init.h"

#define TimeCountMin 14
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
}Status;

void Tim2_Init(u16 arr,u16 psc);
void Tim3_Init(u16 arr,u16 psc);

#endif

