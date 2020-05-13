#include "init.h"
/*

*/



extern u8 CanIDValue;

int main(void)
{
	
	Init();

  while(1)
	{
	   IWDG_Feed();  //ø¥√≈π∑Œππ∑
		  ControlDotArray(CanIDValue);
//	 CAN_Tx_Master(0x302,0x30);
		
		}

}



