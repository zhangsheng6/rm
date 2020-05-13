#include "init.h"
#include  "mydelay.h"
#include "BSP_GPIO_Init.h"



void CAN_Thread1 (void const *argument); //CAN数据发送
osThreadId T_CAN_ID1;
osThreadDef(CAN_Thread1, osPriorityNormal1, 1 ,512);

void Judge_Thread1 (void const *argument);//读取裁判系统
osThreadId T_Judge_ID1;
osThreadDef(Judge_Thread1, osPriorityHigh, 1 ,512);

void PowerMonitor_Thread1 (void const *argument); //电流数据转化接收
osThreadId T_PowerMonitor_ID1;
osThreadDef(PowerMonitor_Thread1, osPriorityNormal1, 1 ,512);

void Monitor_Thread1(void const *argument); //监视器任务
osThreadId T_Monitor_ID1;
osThreadDef(Monitor_Thread1, osPriorityNormal, 1 ,256);

void IMU_Thread1 (void const *argument); //姿态融合 
osThreadId T_IMU_ID1;
osThreadDef(IMU_Thread1, osPriorityNormal1, 1, 512);

void PowerSupply_Thread1 (void const *argument); //姿态融合 
osThreadId T_PowerSupply_ID1;
osThreadDef(PowerSupply_Thread1, osPriorityNormal1, 1, 512);


/************************************************/
//创建消息队列
/************************************************/
osSemaphoreId_t GRYO_Semaphore; //得到陀螺仪数据
osSemaphoreDef(GRYO_Semaphore);




/*RTXKernelStartInit and Task Creak*/
void KernelTaskInit(void)
{
	/************************************************/
	//外设初始化过程
	/************************************************/
   NVIC_StateInit();
	 BSP_GPIO_Init();
//	 BSP_SuperCapacitor_Init();
//	 TIM3_PWM_Init(100-1,72-1);
	 LED0_ON;
	 LED1_ON;
	 LED2_ON;
	 LED3_ON;
	 delay_ms(200);// 延时后系统开始启动
   BSP_Can_Init();
	 BSP_USART2_Init(115200);
	 INA_Init();
  // MPU_Init();
	 LED0_OFF;
	 LED1_OFF;
	 LED2_OFF;
	 LED3_OFF;
   if(osKernelInitialize()!=osOK)
	 {
		 while(1);
	 }
	 //信号量初始化
	 GRYO_Semaphore=osSemaphoreNew(1,0,osSemaphore(GRYO_Semaphore)); 
	 	 
	 //InitKernel Task
	// T_IMU_ID1=osThreadCreate(osThread(IMU_Thread1),NULL);	//IMU任务创建
	 T_CAN_ID1=osThreadCreate(osThread(CAN_Thread1),NULL);	//CAN通信任务创建
   T_Judge_ID1=osThreadCreate(osThread(Judge_Thread1),NULL);//读写裁判系统任务创建
   T_PowerMonitor_ID1=osThreadCreate(osThread(PowerMonitor_Thread1),NULL);//功率监测任务创建
  // T_PowerSupply_ID1=osThreadCreate(osThread(PowerSupply_Thread1),NULL);//供电模式切换任务创建
//	 T_Monitor_ID1=osThreadCreate(osThread(Monitor_Thread1),NULL);	//监视器任务创建 

   if( osKernelStart()!=osOK) //Start Task Running
	 {
	   while(1);
	 }
}

//中断优先级定义
void NVIC_StateInit(void)
{
    NVIC_InitTypeDef 		Nvic_InitStructure;
  	/* Configure one bit for preemption priority */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		/*中断设置*/
		Nvic_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0中断
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //抢占优先级0
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 0;			  		 //子优先级为0
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Nvic_InitStructure);
		
		Nvic_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;	  	 //CAN1 TX中断
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //抢占优先级0
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 1;					   //子优先级为0
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Nvic_InitStructure);
		
		Nvic_InitStructure.NVIC_IRQChannel = USART2_IRQn;      //串口接收中断
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&Nvic_InitStructure);	//根据指定的参数初始化VIC寄存器		
		
		Nvic_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//MPU6050中断
    Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    Nvic_InitStructure.NVIC_IRQChannelSubPriority = 1;
    Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&Nvic_InitStructure);
}
//姿态数据更新
void IMU_Thread1 (void const *argument)
{
  while(1)
	{	
		osSemaphoreAcquire(GRYO_Semaphore,0xffffffff);    //请求信号量
		IMU_Update();
	}
}
//CAN任务发送  
void CAN_Thread1(void const *argument)
{
  while(1)
	{
		CAN_TxMssage();
		osDelay(1);
		LED1_Runsign(500);
	}
}

//裁判系统数据发送
void Judge_Thread1(void const *argument)
{
  while(1)
	{
		static u8 Send_timesFlag=0;
		Send_timesFlag++;
		
		Judge_DataVerify(USART2_Get_Channel);
		if(Send_timesFlag==1)
		{
			Send_timesFlag=0;
			Send_Judge_Update();
			Send_FrameData(STU_CUSTOM_DATA_ID,(uint8_t *)&Client_Show_Data,sizeof(Client_Show_Data));
		}
		LED2_Runsign(500);
		osDelay(5);
	}
}
//电流检测
void PowerMonitor_Thread1(void const *argument)
{
	while(1)
	{
		INA260_DataUpdate();
				LED3_Runsign(500);
		osDelay(2);
	}
}
//供电方式切换
void PowerSupply_Thread1(void const *argument)
{
	while(1)
	{
		PowerSupply_Task();
		osDelay(2);
	}
}
