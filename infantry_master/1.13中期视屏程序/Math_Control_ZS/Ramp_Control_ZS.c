#include "init.h"
#include "Ramp_Control_ZS.h"

//б�¼���,�������ֵ����1�����ع�һ���ֵ
float RampCalc(RampGen_t *ramp)
{
	ramp -> count++;
	if(ramp -> count > ramp -> XSCALE) 
		ramp -> count = ramp -> XSCALE;
	ramp -> out = (1.0f * (ramp -> count) / ramp -> XSCALE);
	return ramp->out;
}



//����б�¼������ֵ
void RampSetScale(struct RampGen_t *ramp, int32_t scale)
{
	ramp ->XSCALE = scale;
}

//б�¼�����0 
void RampResetCounter(struct RampGen_t *ramp)
{
	ramp ->count = 0;
}


//б�³�ʼ����������0���������ֵ����
void RampInit(RampGen_t *ramp, int32_t XSCALE)
{
	ramp -> count = 0;
	ramp ->XSCALE = XSCALE;
}
	

//����б�¼���ֵ��ֵ	
void RampSetCounter(struct RampGen_t *ramp, int32_t count)
{
	ramp -> count = count;
}
		


//б�¼���ֵ�Ƿ����		
uint8_t RampIsOverflow(struct RampGen_t *ramp)
{
	if(ramp -> count >= ramp -> XSCALE) return 1;
	else 																return 0;
}


//б�¼���ѭ��
//����ʱ���-1��+1��ѭ�����
//����-1 ��1
float RampCalcLoop(RampGenLoop_t *ramp)
{
//��֤ б�¼����� -XSCALE��XSCALE ֮��ѭ��	
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
//������� -1��1	
	ramp->out = (1.0f * (ramp->count) / ramp->XSCALE);
	return ramp->out; 
}


//
void RampSetScaleLoop(struct RampGenLoop_t *ramp, int32_t scale)
{
	ramp->XSCALE = scale;
}


//б��ѭ��������0
void RampResetCounterLoop(struct RampGenLoop_t *ramp)
{
	ramp->count = 0;
	ramp->flag = 0;
}




//б��ѭ��������ʼ��
void RampInitLoop(RampGenLoop_t *ramp, int32_t XSCALE)
{
	ramp->count = 0;
	ramp->flag = 0;
	ramp->XSCALE = XSCALE;

}

//










