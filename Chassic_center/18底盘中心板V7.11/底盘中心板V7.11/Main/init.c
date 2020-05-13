#include "init.h"
#include  "mydelay.h"
#include "BSP_GPIO_Init.h"



void CAN_Thread1 (void const *argument); //CAN���ݷ���
osThreadId T_CAN_ID1;
osThreadDef(CAN_Thread1, osPriorityNormal1, 1 ,512);

void Judge_Thread1 (void const *argument);//��ȡ����ϵͳ
osThreadId T_Judge_ID1;
osThreadDef(Judge_Thread1, osPriorityHigh, 1 ,512);

void PowerMonitor_Thread1 (void const *argument); //��������ת������
osThreadId T_PowerMonitor_ID1;
osThreadDef(PowerMonitor_Thread1, osPriorityNormal1, 1 ,512);

void Monitor_Thread1(void const *argument); //����������
osThreadId T_Monitor_ID1;
osThreadDef(Monitor_Thread1, osPriorityNormal, 1 ,256);

void IMU_Thread1 (void const *argument); //��̬�ں� 
osThreadId T_IMU_ID1;
osThreadDef(IMU_Thread1, osPriorityNormal1, 1, 512);

void PowerSupply_Thread1 (void const *argument); //��̬�ں� 
osThreadId T_PowerSupply_ID1;
osThreadDef(PowerSupply_Thread1, osPriorityNormal1, 1, 512);


/************************************************/
//������Ϣ����
/************************************************/
osSemaphoreId_t GRYO_Semaphore; //�õ�����������
osSemaphoreDef(GRYO_Semaphore);




/*RTXKernelStartInit and Task Creak*/
void KernelTaskInit(void)
{
	/************************************************/
	//�����ʼ������
	/************************************************/
   NVIC_StateInit();
	 BSP_GPIO_Init();
//	 BSP_SuperCapacitor_Init();
//	 TIM3_PWM_Init(100-1,72-1);
	 LED0_ON;
	 LED1_ON;
	 LED2_ON;
	 LED3_ON;
	 delay_ms(200);// ��ʱ��ϵͳ��ʼ����
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
	 //�ź�����ʼ��
	 GRYO_Semaphore=osSemaphoreNew(1,0,osSemaphore(GRYO_Semaphore)); 
	 	 
	 //InitKernel Task
	// T_IMU_ID1=osThreadCreate(osThread(IMU_Thread1),NULL);	//IMU���񴴽�
	 T_CAN_ID1=osThreadCreate(osThread(CAN_Thread1),NULL);	//CANͨ�����񴴽�
   T_Judge_ID1=osThreadCreate(osThread(Judge_Thread1),NULL);//��д����ϵͳ���񴴽�
   T_PowerMonitor_ID1=osThreadCreate(osThread(PowerMonitor_Thread1),NULL);//���ʼ�����񴴽�
  // T_PowerSupply_ID1=osThreadCreate(osThread(PowerSupply_Thread1),NULL);//����ģʽ�л����񴴽�
//	 T_Monitor_ID1=osThreadCreate(osThread(Monitor_Thread1),NULL);	//���������񴴽� 

   if( osKernelStart()!=osOK) //Start Task Running
	 {
	   while(1);
	 }
}

//�ж����ȼ�����
void NVIC_StateInit(void)
{
    NVIC_InitTypeDef 		Nvic_InitStructure;
  	/* Configure one bit for preemption priority */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		/*�ж�����*/
		Nvic_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0�ж�
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //��ռ���ȼ�0
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 0;			  		 //�����ȼ�Ϊ0
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Nvic_InitStructure);
		
		Nvic_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;	  	 //CAN1 TX�ж�
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //��ռ���ȼ�0
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 1;					   //�����ȼ�Ϊ0
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Nvic_InitStructure);
		
		Nvic_InitStructure.NVIC_IRQChannel = USART2_IRQn;      //���ڽ����ж�
		Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
		Nvic_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
		Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&Nvic_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���		
		
		Nvic_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//MPU6050�ж�
    Nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    Nvic_InitStructure.NVIC_IRQChannelSubPriority = 1;
    Nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&Nvic_InitStructure);
}
//��̬���ݸ���
void IMU_Thread1 (void const *argument)
{
  while(1)
	{	
		osSemaphoreAcquire(GRYO_Semaphore,0xffffffff);    //�����ź���
		IMU_Update();
	}
}
//CAN������  
void CAN_Thread1(void const *argument)
{
  while(1)
	{
		CAN_TxMssage();
		osDelay(1);
		LED1_Runsign(500);
	}
}

//����ϵͳ���ݷ���
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
//�������
void PowerMonitor_Thread1(void const *argument)
{
	while(1)
	{
		INA260_DataUpdate();
				LED3_Runsign(500);
		osDelay(2);
	}
}
//���緽ʽ�л�
void PowerSupply_Thread1(void const *argument)
{
	while(1)
	{
		PowerSupply_Task();
		osDelay(2);
	}
}
