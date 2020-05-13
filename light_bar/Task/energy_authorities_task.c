#include "energy_authorities_task.h"

//	  acting  = 1,     //正在激活
//	  success = 2,     //激活成功
//	  fail    = 4,     //激活失败

armour_status  flabellum[5] = {0};  //扇叶状态
authorities_Status  running_mode;

extern int  seed;
int rand_num[5]={5,5,5,5,5} ;
unsigned char color = 0;   //初始化为红色
unsigned char send_data[5]; //can发送的数据
unsigned char time_count=0; //判断是否击打超时
unsigned char flabellum_num,num_c=1;
unsigned char first_creat=1,hitted_count=0;


void Energy_Authorities()	
{  
	 //最好搞一个按键 决定亮红色还是黄色
   switch(running_mode)
	 { 
		 case acting :
			   Acting_Task(); break;
		 case success :
			   Success_Task();break;
		 case fail :
			   Fail_Task();	  break;
	 }
} 

 
void Acting_Task()
{
//  unsigned char k;
//	for(k=0;k<5;k++)
//	  {
//     if(flabellum[k].ready ==1&&flabellum[k].hitted==0)
//			 {
//        Light_Bar(k,off,on);  //里面的灯灭，外面装甲板周围的灯亮
//			 }
//		if(flabellum[k].hitted==1) //选中被击中 hitted=1    未选中被击中 hitted=2
//			 {
//			  Light_Bar(k,on,on);
//			 }		 
//		if(flabellum[k].hitted==2) //选中被击中 hitted=1    未选中被击中 hitted=2
//		  {
//			 Light_Bar(k,off,off);
//			}				 
//		}	
}
	


/*
把5个扇形上的灯条依次点亮
*/
void Success_Task(void)
{
  unsigned char i=0;
		for(i=0;i<5;i++)       //中心板扇叶参数清零
	  {
      Light_Bar(i,on,on);			
		}	
}
	

/*
5个扇形上的装甲板信息清0
5个扇形上的灯条熄灭
*/
void Fail_Task(void)
{
  unsigned char i;
	for(i=0;i<5;i++)       //中心板扇叶参数清零
	  {
			flabellum[i].ready=0;
			flabellum[i].hitted=0;
      Light_Bar(i,off,off);			
		}	
}


//数据整合
void data_integration(unsigned char COLOR)
	{
		unsigned char k;
    for(k=0;k<5;k++)
		{
    send_data[k] =((COLOR<<5)|flabellum[k].ready<<4| running_mode ) ;		
		}
	}
	
