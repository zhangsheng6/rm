
#include "stm32f4xx.h"
#include "PWM_Init_ZS.h"
#include "init.h"

#include "mymath.h"
#define ACCURACY   10000      //�Զ���װ��ֵ
#define INIT_DUTY  500       //��ʼ����



//TIM2->CH2=PB3��Ħ����
u8 PWM_Out_Init_TIM2(uint16_t hz)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
    uint16_t PrescalerValue = 0;
    u32 hz_set = ACCURACY*hz;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	
    hz_set = LIMIT (hz_set,1,84000000);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ø��ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//�ٶ�2MHZ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) ( ( SystemCoreClock/2  ) / hz_set ) - 1;
		
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;//�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�������:TIM����Ƚϼ��Ը�

		
		/* PWM1 Mode configuration: Channel1 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 500;
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);


    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
		
    if( hz_set > 84000000 )
    {
        return 0;
    }
		//����
    else
    {
        return 1;
    }
}





	

//TIM3->CH4=PC9��Ħ����     
u8 PWM_Out_Init_TIM3(uint16_t hz)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
    uint16_t PrescalerValue = 0;
    u32 hz_set = ACCURACY*hz;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	
    hz_set = LIMIT (hz_set,1,84000000);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ø��ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//�ٶ�2MHZ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
 	
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);

	
		
    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) ( ( SystemCoreClock/2  ) / hz_set ) - 1;
		
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;//�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�������:TIM����Ƚϼ��Ը�

	
   	/* PWM1 Mode configuration: Channel4 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		

    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
		
    if( hz_set > 84000000 )
    {
        return 0;
    }
		//����
    else
    {
        return 1;
    }
}


//���
//TIM4->CH3=PB8  TIM4->CH4=PB9
u8 PWM_Out_Init_TIM4(uint16_t hz)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
    uint16_t PrescalerValue = 0;
    u32 hz_set = ACCURACY*hz;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	
    hz_set = LIMIT (hz_set,1,84000000);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ø��ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//�ٶ�2MHZ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) ( ( SystemCoreClock/2  ) / hz_set ) - 1;
		
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;//�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�������:TIM����Ƚϼ��Ը�

		
		/* PWM2 Mode configuration: Channel3 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse =500;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  	/* PWM2 Mode configuration: Channel4 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse =500;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
		
    if( hz_set > 84000000 )
    {
        return 0;
    }
		//����
    else
    {
        return 1;
    }
}





















 






















