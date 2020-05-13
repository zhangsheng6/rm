#include "BSP_ADC_Init.h"
#include  "String.h"
u16 ADC1_Get_Channel[ADC1_Channel_Num];//实时AD值
u16 ADC1_Real_Channel[ADC1_Channel_Num];//实时AD值
void BSP_ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);   //ADC时钟：72/8=9<14(时钟应小于14M)
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立模式(即仅用ADC1)
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = ADC1_Channel_Num;	//顺序进行规则转换的ADC通道的数目
	
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_71Cycles5 );//ADC1,通道1，转换排序,采样时间为71.5周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,3,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,4,ADC_SampleTime_71Cycles5 );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,5,ADC_SampleTime_71Cycles5 );
	
	
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_DMACmd(ADC1,ENABLE);	//使能ADC1的DMA通道
	
	ADC_ResetCalibration(ADC1);	//使能复位校准
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
  
	while(ADC_GetCalibrationStatus(ADC1)); //等待校准结束
	DMA_forADC1_Init();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
}
static void DMA_forADC1_Init(void)
{
	DMA_InitTypeDef	DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
	DMA_DeInit(DMA1_Channel1);//DMA复位
	
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&(ADC1->DR);		//外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)ADC1_Get_Channel;	//存储器基地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;							//传输方向:外设到存储器
	DMA_InitStructure.DMA_BufferSize=ADC1_Channel_Num;						//缓冲区大小(实际上是指每次传输的数据量的数目)
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址增量
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;					//储存器地址增量
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//外设数据宽度
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//存储器数据宽度
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;									//传输模式(2种)
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;							//优先级(4种)
	DMA_InitStructure.DMA_M2M=DISABLE;														//储存器to储存器传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE); //打开DMA传输完成中断
  DMA_Cmd(DMA1_Channel1, ENABLE);  //使能
}
void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1)==SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC1);
		memcpy(ADC1_Real_Channel,ADC1_Get_Channel,10); //数据Copy
	}
}
