#include "init.h"
#define Send_Thread 0

/************************************************/
//���� �߳�����:�����ʼ������
/************************************************/
void Calibrate_Thread1 (void const *argument); //У׼����
osThreadId T_Calibrate_ID1;
osThreadDef(Calibrate_Thread1, osPriorityHigh, 1 ,512);

void IMU_Thread1 (void const *argument);//��̬�ں� ����
osThreadId T_IMU_ID1; //�����߳�ID���
osThreadDef(IMU_Thread1, osPriorityNormal1, 1, 2048);//������̬�ںϺ���Ϊ�߳�����

void Control_Thread1 (void const *argument);//�������� 
osThreadId T_Control_ID1;              //�߳�ID����
osThreadDef(Control_Thread1, osPriorityNormal1, 1 ,768);//�̶߳���

void Task_CANSend(void const *argument);//CAN�������� 
osThreadId T_CANSend_ID1;
osThreadDef(Task_CANSend, osPriorityNormal2, 1 ,256);

void Monitor_Thread1(void const *argument); //����������
osThreadId T_Monitor_ID1;
osThreadDef(Monitor_Thread1, osPriorityNormal, 1 ,256);

#if Send_Thread
void Usart_Send_Thread1(void const *argument); //���ڵ��Բ�������
osThreadId T_Usart_Send_ID1;
osThreadDef(Usart_Send_Thread1, osPriorityNormal3, 1 ,256);
#endif



/************************************************/
//�����źų�ʼ������ ��֤һ�ν���һ���߳�������Դ
/************************************************/
/************************************************/
//�ź�����ʼ������  ���ڽ��̼�ͨ��  
/************************************************/
osSemaphoreId_t GRYO_Semaphore; //�õ�����������
osSemaphoreDef(GRYO_Semaphore);

osSemaphoreId_t Calibrate_Semaphore; //У׼����
osSemaphoreDef(Calibrate_Semaphore);


/************************************************/
//������Ϣ����
/************************************************/
osMessageQueueId_t CanSend_MessageQueue; //CAN���Ͷ���  
osMessageQDef(CanSend_MessageQueue,10,u16);



void Init(void)
{

	Init_Function();
	
	if(osKernelInitialize()!=osOK)
	{
		 while(1);
	}

  //�ź�����ʼ��
	GRYO_Semaphore=osSemaphoreNew(1,0,osSemaphore(GRYO_Semaphore));	
	Calibrate_Semaphore=osSemaphoreNew(1,0,osSemaphore(Calibrate_Semaphore));

	
	
	//��Ϣ���� ����+��ʼ��
	CanSend_MessageQueue=osMessageQueueNew(10,sizeof(CanSend_Type),CanSend_MessageQueue);	 
	
	
	//�߳����� ����
	T_IMU_ID1=osThreadCreate(osThread(IMU_Thread1),NULL);	//IMU���񴴽�
 // T_Calibrate_ID1=osThreadCreate(osThread(Calibrate_Thread1),NULL);	//У׼���񴴽� 
	T_Control_ID1=osThreadCreate(osThread(Control_Thread1),NULL);	//�������񴴽�
	T_CANSend_ID1=osThreadCreate(osThread(Task_CANSend),NULL);	//CAN�������񴴽� 
  T_Monitor_ID1=osThreadCreate(osThread(Monitor_Thread1),NULL);	//���������񴴽� 

  //��������
	#if Send_Thread
	T_Usart_Send_ID1=osThreadCreate(osThread(Usart_Send_Thread1),NULL);//���ڲ��ε������񴴽�
 #endif


	if( osKernelStart()!=osOK) //Start Task Running
	{
	   while(1); 
  }	
	
	
}
//12.24,17��һ�����Իؼ�
//1.7,19����һ
//2.4��Ϧ









