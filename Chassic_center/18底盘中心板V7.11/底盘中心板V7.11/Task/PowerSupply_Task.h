#ifndef __POWERSUPPLY_TASK_H_
#define __POWERSUPPLY_TASK_H_


//��������
typedef enum
{
	 SuperCapacitor_OFF = 0,//��ؿ������ݹأ�����
   SuperCapacitor_ON = 1,//��عأ����ݿ�������
	 SuperCapacitor_Charge = 2,//��ؿ������ݹأ���翪
}SuperCapacitor_State_e;




extern SuperCapacitor_State_e SuperCapacitor_State;

void PowerSupply_Task(void);

#endif

