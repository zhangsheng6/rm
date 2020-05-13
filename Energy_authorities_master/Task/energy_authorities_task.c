#include "energy_authorities_task.h"
#include "stdlib.h"//srand

//	  acting  = 1,     //正在激活
//	  success = 2,     //激活成功
//	  fail    = 4,     //激活失败

Armour_Status_Struct  Flabellum_Armour[5] = {0};  //扇叶状态
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
  unsigned char k;
//刚上电，随机让一个扇叶准备
	if(first_creat)     
	{
		flabellum_num = random_number();     //随机扇叶
		Flabellum_Armour[flabellum_num].ready =1;
	//	light_bar(flabellum_num,off,on);
		first_creat--;
	}  
//***************************调试用****
//	     delay_ms(1);
//			 Data_Integration(color);
//		   CAN_CMD_msg(send_data);
//**************************************
//检查5个扇形装甲板的击打状态：击打错误，模式=失败
	for(k=0;k<5;k++)
	  {
		   if(Flabellum_Armour[k].hitted==2) //选中被击中 hitted=1    未选中被击中 hitted=2
			 {
		      running_mode = fail;
			 }
//			 if(Flabellum_Armour[k].hitted==1) //选中被击中 hitted=1    未选中被击中 hitted=2
//				 {
//					 light_bar(k,on,on);
//				 }  
		}
//检查某个被选中的扇形装甲板的击打状态：击打成功，选择下一次的扇形装甲板
  if(Flabellum_Armour[flabellum_num].hitted==1)      //击中正确的扇叶
		{   			
			if(hitted_count<5)
		      hitted_count++;	
			
			if(hitted_count>=2)
				 TIM_Cmd(TIM3, DISABLE);		
			Flabellum_Armour[flabellum_num].ready =0;//被选中的扇形装甲板取消准备状态
			
			time_count =0;  //击中之后  击败时间累计计数清零
			
			//下一次选择扇叶
     if(hitted_count<5)
		 {		 
			 flabellum_num =  random_number();      
			 Flabellum_Armour[flabellum_num].ready =1;
    //   light_bar(flabellum_num,off,on);			 
		 }	
			TIM_Cmd(TIM3, ENABLE); 
		}
		
	//激活成功		
		if(hitted_count>=5)  
		{		
			running_mode = success;	
		}	
		 	 Data_Integration(color);
  	   CAN_CMD_msg(send_data);//加发送函数	
}
	


/*
//把5个扇形上的灯条依次点亮
通过CAN1发送5个扇形的：颜色|准备状态|运行模式，激活成功
TIM3重新使能

*/
void Success_Task(void)
{
	
 // unsigned char i=0;
   TIM_Cmd(TIM3, DISABLE);
//		for(i=0;i<5;i++)       //中心板扇叶参数清零
//	  {
//      light_bar(i,on,on);			
//		}	
		Data_Integration(color);
	  CAN_CMD_msg(send_data);//加发送函数//can发送激活成功
	TIM_Cmd(TIM3, ENABLE);  
}
	

/*
5个扇形上的装甲板信息清0，.ready=0，hitted=0;并通过CAN1发送，发送5个扇形的：颜色|准备状态|运行模式
TIM3重新使能
//5个扇形上的灯条熄灭

*/
void Fail_Task(void)
{
  unsigned char i;
	TIM_Cmd(TIM3, DISABLE);
	for(i=0;i<5;i++)       //中心板扇叶参数清零
	  {
			Flabellum_Armour[i].ready=0;
			Flabellum_Armour[i].hitted=0;
    //  light_bar(i,off,off);			
		}
		first_creat=1;
		hitted_count=0;
		time_count=0;  //计时归零
		num_c=1;
		for(i=0;i<5;i++)
		  rand_num[i] = 5;
	
		Data_Integration(color);
		CAN_CMD_msg(send_data);//加发送函数,发送5个扇形的：颜色|准备状态|运行模式
		TIM_Cmd(TIM3, ENABLE);
}


/*
数据整合： 5个扇形的：颜色|准备状态|运行模式
*/
void Data_Integration(unsigned char COLOR)
	{
		unsigned char k;
    for(k=0;k<5;k++)
		{
    send_data[k] =((COLOR<<5)|Flabellum_Armour[k].ready<<4| running_mode ) ;		
		}
	}
	
	
//产生五个不同的随机数
unsigned char  random_number()
{
	unsigned char num,k,count,flag=1;	  
     while(flag)
		 { 
				count=0;
				srand(seed);
				num = rand()%5;
				for(k=0;k<num_c;k++)  //num_c=1
				{
				 if(rand_num[k]==num) //有相同的给1
					count=1;
				}

				if(count==0)
				{		 
				 flag =0;
				 num_c++;
				 rand_num[hitted_count] = num;
				}
		 }
  return num;
}




