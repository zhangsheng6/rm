#ifndef _energy_authorities_task_h_
#define _energy_authorities_task_h_

#include "init.h"
//发送的数据的标志*******************
//要发送的值  color   ready   running_mode
//             5        4      3 2 1 0

#define RED   0  
#define BLUE  1

//能量机关激活状态
typedef enum
{
	  acting  = 1,     //正在激活
	  success = 2,    //激活成功
	  fail    = 4,       //激活失败
}authorities_Status;


typedef struct  armour //装甲
{
  unsigned char ready;
  unsigned char hitted;
}Armour_Status_Struct;


extern Armour_Status_Struct  Flabellum_Armour[];  //扇叶状态
extern authorities_Status  running_mode;

extern unsigned char color ;   //初始化为红色


void Energy_Authorities(void);
void Acting_Task(void);
void Success_Task(void);
void Fail_Task(void);
unsigned char  random_number(void);
void hitted_fail_text(void);

void Data_Integration(unsigned char COLOR);


#endif

