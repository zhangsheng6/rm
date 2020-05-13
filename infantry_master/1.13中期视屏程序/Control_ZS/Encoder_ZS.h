#ifndef _Encoder_ZS_H_
#define _Encoder_ZS_H_

#include "init.h"
#include "stm32f4xx_can.h"
typedef struct{
	int32_t raw_value;   									//���������������ԭʼֵ
	int32_t last_raw_value;								//��һ�εı�����ԭʼֵ
	int32_t ecd_value;                       //��������������ı�����ֵ
	int32_t diff;													//���α�����֮��Ĳ�ֵ
	int32_t temp_count;                   //������
	uint8_t buf_count;								//�˲�����buf��
	int32_t ecd_bias;											//��ʼ������ֵ	
	int32_t ecd_raw_rate;									//ͨ������������õ����ٶ�ԭʼֵ
	int32_t rate_buf[RATE_BUF_SIZE];	//buf��for filter
	int32_t round_cnt;										//Ȧ��
	int32_t filter_rate;											//�ٶ�
	float ecd_angle;											//�Ƕ�
	float ecd_angle_abs;											//�Ƕ�
	int32_t encoder_zhuansu;											
	int32_t encoder_dianliu;										
	int32_t encoder_wendu;											
 // int32_t motor_current;
	u8 first;
}Encoder;


extern volatile Encoder CM1Encoder;
extern volatile Encoder CM2Encoder;
extern volatile Encoder CM3Encoder;
extern volatile Encoder CM4Encoder;
extern volatile Encoder GMPokeEncoder;
extern volatile Encoder GMYawEncoder ;
extern volatile Encoder GMPitchEncoder ;
extern volatile ChassisCenter_t ChassisCenter;   //���̵���ֵ
extern volatile JudgeMent  Real_JudgeMent; //����ϵͳֵ

void EncoderProcess(volatile Encoder *v, CanRxMsg * msg);
void GetEncoderBias(volatile Encoder *v, CanRxMsg * msg);

#endif
