#include "init.h"
#define Send_Thread 0

/************************************************/
//创建 线程任务:任务初始化过程
/************************************************/
void Calibrate_Thread1 (void const *argument); //校准任务
osThreadId T_Calibrate_ID1;
osThreadDef(Calibrate_Thread1, osPriorityHigh, 1 ,512);

void IMU_Thread1 (void const *argument);//姿态融合 函数
osThreadId T_IMU_ID1; //定义线程ID入口
osThreadDef(IMU_Thread1, osPriorityNormal1, 1, 2048);//定义姿态融合函数为线程任务

void Control_Thread1 (void const *argument);//控制任务 
osThreadId T_Control_ID1;              //线程ID定义
osThreadDef(Control_Thread1, osPriorityNormal1, 1 ,768);//线程定义

void Task_CANSend(void const *argument);//CAN发送任务 
osThreadId T_CANSend_ID1;
osThreadDef(Task_CANSend, osPriorityNormal2, 1 ,256);

void Monitor_Thread1(void const *argument); //监视器任务
osThreadId T_Monitor_ID1;
osThreadDef(Monitor_Thread1, osPriorityNormal, 1 ,256);

#if Send_Thread
void Usart_Send_Thread1(void const *argument); //串口调试波形任务
osThreadId T_Usart_Send_ID1;
osThreadDef(Usart_Send_Thread1, osPriorityNormal3, 1 ,256);
#endif



/************************************************/
//互斥信号初始化过程 保证一次仅有一个线程享用资源
/************************************************/
/************************************************/
//信号量初始化过程  用于进程间通信  
/************************************************/
osSemaphoreId_t GRYO_Semaphore; //得到陀螺仪数据
osSemaphoreDef(GRYO_Semaphore);

osSemaphoreId_t Calibrate_Semaphore; //校准任务
osSemaphoreDef(Calibrate_Semaphore);


/************************************************/
//创建消息队列
/************************************************/
osMessageQueueId_t CanSend_MessageQueue; //CAN发送队列  
osMessageQDef(CanSend_MessageQueue,10,u16);



void Init(void)
{

	Init_Function();
	
	if(osKernelInitialize()!=osOK)
	{
		 while(1);
	}

  //信号量初始化
	GRYO_Semaphore=osSemaphoreNew(1,0,osSemaphore(GRYO_Semaphore));	
	Calibrate_Semaphore=osSemaphoreNew(1,0,osSemaphore(Calibrate_Semaphore));

	
	
	//消息队列 创建+初始化
	CanSend_MessageQueue=osMessageQueueNew(10,sizeof(CanSend_Type),CanSend_MessageQueue);	 
	
	
	//线程任务 创建
	T_IMU_ID1=osThreadCreate(osThread(IMU_Thread1),NULL);	//IMU任务创建
 // T_Calibrate_ID1=osThreadCreate(osThread(Calibrate_Thread1),NULL);	//校准任务创建 
	T_Control_ID1=osThreadCreate(osThread(Control_Thread1),NULL);	//控制任务创建
	T_CANSend_ID1=osThreadCreate(osThread(Task_CANSend),NULL);	//CAN发送任务创建 
  T_Monitor_ID1=osThreadCreate(osThread(Monitor_Thread1),NULL);	//监视器任务创建 

  //错误，屏蔽
	#if Send_Thread
	T_Usart_Send_ID1=osThreadCreate(osThread(Usart_Send_Thread1),NULL);//串口波形调试任务创建
 #endif


	if( osKernelStart()!=osOK) //Start Task Running
	{
	   while(1); 
  }	
	
	
}
//12.24,17周一，可以回家
//1.7,19周周一
//2.4除夕









