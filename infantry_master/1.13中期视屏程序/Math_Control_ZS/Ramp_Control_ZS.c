#include "init.h"
#include "Ramp_Control_ZS.h"

//斜坡计数,限制最大值，归1，返回归一输出值
float RampCalc(RampGen_t *ramp)
{
	ramp -> count++;
	if(ramp -> count > ramp -> XSCALE) 
		ramp -> count = ramp -> XSCALE;
	ramp -> out = (1.0f * (ramp -> count) / ramp -> XSCALE);
	return ramp->out;
}



//设置斜坡计数最大值
void RampSetScale(struct RampGen_t *ramp, int32_t scale)
{
	ramp ->XSCALE = scale;
}

//斜坡计数清0 
void RampResetCounter(struct RampGen_t *ramp)
{
	ramp ->count = 0;
}


//斜坡初始化：计数清0，计数最大值设置
void RampInit(RampGen_t *ramp, int32_t XSCALE)
{
	ramp -> count = 0;
	ramp ->XSCALE = XSCALE;
}
	

//设置斜坡计数值数值	
void RampSetCounter(struct RampGen_t *ramp, int32_t count)
{
	ramp -> count = count;
}
		


//斜坡计数值是否溢出		
uint8_t RampIsOverflow(struct RampGen_t *ramp)
{
	if(ramp -> count >= ramp -> XSCALE) return 1;
	else 																return 0;
}


//斜坡计数循环
//根据时间从-1到+1内循环输出
//返回-1 到1
float RampCalcLoop(RampGenLoop_t *ramp)
{
//保证 斜坡计数在 -XSCALE到XSCALE 之间循环	
	if(ramp->flag < 1)
	{
		ramp->count++;
	}
	else if(ramp->flag >-1)
	{
		ramp->count--;
	}

	if(ramp->count >= ramp->XSCALE)
	{
		ramp->count = ramp->XSCALE;
		ramp->flag = 1;
	}		
	else if(ramp->count <= -ramp->XSCALE)
	{
		ramp->count = -ramp->XSCALE;                                                                                                                                                                                                                                                                                                                            
		ramp->flag = -1;
	}		
//返回输出 -1到1	
	ramp->out = (1.0f * (ramp->count) / ramp->XSCALE);
	return ramp->out; 
}


//
void RampSetScaleLoop(struct RampGenLoop_t *ramp, int32_t scale)
{
	ramp->XSCALE = scale;
}


//斜坡循环计数清0
void RampResetCounterLoop(struct RampGenLoop_t *ramp)
{
	ramp->count = 0;
	ramp->flag = 0;
}




//斜坡循环计数初始化
void RampInitLoop(RampGenLoop_t *ramp, int32_t XSCALE)
{
	ramp->count = 0;
	ramp->flag = 0;
	ramp->XSCALE = XSCALE;

}

//










