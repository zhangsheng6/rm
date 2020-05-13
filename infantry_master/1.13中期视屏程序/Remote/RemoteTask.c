//#include "init.h"
#include "RemoteTask.h"

RC_Ctl_t RC_CtrlData; 

ChassisSpeed_Ref_t ChassisSpeedRef;

RampGen_t frictionRamp = RAMP_GEN_DAFAULT;  //Ħ����б��
RampGen_t LRSpeedRamp = RAMP_GEN_DAFAULT;   //mouse�����ƶ�б��
RampGen_t FBSpeedRamp = RAMP_GEN_DAFAULT;   //mouseǰ���ƶ�б��
int Serve_ref=0;

u8	 Shot_Flag=0,Shot_Flag_Temp=0;
u8	 Friction_Flag=0,Friction_Flag_Temp=0;
u8	 Sero_Flag=0,Sero_Flag_Temp=0;
uint8_t KeyRFlag = 0;
uint8_t ServoState = 0;
uint8_t FrictionState = 0;
uint8_t MouseRFlag = 0;
uint8_t MouseLFlag = 0;

static InputMode_e inputmode = REMOTE_INPUT;   //����ģʽ�趨


/*********************************************************/
//USART���յ���ң�����ݴ��� 
/***********************************************************/
void RemoteDataPrcess(uint8_t *pData)
{
	 Real_Monitor.DBUSFrameCounter++;  //ң��֡
	 if(pData == NULL)
    {
        return;
    }
//ң��------------------------------------------------------------------------------------		
    RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 						//364~1024~1684
    RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;			//364~1024~1684
    RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |								//364~1024~1684
                         ((int16_t)pData[4] << 10)) & 0x07FF;
    RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;				//364~1024~1684
    /*********s1��s2��1��2��3�ֱ��Ӧ�ϡ��¡���************************************************************/
    RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;//���  ������123
    RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);//�ұ� ���ϵ���132
//���------------------------------------------------------------------------------------		

	  RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
    RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
    RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);    

    RC_CtrlData.mouse.press_l = pData[12];
    RC_CtrlData.mouse.press_r = pData[13];
 
//����------------------------------------------------------------------------------------		
    RC_CtrlData.key.v = ((int16_t)pData[14]) | ((int16_t)pData[15] << 8);

		SetInputMode(&RC_CtrlData.rc);
		
		switch(inputmode)
		{
		  case REMOTE_INPUT://ң��������ģʽ	  		
		       RemoteControlProcess(&(RC_CtrlData.rc));
						WorkState_Flag =Normal_State; 	

			break;
			
		  case KEY_MOUSE_INPUT:
						MouseKeyControlProcess(&RC_CtrlData.mouse,&RC_CtrlData.key);
		  			WorkState_Flag =Normal_State; 	

			break;	
			
			case STOP:
		       WorkState_Flag = Stop_State_ZS;
			break;
		
		}



}


