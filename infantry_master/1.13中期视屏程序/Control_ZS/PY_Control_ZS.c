#include "PY_Control_ZS.h"

PID GMPPositionPID;
PID GMYPositionPID;

PID GMPSpeedPID;
PID GMYSpeedPID;

RampGen_t GMPitchRamp = RAMP_GEN_DAFAULT;		//��̨pitch��б��
RampGen_t GMYawRamp = RAMP_GEN_DAFAULT;			//��̨yaw��б��
u16 guodu_count=0;

Gimbal_Ref_t GimbalRef;

u8 yaw_ready=0;
/****************************************************************/	
//PY�� ׼��ģʽ��������ģʽ+ȷ��λ��PID������ֵ��ʵ��ֵ-------------------------------------------------------------------
/****************************************************************/
void GimbalYaw_PitchControlModeSwitch(void)
{
static uint8_t normalFlag = 0;   //��������ģʽ��־
static uint8_t prepareFlag = 1;  //IMU����ģʽ��־
static float angleSave = 0.0f;    //�����л�ģʽʱ�����л�ǰ�ĽǶ�ֵ�����ڽǶȸ���ֵ�л�
	
	switch(WorkState_Flag)
	{
		
	  case  Prepare_State :
		{		
			if(prepareFlag == 1)
			{
				prepareFlag = 0;														
				normalFlag = 1;
			}
			
		  GMYPositionPID.ref = 0.0f;
			GMPPositionPID.ref = 0.0f;
			
			                  //����б�£����ܸտ�ʼ�Ƕ�̫�󣬵���̫�󣬻���ת�������
			                    //�������Ƕ� *б�¹�һֵ(����500ms,��0����1) 
			//����ʵ��ֵ+
			GMYPositionPID.fdb =- GMYawEncoder.ecd_angle*GMYawRamp.Calc(&GMYawRamp);
			//���µ�ͷ���趨ֵ+
			GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle * GMPitchRamp.Calc(&GMPitchRamp); 
						
			angleSave = yaw_angle;

		}		
		break;
		
		
		case   Normal_State :
		{
			//		LED1_ON
       //   LED2_ON			
			if(normalFlag == 1)										
			{
				prepareFlag = 1;														
				normalFlag = 0;
				//׼��״̬�չ��������ҽǶ��趨ֵΪ+
				GimbalRef.yaw_angle_dynamic_ref = angleSave;   //�޸��趨ֵΪSTANDBY״̬�¼�¼�����һ��ZGYROMODULEAngleֵ��ƽ�ȹ���				
		   //GMPitchRamp.ResetCounter(&GMPitchRamp);
	    // GMYawRamp.ResetCounter(&GMYawRamp);
			}

	
			GMYPositionPID.ref = GimbalRef.yaw_angle_dynamic_ref;   //�趨����ֵ
			GMPPositionPID.ref = GimbalRef.pitch_angle_dynamic_ref;
			
			//�������--------------------------------------------------
			if(guodu_count++<2000)
			{
 			GMYPositionPID.fdb =yaw_angle*GMYawRamp.Calc(&GMYawRamp);
			GMPPositionPID.fdb = - GMPitchEncoder.ecd_angle * GMPitchRamp.Calc(&GMPitchRamp); 
				//yaw_ready=1;
			}
			else
			{
			//���ң�ʵ��ֵ
	   // GMYPositionPID.fdb = -GMYawEncoder.ecd_angle;//ȡ���ʱ�� ʵ��ֵ �õı������Ƕ�
	    //���ң�ʵ��ֵ+			
			GMYPositionPID.fdb = yaw_angle;//����ʱ���õ�ŷ����
			//���µ�ͷ���趨ֵ+
	    GMPPositionPID.fdb = -GMPitchEncoder.ecd_angle;
					
			}
			
			
						angleSave = yaw_angle;

/*
	 Y��ͨ����Ƭ����λ��������Ƭ��λ��ȷ�� 0�Ƕ�
	 P��ͨ�����趨�ı�������ʼ�Ƕ�ȷ�� 0�Ƕ�
*/	
		}		
		break;	

		case   Stop_State_ZS :
		{
		
		}		
		break;
			
	 default:
	 break;

	}

}

