#include "Poke_Control_ZS.h"
#include "init.h"
u8	 Shot_Flag_OK=0;

//�������
PID GMPokeSpeedPID;
PID GMPokePositionPID;

//�ڿ�c610�����24V
void GMPokeControlLoop(void)
{
//�ٶ�PID
	/*
	GMPokeSpeedPID.ref = 200;
	GMPokeSpeedPID.fdb = GMPokeEncoder.filter_rate;
	
	PID_Set(&GMPokeSpeedPID,GMPokePID_S.P,GMPokePID_S.I,GMPokePID_S.D);

	PID_Control_Position(&GMPokeSpeedPID);	
  */
	
//�Ƕ�PID    Shot_Flag_OK
	///*
Shot_Flag=Shot_Flag_Temp;
	
	if(Shot_Flag==1)
	{
		if(Shot_Flag_OK==1)
		{
	   	Shot_Flag_OK=0;
	    GMPokePositionPID.ref -=2200;
	    //GMPokePositionPID.ref +=4000;//���ڿ�
		}
	}
	else if(Shot_Flag==2)
	{
		Shot_Flag_OK=1;
	}
	GMPokePositionPID.fdb = GMPokeEncoder.ecd_angle;
	
	PID_Set(&GMPokePositionPID,PokePID_Position.P,PokePID_Position.I,PokePID_Position.D);

	PID_Control_Position(&GMPokePositionPID);	
	//*/
}





