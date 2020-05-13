#ifndef _led_h_
#define _led_h_

#include "sys.h"//ÓÐPAout(5)
#include "init.h"

#define on 1
#define off 0

void Led_Init(void);
void Light_Bar(unsigned char num,unsigned char A,unsigned char B);

#endif

