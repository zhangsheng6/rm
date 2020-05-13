#include "BSP_ADC_Init.h"
#include  "String.h"
u16 ADC1_Get_Channel[ADC1_Channel_Num];//ʵʱADֵ
u16 ADC1_Real_Channel[ADC1_Channel_Num];//ʵʱADֵ
void BSP_ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);   //ADCʱ�ӣ�72/8=9<14(ʱ��ӦС��14M)
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ģʽ(������ADC1)
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת�����������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = ADC1_Channel_Num;	//˳����й���ת����ADCͨ������Ŀ
	
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_71Cycles5 );//ADC1,ͨ��1��ת������,����ʱ��Ϊ71.5����
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,3,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,4,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,5,ADC_SampleTime_71Cycles5 );
	
	
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_DMACmd(ADC1,ENABLE);	//ʹ��ADC1��DMAͨ��
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
  
	while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����
	DMA_forADC1_Init();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}
static void DMA_forADC1_Init(void)
{
	DMA_InitTypeDef	DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
	DMA_DeInit(DMA1_Channel1);//DMA��λ
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&(ADC1->DR);		//�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)ADC1_Get_Channel;	//�洢������ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;							//���䷽��:���赽�洢��
	DMA_InitStructure.DMA_BufferSize=ADC1_Channel_Num;						//��������С(ʵ������ָÿ�δ��������������Ŀ)
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;					//��������ַ����
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//�������ݿ��
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//�洢�����ݿ��
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;									//����ģʽ(2��)
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;							//���ȼ�(4��)
	DMA_InitStructure.DMA_M2M=DISABLE;														//������to����������
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE); //��DMA��������ж�
  DMA_Cmd(DMA1_Channel1, ENABLE);  //ʹ��
}
void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1)==SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC1);
		memcpy(ADC1_Real_Channel,ADC1_Get_Channel,10); //����Copy
	}
}
