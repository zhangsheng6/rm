#include "ADC_Task.h"
#include "math.h"
#include "BSP_ADC_Init.h"
#include "judgement_info.h"
extern receive_judge_t judge_rece_mesg;
Current Real_Current;//����ϵͳ������ĵ���ֵ
Current Raw_Current;//ʵ�������ĵ���
Current Offest_Current;  //��׼ֵ

float ADC1_Get_Channel_renewal[ADC1_Channel_Num];//���ڸ��µ����� 
u8 Time=0;          //�ɼ�����
u8 flag=0;


//ADC���ݲɼ�����
void ADC1_Data_processing(void)
{
  if(flag==0&&Time>=Count)
  {
	   flag=Offest_flag;
		 Time=0;
		 //����ȡƽ��
	   ADC1_Get_Channel_renewal[0]=ADC1_Get_Channel_renewal[0]/Count;
		 ADC1_Get_Channel_renewal[1]=ADC1_Get_Channel_renewal[1]/Count;
		 ADC1_Get_Channel_renewal[2]=ADC1_Get_Channel_renewal[2]/Count;
		 ADC1_Get_Channel_renewal[3]=ADC1_Get_Channel_renewal[3]/Count;
		 ADC1_Get_Channel_renewal[4]=ADC1_Get_Channel_renewal[4]/Count;
		 //�õ���ѹ��׼
		 Offest_Current.Ch1=ADC1_Get_Channel_renewal[4];		
		 Offest_Current.Ch2=ADC1_Get_Channel_renewal[3];
		 Offest_Current.Ch3=ADC1_Get_Channel_renewal[1];
		 Offest_Current.Ch4=ADC1_Get_Channel_renewal[0];
		 Offest_Current.Ch_Ref=ADC1_Get_Channel_renewal[2];
		
		 ADC1_Get_Channel_renewal[0]=0;
		 ADC1_Get_Channel_renewal[1]=0;
		 ADC1_Get_Channel_renewal[2]=0;
		 ADC1_Get_Channel_renewal[3]=0;
		 ADC1_Get_Channel_renewal[4]=0;
	}
	else if(flag==Offest_flag&&Time>=Count)
	{
  	 Time=0;
		 //����ȡƽ��
		 ADC1_Get_Channel_renewal[0]=ADC1_Get_Channel_renewal[0]/Count;
		 ADC1_Get_Channel_renewal[1]=ADC1_Get_Channel_renewal[1]/Count;
		 ADC1_Get_Channel_renewal[2]=ADC1_Get_Channel_renewal[2]/Count;
		 ADC1_Get_Channel_renewal[3]=ADC1_Get_Channel_renewal[3]/Count;
		 ADC1_Get_Channel_renewal[4]=ADC1_Get_Channel_renewal[4]/Count;
		
		 Raw_Current.Ch1=fabs((Offest_Current.Ch1-ADC1_Get_Channel_renewal[4])*0.00447591);		
		 Raw_Current.Ch2=fabs((Offest_Current.Ch2-ADC1_Get_Channel_renewal[3])*0.00447591);
		 Raw_Current.Ch3=fabs((Offest_Current.Ch3-ADC1_Get_Channel_renewal[1])*0.00447591);
		 Raw_Current.Ch4=fabs((Offest_Current.Ch4-ADC1_Get_Channel_renewal[0])*0.00447591);
		 Raw_Current.Ch_Ref=fabs((Offest_Current.Ch_Ref-ADC1_Get_Channel_renewal[2])*0.00447591);
		
		 Raw_Current.Ch_In=Raw_Current.Ch1+Raw_Current.Ch2+Raw_Current.Ch3+Raw_Current.Ch4;   //ͨ���������
		 Raw_Current.ch_err=judge_rece_mesg.real_powerheat_data.chassisCurrent-Raw_Current.Ch_In;   //���������
		
		 //�����ϵͳ�������ݲ�ֵ����
		 Real_Current.Ch1=Raw_Current.Ch1+Raw_Current.ch_err*0.25f;
		 Real_Current.Ch2=Raw_Current.Ch2+Raw_Current.ch_err*0.25f;
		 Real_Current.Ch3=Raw_Current.Ch3+Raw_Current.ch_err*0.25f;
		 Real_Current.Ch4=Raw_Current.Ch4+Raw_Current.ch_err*0.25f;
		 Real_Current.Ch_In=Real_Current.Ch1+Real_Current.Ch2+Real_Current.Ch3+Real_Current.Ch4;   //ͨ���������
		 Real_Current.ch_err=judge_rece_mesg.real_powerheat_data.chassisCurrent-Real_Current.Ch_In;   //���������	
	   //��������
		 ADC1_Get_Channel_renewal[0]=0;
		 ADC1_Get_Channel_renewal[1]=0;
		 ADC1_Get_Channel_renewal[2]=0;
		 ADC1_Get_Channel_renewal[3]=0;
		 ADC1_Get_Channel_renewal[4]=0;
	}
	else
  {
		ADC1_Get_Channel_renewal[0]+=ADC1_Real_Channel[0];
		ADC1_Get_Channel_renewal[1]+=ADC1_Real_Channel[1];
		ADC1_Get_Channel_renewal[2]+=ADC1_Real_Channel[2];
		ADC1_Get_Channel_renewal[3]+=ADC1_Real_Channel[3];
		ADC1_Get_Channel_renewal[4]+=ADC1_Real_Channel[4];
		Time++;
	}
}






