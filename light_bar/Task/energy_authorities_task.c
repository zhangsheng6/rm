#include "energy_authorities_task.h"

//	  acting  = 1,     //���ڼ���
//	  success = 2,     //����ɹ�
//	  fail    = 4,     //����ʧ��

armour_status  flabellum[5] = {0};  //��Ҷ״̬
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
//  unsigned char k;
//	for(k=0;k<5;k++)
//	  {
//     if(flabellum[k].ready ==1&&flabellum[k].hitted==0)
//			 {
//        Light_Bar(k,off,on);  //����ĵ�������װ�װ���Χ�ĵ���
//			 }
//		if(flabellum[k].hitted==1) //ѡ�б����� hitted=1    δѡ�б����� hitted=2
//			 {
//			  Light_Bar(k,on,on);
//			 }		 
//		if(flabellum[k].hitted==2) //ѡ�б����� hitted=1    δѡ�б����� hitted=2
//		  {
//			 Light_Bar(k,off,off);
//			}				 
//		}	
}
	


/*
��5�������ϵĵ������ε���
*/
void Success_Task(void)
{
  unsigned char i=0;
		for(i=0;i<5;i++)       //���İ���Ҷ��������
	  {
      Light_Bar(i,on,on);			
		}	
}
	

/*
5�������ϵ�װ�װ���Ϣ��0
5�������ϵĵ���Ϩ��
*/
void Fail_Task(void)
{
  unsigned char i;
	for(i=0;i<5;i++)       //���İ���Ҷ��������
	  {
			flabellum[i].ready=0;
			flabellum[i].hitted=0;
      Light_Bar(i,off,off);			
		}	
}


//��������
void data_integration(unsigned char COLOR)
	{
		unsigned char k;
    for(k=0;k<5;k++)
		{
    send_data[k] =((COLOR<<5)|flabellum[k].ready<<4| running_mode ) ;		
		}
	}
	
