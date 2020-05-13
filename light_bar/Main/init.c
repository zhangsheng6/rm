#include "init.h"

void Init()
{

	NVIC_Init_User();
	Can1_Init();
	Delay_Init();
	Led_Init();
}


