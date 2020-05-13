#include "init.h"
#include "Thread_ZS.h"
#include "UART_Data_ZS.h"
#include "UART_Send_ZS.h"
SystemMonitor Real_Monitor;  //����֡  
SystemMonitor Rate_Monitor;  //����֡  

 uint16_t SysErrorStatus = 0;   



/****************************************************************/	
//�����շ��߳�----------------------------------------------------------------
/****************************************************************/
void Usart_Send_Thread1(void const *argument)
{
 static u16  flag_led1=0;

 while(1)
  {	 
	  
		if(flag_led1++>=333)
		{
	 	  flag_led1=0;
			//LED1_TOGGLE
		}

	  //vcan_sendware(UART4);
		osDelay(1);
	}
	
}



/****************************************************************/	
//�����߳�-------------------------------------------------------------------
/****************************************************************/
void Control_Thread1 (void const *argument)
{
//	/*�����ݽ��д���
//�Ѵ������ĵĵ�����������CAN1���棬
//����CAN1Ҫ���͵����ݷŽ�OS��Ϣ��������*/
 static u16  flag_led2=0;
 while(1)
  {	 	  

		Control_Task(); 


		if(flag_led2++>=333)
		{
	 	  flag_led2=0;
	//		LED1_TOGGLE
		}
		osDelay(1);
	}
}



/****************************************************************/	
//9250�߳�-------------------------------------------------------------------
/****************************************************************/
void IMU_Thread1 (void const *argument)
{
	 static u16  flag_led4=0;

  while(1)
	{	

    osSemaphoreAcquire(GRYO_Semaphore,0xffffffff); //�������������ݶ�ȡ ���޵ȴ� 
    IMU_Update();	
	//	 MPU9250_Read_Data_ZS();
			  UART_Data_Learn_ZS();		
				if(flag_led4++>=333)
		{
	 	flag_led4=0;
	 // LED2_TOGGLE
		}
		
		osDelay(1);
	
	}
}



/****************************************************************/	
//У׼�߳�-------------------------------------------------------------------
/****************************************************************/
void Calibrate_Thread1 (void const *argument)
{
  while(1)
  {		
		osSemaphoreAcquire(Calibrate_Semaphore,0xffffffff);
		//CanTransferDisplay();//������ʾ����Ļ
	//	CalibrateLoop();   //У׼���񣬵����յ�У׼��������Чִ�У�����ֱ������  
		//У׼�����ƫ��ֵ��ʼ������У׼���ֵ������������
	  //Sensor_Offset_Param_Init(&gAppParamStruct); 
	}
}










/****************************************************************/	
//�����̣߳���������շ������Ƿ�ͨ��-------------------------------------------------------------------
/****************************************************************/
void Monitor_Thread1 (void const *argument)
{
//ϵͳ״̬��ÿһλ��Ӧһ������0������1����
/****************************************************************
    15  |   14  |   13  |   12  |   11  |   10 |   9   |   8     |
        |       |       |       |  ���� |  IMU | PC�Ӿ� | ����ϵͳ|
-----------------------------------------------------------------
    7   |   6   |   5   |   4      |   3      |   2   |   1   |   0   |
���̵���|�Һ����|������|��ǰ����| ��ǰ���� |  Yaw  | Pitch |  DBUS |
****************************************************************/
	

	while(1)
	{
		
		memcpy(&Rate_Monitor,&Real_Monitor,sizeof(SystemMonitor));
		memset(&Real_Monitor,0,sizeof(SystemMonitor));   //���ṹ������������
	
		//DBUS֡�ʹ���
		if(Rate_Monitor.DBUSFrameCounter<12)
		{
		  SysErrorStatus|=(1<<0);//
		}
		else
		{
		  SysErrorStatus&=~(1<<0);
		}
		
		
		 //Pitch��̨֡�ʹ���
		if(Rate_Monitor.PitchFrameCounter<30)
		{
		  SysErrorStatus|=(1<<1);
		}
		else
		{
		  SysErrorStatus&=~(1<<1);
		}
		
		
		//Yaw��̨֡�ʹ���
		if(Rate_Monitor.YawFrameCounter<30)
		{
		  SysErrorStatus|=(1<<2);
		}
		else
		{
		  SysErrorStatus&=~(1<<2);
		}
		
		
		//1�ŵ�� 
		if(Rate_Monitor.ChassisFrameCounter_1<30)
		{
		  SysErrorStatus|=(1<<3);
		}
		else
		{
		  SysErrorStatus&=~(1<<3);
		}
		
		
		//2�ŵ�� 
		if(Rate_Monitor.ChassisFrameCounter_2<30)
		{
		  SysErrorStatus|=(1<<4);
		}
		else
		{
		  SysErrorStatus&=~(1<<4);
		}
		
		
		//3�ŵ�� 
		if(Rate_Monitor.ChassisFrameCounter_3<30)
		{
		  SysErrorStatus|=(1<<5);
		}
		else
		{
		  SysErrorStatus&=~(1<<5);
		}
		
		
		//4�ŵ�� 
		if(Rate_Monitor.ChassisFrameCounter_4<30)
		{
		  SysErrorStatus|=(1<<6);
		}
		else
		{
		  SysErrorStatus&=~(1<<6);
		}
		
		
		//IMU���֡
		if(Rate_Monitor.IMUFrameCounter<12)
		{
		  SysErrorStatus|=(1<<7);
		}
	  else
		{
		  SysErrorStatus&=~(1<<7);
		}	
		
		
		if(SysErrorStatus)  //�д���֡���ݳ���
		{	
//			LED2_ON
//	  workState = ERR_STATE;  	
		}
		else
		{		  
		  LED2_OFF
		}
		
 
	  osDelay(300);
	}

}	
	
	
	
	


