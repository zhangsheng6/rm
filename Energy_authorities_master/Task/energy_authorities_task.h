#ifndef _energy_authorities_task_h_
#define _energy_authorities_task_h_

#include "init.h"
//���͵����ݵı�־*******************
//Ҫ���͵�ֵ  color   ready   running_mode
//             5        4      3 2 1 0

#define RED   0  
#define BLUE  1

//�������ؼ���״̬
typedef enum
{
	  acting  = 1,     //���ڼ���
	  success = 2,    //����ɹ�
	  fail    = 4,       //����ʧ��
}authorities_Status;


typedef struct  armour //װ��
{
  unsigned char ready;
  unsigned char hitted;
}Armour_Status_Struct;


extern Armour_Status_Struct  Flabellum_Armour[];  //��Ҷ״̬
extern authorities_Status  running_mode;

extern unsigned char color ;   //��ʼ��Ϊ��ɫ


void Energy_Authorities(void);
void Acting_Task(void);
void Success_Task(void);
void Fail_Task(void);
unsigned char  random_number(void);
void hitted_fail_text(void);

void Data_Integration(unsigned char COLOR);


#endif
