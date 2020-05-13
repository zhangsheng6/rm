#include "init.h"
#include "stm32f10x.h"                  // Device header

SystemMonitor Real_Monitor;  //����֡  
SystemMonitor Rate_Monitor;  //����֡  
/**
  * @brief  ����������
  * @param  unused
  * @retval voif
  */

uint16_t SysErrorStatus = 0;   
void Monitor_Thread1 (void const *argument)
{
//ϵͳ״̬��ÿһλ��Ӧһ������0������1����
/*************************************************************************
    15  |   14  |   13   |   12     |   11     |   10   |   9   |   8    |
        |       |        |          |          |        |       |        |
--------------------------------------------------------------------------
    7   |   6   |   5    |   4      |   3      |   2     |   1   |   0   |
        |       |        |CAN_Recive|CAN_Sent  |Judgement| INA260|MPU6050|
**************************************************************************/
	
//ָʾ�ƣ����ϵ�����led��˸��ʾû�д��󣬳����д�
//				���ŵĵ�һ��Ϊ��ȡINA,�ڶ���Ϊ��ȡ����ϵͳ��������ΪCAN����


	while(1)
	{
		memcpy(&Rate_Monitor,&Real_Monitor,sizeof(SystemMonitor));
		memset(&Real_Monitor,0,sizeof(SystemMonitor));   //���ṹ������������
		//��ȡMPU6050
		if(Rate_Monitor.IMUFrameCounter<15)
		{
		  SysErrorStatus|=(1<<0);
		}
		else
		{
		  SysErrorStatus&=~(1<<0);
		}
		 //��ȡINA260
		if(Rate_Monitor.INA260FrameCounter<15)
		{
		  SysErrorStatus|=(1<<1);
		}
		else
		{
			LED1_Runsign(2);
		  SysErrorStatus&=~(1<<1);
		}
		//��ȡ����ϵͳ����
		if(Rate_Monitor.Judgement_Recive_FrameCounter<10)
		{
			ReadJudgementState=NONE_STATE;
		  SysErrorStatus|=(1<<2);
		}
		else
		{
			ReadJudgementState=NORMAL_STATE;//�ö�ȡ״̬��־Ϊ1
		  SysErrorStatus&=~(1<<2);
		}
		//CAN��������
		if(Rate_Monitor.CAN_Send_FrameCounter<80)
		{
//		  SysErrorStatus|=(1<<3);
		}
		else
		{
		  SysErrorStatus&=~(1<<3);
		}
		//CAN��������
		if(Rate_Monitor.CAN_Recive_FrameCounter<30)
		{
//		  SysErrorStatus|=(1<<4);
		}
		else
		{
		  SysErrorStatus&=~(1<<4);
		}

		if(SysErrorStatus)  //�д���֡���ݳ���
		{
			LED0_ON;
		}
		else
		{
			LED0_Runsign(3);
		}

	  osDelay(300);
	}

}
	
	
	
	


