#include "Encoder_ZS.h"

volatile Encoder CM1Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM2Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM3Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM4Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMPokeEncoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMYawEncoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMPitchEncoder = {0,0,0,0,0,0,0,0,0};
volatile ChassisCenter_t ChassisCenter;   //底盘电流值
volatile JudgeMent  Real_JudgeMent; //裁判系统值
/*
*Name          :GetEncoderBias
*Input         :can message
*Return        :void
*Description   :to get the initiatial encoder of the chassis motor 201 202 203 204
*/
void GetEncoderBias(volatile Encoder *v, CanRxMsg * msg)
{
     v->ecd_bias = (msg->Data[0]<<8)|msg->Data[1];  //保存初始编码器值作为偏差 
 	v->encoder_dianliu=(msg->Data[4]<<8)|msg->Data[5];

//	 v->ecd_bias = (msg->Data[0]<<8)|msg->Data[1];  //保存初始编码器值作为偏差  
//            v->ecd_value = v->ecd_bias;
//            v->raw_value = v->ecd_bias;
//            v->temp_count++;
	
}

/*
*Name          :EncoderProcess
*Input         :can message
*Return        :void
*Description   :to get the initiatial encoder of the chassis motor 201 202 203 204

编码器原始输出值：raw_value
编码器原始连续输出值：ecd_value
编码器角度:ecd_angle 正负无穷大
原始速度：ecd_raw_rate
滤波速度：filter_rate=把5个ecd_raw_rate平均
*/
void EncoderProcess(volatile Encoder *v, CanRxMsg * msg)
{
//	v->rate_buf[v->buf_count++] = v->ecd_raw_rate;
//	if(v->buf_count == RATE_BUF_SIZE)
//	{
//		v->buf_count = 0;
//	}
//	//计算速度平均值
//	for(i = 0;i < RATE_BUF_SIZE; i++)
//	{
//		temp_sum += v->rate_buf[i];
//	}
//	v->filter_rate = (int32_t)(temp_sum/RATE_BUF_SIZE);	
	
int i=0;
	int32_t temp_sum = 0; 

	v->last_raw_value = v->raw_value;
	v->raw_value = (msg->Data[0]<<8)|msg->Data[1];
//	v->encoder_zhuansu=(msg->Data[2]<<8)|msg->Data[3];
 	v->encoder_dianliu=(msg->Data[4]<<8)|msg->Data[5];
//	v->encoder_wendu=msg->Data[6];
	v->diff = v->raw_value - v->last_raw_value;

		if(v->diff < -6500)    //两次编码器的反馈值差别太大，表示圈数发生了改变
		{
			v->round_cnt++;
			v->ecd_raw_rate = v->diff + 8192;
		}
		else if(v->diff>6500)
		{
			v->round_cnt--;
			v->ecd_raw_rate = v->diff- 8192;
		}		
		else
		{
			v->ecd_raw_rate = v->diff;     //原始速度
		}

	//计算得到连续的编码器输出值
	v->ecd_value = v->raw_value + v->round_cnt * 8192;
	//计算得到角度值，范围正负无穷大
	v->ecd_angle = (float)(v->raw_value - v->ecd_bias)*360/8192 + v->round_cnt * 360;
		
/*解算滤波速度*/		
	//速度滤波，效果好，速度差不了多少	
	v->rate_buf[v->buf_count++] = v->ecd_raw_rate;
	if(v->buf_count == RATE_BUF_SIZE)
	{
		v->buf_count = 0;
	}
	//计算速度平均值
	for(i = 0;i < RATE_BUF_SIZE; i++)
	{
		temp_sum += v->rate_buf[i];
	}
	v->filter_rate = (int32_t)(temp_sum/RATE_BUF_SIZE);			


}
