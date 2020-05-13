#include "iwdg.h"


//独立看门狗
//Tout=((4×2^prer) ×rlr) /40

void Iwdg_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//对寄存器IWDG_PR和IWDG_RLR 的写操作:使能
	IWDG_SetPrescaler(prer);//设置IWDG预分频：4，8，16...256
	IWDG_SetReload(rlr);		//设置 IWDG 重装载值：范围为 0 – 0x0FFF
	IWDG_ReloadCounter();		//按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
	IWDG_Enable();

}
//Feed IWDG ;
void IWDG_Feed(void)
{ 
IWDG_ReloadCounter();//reload 
}


