#include "Init.h"

SuperCapacitor_State_e SuperCapacitor_State;


void PowerSupply_Task()
{
	SuperCapacitor_CompareState = Compare_State;
	
	if(SuperCapacitor_CompareState)
	{
		Charge_Disable;
		Battery_Enable;
		Output_ratio=0;
	}
	else
	{
		if(SendToJudgementData.SuperCapacitorComment == SuperCapacitor_ON)
		{
			Charge_Disable;
			Output_ratio=20;
			Battery_Disable;
		}
		else if(SendToJudgementData.SuperCapacitorComment == SuperCapacitor_Charge)
		{
			Battery_Enable;
			Output_ratio=0;
			Charge_Enable;
		}
		else
		{
			Charge_Disable;
			Battery_Enable;
			Output_ratio=0;
		}
	}
	TIM_SetCompare2(TIM3,Output_ratio);
}