/*********************************************************/
//ң��������ģʽ���� 
/***********************************************************/
void RemoteControlProcess(Remote *rc)
{
    //  660*0.75=495
	//��������
	ChassisSpeedRef.forward_back_ref = (rc->ch3 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT;
  ChassisSpeedRef.left_right_ref   = (rc->ch2 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT; 
  
	// ChassisSpeedRef.rotate_ref       = (rc->ch0 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT; 
	//��̨PY����
	//ң��P��Ƕ�+= ��ǰ�����660*0.0035=2.31
	//ң��P��Ƕ�+= �������-660*0.0035=-2.31
	GimbalRef.pitch_angle_dynamic_ref += ((int16_t)REMOTE_CONTROLLER_STICK_OFFSET-rc->ch1 ) * STICK_TO_PITCH_ANGLE_INC_FACT;
	GimbalRef.yaw_angle_dynamic_ref -= ((int16_t)REMOTE_CONTROLLER_STICK_OFFSET-rc->ch0 ) * STICK_TO_YAW_ANGLE_INC_FACT;
	
	//��ʱ �����ڿ� SPEEDPID
	//GMPokeSpeedPID.ref     = (rc->ch1 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT; 
	//��ʱ���Զ��
//	Serve_ref = (rc->ch3 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT;
	
	//��ͣ
//	if(rc->s1==1)
//		WorkState_Flag = Stop_State_ZS;
//	else//ȡ����ͣ
//	{
//	  if(WorkState_Flag ==Stop_State_ZS )//��ͣ��Ҫ�����ָ�����
//			WorkState_Flag =Normal_State; 	
//	}
	//��ʱ����
	// Shot_Flag_Temp=rc->s2;
	
   if(rc->s1==1)
	 {
	    chassisstate = Chassis_CRUISE;
		// SetFrictionWheelSpeed(550);
		 Shot_Flag_Temp=1;
	 } 
	 else if(rc->s1==3)
	 {
	    chassisstate = Chassis_NORAML;
		 		// SetFrictionWheelSpeed(500);
		 Shot_Flag_Temp=2;

	 }
   else	if(rc->s1==2)
	 {
	 	  chassisstate = Chassis_DANCE;
	 }	
}


/*********************************************************/
//�����̿���ģʽ���� 
/***********************************************************/
void MouseKeyControlProcess(Mouse *mouse, Key *key)
{
	static uint16_t forward_back_speed = 0;
	static uint16_t left_right_speed = 0;
//������ ���ϵ縴λ--------------------------------------------	
	
  if(WorkState_Flag!=Prepare_State)
  {
		//speed mode: normal speed/high speed,    key:shift
		if(key->v & Key_SHIFT)
		{
			forward_back_speed =ChassisSpeedParm.high;
		  left_right_speed   =ChassisSpeedParm.high;
		}
		else if(key->v & Key_CTRL)
		{	
			forward_back_speed =  ChassisSpeedParm.low;
			left_right_speed   =  ChassisSpeedParm.low;
		}
		else
		{
			forward_back_speed = ChassisSpeedParm.normal;
			left_right_speed   =ChassisSpeedParm.normal;
		}
		
		
    if(key->v & Key_R)   //�����Ƿ���
		{
			if(KeyRFlag)     //��ֹ����
			{
				KeyRFlag = 0;
								Sero_Flag_Temp=1;


				//Send_Mask^=0xff;//0000 0001
			}
		}
    else
		{
			KeyRFlag = 1;
			Sero_Flag_Temp=2;
		}
		
		
	 
	
		
		if(key->v & Key_E)   //��������
		{
			//SuperCapacitor_State = SuperCapacitor_ON;
					//	ServoState=~ServoState;
		//	KeyEFlag=1;

		}

		/*
    else
		{
			if(KeyEFlag)     //��ֹ����
			{
				SuperCapacitor_State = SuperCapacitor_OFF;
				KeyEFlag = 0;
			}
		}
		*/
		
		if(key->v & Key_Q)
		{
			chassisstate=Chassis_DANCE;				
		}	
		else
		{
			chassisstate=Chassis_NORAML;
		}		
		/*	
		if(FrictionState)
		{
			// lanuch process
			if(key->v & Key_F)
			{
				if(KeyFFlag==1)
				{
					KeyFFlag=0;
					if(Shootstate==Shoot_NS_NF)
					{
					  Shootstate=Shoot_LS_HF;
					}
					else if(Shootstate==Shoot_LS_HF)
					{
					  Shootstate=Shoot_HS_LF;
					}
					else
					{
						Shootstate=Shoot_NS_NF;
					}
					switch(Shootstate)
					{
						case Shoot_NS_NF:   { FriceSpeed_LEVEL=2;PokeSpeed_LEVEL=2;Heat0_reserved=20; }break;	
						case Shoot_LS_HF:   {	FriceSpeed_LEVEL=1;PokeSpeed_LEVEL=3;Heat0_reserved=16; }break;						
						case Shoot_HS_LF:   { FriceSpeed_LEVEL=3;PokeSpeed_LEVEL=1;Heat0_reserved=28; }break;
					}
				}
			}
			else
			{
				KeyFFlag=1;
			}
  	}
     */
		//movement process
		if(key->v & Key_W)  // key: w   ��0��1��û��
		{
//			  ChassisSpeedRef.forward_back_ref = forward_back_speed * FBSpeedRamp.Calc(&FBSpeedRamp);
				ChassisSpeedRef.forward_back_ref = forward_back_speed;
	  }
		else if(key->v & Key_S) //key: s
		{

//			  ChassisSpeedRef.forward_back_ref = -forward_back_speed * FBSpeedRamp.Calc(&FBSpeedRamp);
				ChassisSpeedRef.forward_back_ref = -forward_back_speed;
		}
		else
		{
			ChassisSpeedRef.forward_back_ref = 0;
//			
//			FBSpeedRamp.ResetCounter(&FBSpeedRamp);
//			FBSpeedRamp.ResetCounter(&FBSpeedRamp_1);
		}
		if(key->v & Key_A)  // key: a
		{
//				ChassisSpeedRef.left_right_ref = -left_right_speed* LRSpeedRamp.Calc(&LRSpeedRamp);
			ChassisSpeedRef.left_right_ref = -left_right_speed;
		}
		else if(key->v & Key_D) //key: d
		{
//				ChassisSpeedRef.left_right_ref = left_right_speed* LRSpeedRamp.Calc(&LRSpeedRamp);
			ChassisSpeedRef.left_right_ref = left_right_speed;
		}
		else
		{
			ChassisSpeedRef.left_right_ref = 0;
			//ChassisSpeedRef.forward_back_ref = 0;//zs
//			LRSpeedRamp.ResetCounter(&LRSpeedRamp);
//			LRSpeedRamp.ResetCounter(&LRSpeedRamp_1);
		}	
		
		
	}
	
	

//����״̬�µ����-------------------------------------------		
//step2: gimbal ref calc
    if(WorkState_Flag == Normal_State)
    {
			VAL_LIMIT(mouse->x, -90, 90); 
			VAL_LIMIT(mouse->y, -90, 90); 
		//ң��P��Ƕ�+= �������-660*0.0035=-2.31
			//P��Ƕ�-=90*0.12=10.8
			GimbalRef.pitch_angle_dynamic_ref -= mouse->y* MOUSE_TO_PITCH_ANGLE_INC_FACT;  //(rc->ch3 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_PITCH_ANGLE_INC_FACT;
			//Y��Ƕ�-=90*0.08=7.2
			GimbalRef.yaw_angle_dynamic_ref   += mouse->x* MOUSE_TO_YAW_ANGLE_INC_FACT;
		
		}
	
	/* not used to control, just as a flag
  GimbalRef.pitch_speed_ref = mouse->y;    //speed_ref�����������ж���
  GimbalRef.yaw_speed_ref   = mouse->x; */ 
		
  MouseShootControl(mouse);   //��Ħ���ֿ���״̬����������  
}

 void  MouseShootControl(Mouse *mouse)
 {
// static u32  num=0;
	 if(mouse->press_l==1)
	 {
	    if(MouseLFlag==1)
			{
			   MouseLFlag=0;
				Shot_Flag_Temp=1;//�ڿڵ���趨ֵ+1������һö�ӵ�				
			}	 
	 }
	 else
	 {
	    MouseLFlag=1; 
		 Shot_Flag_Temp=2;
	 }
			
 
	 	 if(mouse->press_r==1)
	 {
	    if(MouseRFlag==1)
			{
			   MouseRFlag=0;
				Friction_Flag_Temp=1;
			//	Sero_Flag_Temp=1;
				LED2_ON
			// FrictionState=~FrictionState;
		//		ServoState=~ServoState;
			}	 
	 }
	 else
	 {
	    MouseRFlag=1; 
		 				Friction_Flag_Temp=2;
		//		Sero_Flag_Temp=2;
	 }
	 

		 
 
 
		 
 
 
 }	 









/*********************************************************/
//����ģʽ���� 
/***********************************************************/
void SetInputMode(Remote *rc)
{
	if(rc->s2 == 1)
	{
		inputmode =STOP ;
	}
	else if(rc->s2 == 3)
	{
		inputmode =REMOTE_INPUT ;
	}
	else if(rc->s2 == 2)
	{
		inputmode =KEY_MOUSE_INPUT ;
	}	
}


//ң�������ݳ�ʼ����б�º����ȵĳ�ʼ��
void RemoteTaskInit()
{
	//б�³�ʼ����Ħ���֣�������ң�ǰ��
	frictionRamp.SetScale(&frictionRamp, FRICTION_RAMP_TICK_COUNT);//
	LRSpeedRamp.SetScale(&LRSpeedRamp, MOUSE_LR_RAMP_TICK_COUNT);
	FBSpeedRamp.SetScale(&FBSpeedRamp, MOUSR_FB_RAMP_TICK_COUNT);
	
	frictionRamp.ResetCounter(&frictionRamp);
	LRSpeedRamp.ResetCounter(&LRSpeedRamp);
	FBSpeedRamp.ResetCounter(&FBSpeedRamp);
	//Systeam_State=Key_Reset; 
	//mousestate=Mouse_NORAML;
	
	//ң�أ����̸���ֵ��ʼ��
	ChassisSpeedRef.forward_back_ref = 0.0f;
	ChassisSpeedRef.left_right_ref = 0.0f;
	ChassisSpeedRef.rotate_ref = 0.0f;
		
	//ң�أ�PY����ֵ��ʼ��
	GimbalRef.pitch_angle_dynamic_ref = 0.0f;
	GimbalRef.yaw_angle_dynamic_ref = 0.0f;
}





