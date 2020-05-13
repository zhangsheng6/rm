#ifndef _Encoder_ZS_H_
#define _Encoder_ZS_H_

#include "init.h"
#include "stm32f4xx_can.h"
typedef struct{
	int32_t raw_value;   									//编码器不经处理的原始值
	int32_t last_raw_value;								//上一次的编码器原始值
	int32_t ecd_value;                       //经过处理后连续的编码器值
	int32_t diff;													//两次编码器之间的差值
	int32_t temp_count;                   //计数用
	uint8_t buf_count;								//滤波更新buf用
	int32_t ecd_bias;											//初始编码器值	
	int32_t ecd_raw_rate;									//通过编码器计算得到的速度原始值
	int32_t rate_buf[RATE_BUF_SIZE];	//buf，for filter
	int32_t round_cnt;										//圈数
	int32_t filter_rate;											//速度
	float ecd_angle;											//角度
	float ecd_angle_abs;											//角度
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
extern volatile ChassisCenter_t ChassisCenter;   //底盘电流值
extern volatile JudgeMent  Real_JudgeMent; //裁判系统值

void EncoderProcess(volatile Encoder *v, CanRxMsg * msg);
void GetEncoderBias(volatile Encoder *v, CanRxMsg * msg);

#endif
