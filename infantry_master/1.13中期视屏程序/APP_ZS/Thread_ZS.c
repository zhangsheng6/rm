#include "init.h"
#include "Thread_ZS.h"
#include "UART_Data_ZS.h"
#include "UART_Send_ZS.h"
SystemMonitor Real_Monitor;  //计数帧  
SystemMonitor Rate_Monitor;  //速率帧  

 uint16_t SysErrorStatus = 0;   



/****************************************************************/	
//串口收发线程----------------------------------------------------------------
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
//控制线程-------------------------------------------------------------------
/****************************************************************/
void Control_Thread1 (void const *argument)
{
//	/*对数据进行处理，
//把处理最后的的电流数据送入CAN1里面，
//并把CAN1要发送的数据放进OS消息队列里面*/
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
//9250线程-------------------------------------------------------------------
/****************************************************************/
void IMU_Thread1 (void const *argument)
{
	 static u16  flag_led4=0;

  while(1)
	{	

    osSemaphoreAcquire(GRYO_Semaphore,0xffffffff); //请求陀螺仪数据读取 无限等待 
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
//校准线程-------------------------------------------------------------------
/****************************************************************/
void Calibrate_Thread1 (void const *argument)
{
  while(1)
  {		
		osSemaphoreAcquire(Calibrate_Semaphore,0xffffffff);
		//CanTransferDisplay();//数据显示到屏幕
	//	CalibrateLoop();   //校准任务，当接收到校准命令后才有效执行，否则直接跳过  
		//校准后参数偏差值初始化，将校准后的值赋给各个变量
	  //Sensor_Offset_Param_Init(&gAppParamStruct); 
	}
}










/****************************************************************/	
//监视线程：检查数据收发错误，是否通信-------------------------------------------------------------------
/****************************************************************/
void Monitor_Thread1 (void const *argument)
{
//系统状态，每一位对应一个错误，0正常，1错误
/****************************************************************
    15  |   14  |   13  |   12  |   11  |   10 |   9   |   8     |
        |       |       |       |  拨弹 |  IMU | PC视觉 | 裁判系统|
-----------------------------------------------------------------
    7   |   6   |   5   |   4      |   3      |   2   |   1   |   0   |
底盘电流|右后底盘|左后底盘|左前底盘| 右前底盘 |  Yaw  | Pitch |  DBUS |
****************************************************************/
	

	while(1)
	{
		
		memcpy(&Rate_Monitor,&Real_Monitor,sizeof(SystemMonitor));
		memset(&Real_Monitor,0,sizeof(SystemMonitor));   //将结构体内数据清零
	
		//DBUS帧率过低
		if(Rate_Monitor.DBUSFrameCounter<12)
		{
		  SysErrorStatus|=(1<<0);//
		}
		else
		{
		  SysErrorStatus&=~(1<<0);
		}
		
		
		 //Pitch云台帧率过低
		if(Rate_Monitor.PitchFrameCounter<30)
		{
		  SysErrorStatus|=(1<<1);
		}
		else
		{
		  SysErrorStatus&=~(1<<1);
		}
		
		
		//Yaw云台帧率过低
		if(Rate_Monitor.YawFrameCounter<30)
		{
		  SysErrorStatus|=(1<<2);
		}
		else
		{
		  SysErrorStatus&=~(1<<2);
		}
		
		
		//1号电机 
		if(Rate_Monitor.ChassisFrameCounter_1<30)
		{
		  SysErrorStatus|=(1<<3);
		}
		else
		{
		  SysErrorStatus&=~(1<<3);
		}
		
		
		//2号电机 
		if(Rate_Monitor.ChassisFrameCounter_2<30)
		{
		  SysErrorStatus|=(1<<4);
		}
		else
		{
		  SysErrorStatus&=~(1<<4);
		}
		
		
		//3号电机 
		if(Rate_Monitor.ChassisFrameCounter_3<30)
		{
		  SysErrorStatus|=(1<<5);
		}
		else
		{
		  SysErrorStatus&=~(1<<5);
		}
		
		
		//4号电机 
		if(Rate_Monitor.ChassisFrameCounter_4<30)
		{
		  SysErrorStatus|=(1<<6);
		}
		else
		{
		  SysErrorStatus&=~(1<<6);
		}
		
		
		//IMU输出帧
		if(Rate_Monitor.IMUFrameCounter<12)
		{
		  SysErrorStatus|=(1<<7);
		}
	  else
		{
		  SysErrorStatus&=~(1<<7);
		}	
		
		
		if(SysErrorStatus)  //有错误帧数据出现
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
	
	
	
	


