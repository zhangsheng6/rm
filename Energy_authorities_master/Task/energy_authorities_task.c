#include "energy_authorities_task.h"
#include "stdlib.h"//srand

//	  acting  = 1,     //���ڼ���
//	  success = 2,     //����ɹ�
//	  fail    = 4,     //����ʧ��

Armour_Status_Struct  Flabellum_Armour[5] = {0};  //��Ҷ״̬
authorities_Status  running_mode;

extern int  seed;
int rand_num[5]={5,5,5,5,5} ;
unsigned char color = 0;   //��ʼ��Ϊ��ɫ
unsigned char send_data[5]; //can���͵�����
unsigned char time_count=0; //�ж��Ƿ����ʱ
unsigned char flabellum_num,num_c=1;
unsigned char first_creat=1,hitted_count=0;


void Energy_Authorities()	
{  
	 //��ø�һ������ ��������ɫ���ǻ�ɫ
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
//���ϵ磬�����һ����Ҷ׼��
	if(first_creat)     
	{
		flabellum_num = random_number();     //�����Ҷ
		Flabellum_Armour[flabellum_num].ready =1;
	//	light_bar(flabellum_num,off,on);
		first_creat--;
	}  
//***************************������****
//	     delay_ms(1);
//			 Data_Integration(color);
//		   CAN_CMD_msg(send_data);
//**************************************
//���5������װ�װ�Ļ���״̬���������ģʽ=ʧ��
	for(k=0;k<5;k++)
	  {
		   if(Flabellum_Armour[k].hitted==2) //ѡ�б����� hitted=1    δѡ�б����� hitted=2
			 {
		      running_mode = fail;
			 }
//			 if(Flabellum_Armour[k].hitted==1) //ѡ�б����� hitted=1    δѡ�б����� hitted=2
//				 {
//					 light_bar(k,on,on);
//				 }  
		}
//���ĳ����ѡ�е�����װ�װ�Ļ���״̬������ɹ���ѡ����һ�ε�����װ�װ�
  if(Flabellum_Armour[flabellum_num].hitted==1)      //������ȷ����Ҷ
		{   			
			if(hitted_count<5)
		      hitted_count++;	
			
			if(hitted_count>=2)
				 TIM_Cmd(TIM3, DISABLE);		
			Flabellum_Armour[flabellum_num].ready =0;//��ѡ�е�����װ�װ�ȡ��׼��״̬
			
			time_count =0;  //����֮��  ����ʱ���ۼƼ�������
			
			//��һ��ѡ����Ҷ
     if(hitted_count<5)
		 {		 
			 flabellum_num =  random_number();      
			 Flabellum_Armour[flabellum_num].ready =1;
    //   light_bar(flabellum_num,off,on);			 
		 }	
			TIM_Cmd(TIM3, ENABLE); 
		}
		
	//����ɹ�		
		if(hitted_count>=5)  
		{		
			running_mode = success;	
		}	
		 	 Data_Integration(color);
  	   CAN_CMD_msg(send_data);//�ӷ��ͺ���	
}
	


/*
//��5�������ϵĵ������ε���
ͨ��CAN1����5�����εģ���ɫ|׼��״̬|����ģʽ������ɹ�
TIM3����ʹ��

*/
void Success_Task(void)
{
	
 // unsigned char i=0;
   TIM_Cmd(TIM3, DISABLE);
//		for(i=0;i<5;i++)       //���İ���Ҷ��������
//	  {
//      light_bar(i,on,on);			
//		}	
		Data_Integration(color);
	  CAN_CMD_msg(send_data);//�ӷ��ͺ���//can���ͼ���ɹ�
	TIM_Cmd(TIM3, ENABLE);  
}
	

/*
5�������ϵ�װ�װ���Ϣ��0��.ready=0��hitted=0;��ͨ��CAN1���ͣ�����5�����εģ���ɫ|׼��״̬|����ģʽ
TIM3����ʹ��
//5�������ϵĵ���Ϩ��

*/
void Fail_Task(void)
{
  unsigned char i;
	TIM_Cmd(TIM3, DISABLE);
	for(i=0;i<5;i++)       //���İ���Ҷ��������
	  {
			Flabellum_Armour[i].ready=0;
			Flabellum_Armour[i].hitted=0;
    //  light_bar(i,off,off);			
		}
		first_creat=1;
		hitted_count=0;
		time_count=0;  //��ʱ����
		num_c=1;
		for(i=0;i<5;i++)
		  rand_num[i] = 5;
	
		Data_Integration(color);
		CAN_CMD_msg(send_data);//�ӷ��ͺ���,����5�����εģ���ɫ|׼��״̬|����ģʽ
		TIM_Cmd(TIM3, ENABLE);
}


/*
�������ϣ� 5�����εģ���ɫ|׼��״̬|����ģʽ
*/
void Data_Integration(unsigned char COLOR)
	{
		unsigned char k;
    for(k=0;k<5;k++)
		{
    send_data[k] =((COLOR<<5)|Flabellum_Armour[k].ready<<4| running_mode ) ;		
		}
	}
	
	
//���������ͬ�������
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
				 if(rand_num[k]==num) //����ͬ�ĸ�1
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