/*
�����������ã�
GMPositionPID�ģ�
  ���ո�λʱ��׼��״̬��
	    �趨ֵ=0������ֵ=�������Ƕ�*б�¹�һϵ��(��0����1����һ��) 
������ʱ������״̬��
	    �趨ֵ=ң�ش���ֵ��
      Y������ֵ=9250��yaw�Ƕ�ֵ
      P������ֵ=�������Ƕ�
*/
/****************************************************************/	
//��̨pitch����Ƴ���-------------------------------------------------------------------
/****************************************************************/
void GMPitchControlLoop(void)
{
/*
��ͷ�趨ֵ13�Ƕȶ� ʵ��0�Ƕ�   �⻷���13
�ڻ��趨13���ٶ�   ʵ�ʽ��ٶ�0 pwm13
	
��ͷ�趨ֵ13�Ƕȶ� ʵ��3�Ƕ�   �⻷���10
�ڻ��趨10���ٶ�   ʵ�ʽ��ٶ�3 pwm7
eg��
�ڻ��趨0���ٶ�   ʵ�ʽ��ٶ�13 pwm-13
ң���²���ң�ؽǶ��趨��
��̨��ͷ���������Ƕ���
��̨��ͷ��9259�Ƕ���
*/
	PID_Set(&GMPPositionPID,GMPPID_Position.P,GMPPID_Position.I,GMPPID_Position.D);	
	PID_Control_Position(&GMPPositionPID);   //�õ�pitch��λ�û����������
	
	//pitch speed control  
	GMPSpeedPID.ref = GMPPositionPID.pid_out;//�ٶ�PID��ʵ��ֵ=λ��PID�����	
	//���µ�ͷ���趨ֵ-
	GMPSpeedPID.fdb = -MPU6050_Real_Data.Gyro_X;//
  PID_Set(&GMPSpeedPID,GMPPID_Speed.P,GMPPID_Speed.I,GMPPID_Speed.D);
	PID_Control_Position(&GMPSpeedPID); 
}

/****************************************************************/	
//��̨YAW�������13000+-  -------------------------------------------------------------------
/****************************************************************/
void GMYawControlLoop(void)
{
  PID_Set(&GMYPositionPID,GMYPID_Position.P,GMYPID_Position.I,GMYPID_Position.D);
	PID_Control_Position(&GMYPositionPID);

	//yaw speed control	
	GMYSpeedPID.ref = GMYPositionPID.pid_out;	
	//ʵ��ֵ ������
	GMYSpeedPID.fdb = -MPU6050_Real_Data.Gyro_Z;
	PID_Set(&GMYSpeedPID,GMYPID_Speed.P,GMYPID_Speed.I,GMYPID_Speed.D);
	PID_Control_Position(&GMYSpeedPID);			
}


/****************************************************************/	
//ң��������ֵ����,���������Сֵ-------------------------------------------------------------------
/*P��
����
     ң�����ýǶ�0�ȵ�35��
     �������Ƕȣ���̨��ͷΪ0�ȣ���̨�м�17.5�ȣ�̧ͷ35�� 
zs: 
      ң�����ýǶ�-35�ȵ�35��
     �������Ƕȣ��м�0�ȣ���̨̧ͷ35�ȣ���̨��ͷ-35�� 
ң��һֱ������ǰ�棬��̨35�ȣ���̨��ͷ
ң��һֱ��������棬��̨-35�ȣ���̨̧ͷ
*/
/****************************************************************/

void PYAngleLimit(void)
{
/*
P�᣺
 Ŀǰ���������޽Ƕ��� -33�ȵ�13��֮��仯
 ��������΢�ı��������ʼƫ��ֵ	���Ƕȷ����ı䣬��������ֵ�ı�
 ����е������/���˳�/��̨�� ������ĳ�ʼƫ��ֵ���ܴ��ı䣬
Y�᣺	
	Ŀǰ9250���޽Ƕ� ��223�ȷ�Χ֮��
	��Ƭ����λ��ʼ��9250����IMU�߳�֮��ĳ�ʼֵ��Ϊyaw�ǵ�0�Ƚ�
	��̨�ڲ�ͬ���������󣬳�ʼ��λ��Ϊ0�Ƚǣ��������� ����֮ǰ û������Y�Ἣ�޽Ƕ�
*/
	//0��35��
  //VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -PITCH_MAX-35, PITCH_MAX+15);	//ȥ����������	
  VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -PITCH_MAX-27, PITCH_MAX+27.5f);	//������������	
  //���޲��ܳ�����ǰ�Ƕȵ�20��
	VAL_LIMIT(GimbalRef.yaw_angle_dynamic_ref, GMYPositionPID.fdb -YAW_MAX, GMYPositionPID.fdb+ YAW_MAX);	
  //������  
	//���εĻ�������һֱ���� ��ת��̨����
	//VAL_LIMIT(GimbalRef.pitch_angle_dynamic_ref, -230, 230);		

}










