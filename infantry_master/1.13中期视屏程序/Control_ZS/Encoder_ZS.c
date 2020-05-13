#include "Encoder_ZS.h"

volatile Encoder CM1Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM2Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM3Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder CM4Encoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMPokeEncoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMYawEncoder = {0,0,0,0,0,0,0,0,0};
volatile Encoder GMPitchEncoder = {0,0,0,0,0,0,0,0,0};
volatile ChassisCenter_t ChassisCenter;   //���̵���ֵ
volatile JudgeMent  Real_JudgeMent; //����ϵͳֵ
/*
*Name          :GetEncoderBias
*Input         :can message
*Return        :void
*Description   :to get the initiatial encoder of the chassis motor 201 202 203 204
*/
void GetEncoderBias(volatile Encoder *v, CanRxMsg * msg)
{
     v->ecd_bias = (msg->Data[0]<<8)|msg->Data[1];  //�����ʼ������ֵ��Ϊƫ�� 
 	v->encoder_dianliu=(msg->Data[4]<<8)|msg->Data[5];

//	 v->ecd_bias = (msg->Data[0]<<8)|msg->Data[1];  //�����ʼ������ֵ��Ϊƫ��  
//            v->ecd_value = v->ecd_bias;
//            v->raw_value = v->ecd_bias;
//            v->temp_count++;
	
}

/*
*Name          :EncoderProcess
*Input         :can message
*Return        :void
*Description   :to get the initiatial encoder of the chassis motor 201 202 203 204

������ԭʼ���ֵ��raw_value
������ԭʼ�������ֵ��ecd_value
�������Ƕ�:ecd_angle ���������
ԭʼ�ٶȣ�ecd_raw_rate
�˲��ٶȣ�filter_rate=��5��ecd_raw_rateƽ��
*/
void EncoderProcess(volatile Encoder *v, CanRxMsg * msg)
{
//	v->rate_buf[v->buf_count++] = v->ecd_raw_rate;
//	if(v->buf_count == RATE_BUF_SIZE)
//	{
//		v->buf_count = 0;
//	}
//	//�����ٶ�ƽ��ֵ
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

		if(v->diff < -6500)    //���α������ķ���ֵ���̫�󣬱�ʾȦ�������˸ı�
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
			v->ecd_raw_rate = v->diff;     //ԭʼ�ٶ�
		}

	//����õ������ı��������ֵ
	v->ecd_value = v->raw_value + v->round_cnt * 8192;
	//����õ��Ƕ�ֵ����Χ���������
	v->ecd_angle = (float)(v->raw_value - v->ecd_bias)*360/8192 + v->round_cnt * 360;
		
/*�����˲��ٶ�*/		
	//�ٶ��˲���Ч���ã��ٶȲ�˶���	
	v->rate_buf[v->buf_count++] = v->ecd_raw_rate;
	if(v->buf_count == RATE_BUF_SIZE)
	{
		v->buf_count = 0;
	}
	//�����ٶ�ƽ��ֵ
	for(i = 0;i < RATE_BUF_SIZE; i++)
	{
		temp_sum += v->rate_buf[i];
	}
	v->filter_rate = (int32_t)(temp_sum/RATE_BUF_SIZE);			


}
