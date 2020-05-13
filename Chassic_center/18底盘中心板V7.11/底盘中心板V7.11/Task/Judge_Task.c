#include "init.h"

extern u16 USART2_RX_STA;
client_show_data_t Client_Show_Data;
ReadJudgementState_e	ReadJudgementState=NONE_STATE;
//����ϵͳ���ݽ���
void Judge_DataVerify(u8 *Buff)
{
	Dateframe_t	*frame;
  if(Buff!=NULL)
  {
		if(USART2_RX_STA&0x8000)//�������
		{
			frame=(Dateframe_t *)Buff;
			//������֡ͷ����֡����CRCУ��  ֡ͷCRC8  ��֡CRC16
			if(verify_crc8_check_sum((uint8_t *)frame, HEADER_LEN)&&verify_crc16_check_sum((uint8_t *)frame, HEADER_LEN + CMD_LEN + frame->FrameHeader.data_length + CRC_LEN))
			{
				Real_Monitor.Judgement_Recive_FrameCounter++;
				LED3_Runsign(30);
				judgement_data_handler(Buff);  //ͨ��У��������ݽ���
			}
			USART2_RX_STA = 0;
		}
	}
}


void Send_FrameData(judge_data_id_e cmdid, uint8_t * pchMessage,uint8_t dwLength)
{
	uint8_t i;
	uint8_t *addr;
	static Dateframe_t Frame = {.FrameHeader.sof = 0xA5};// ֡
	
	addr = (uint8_t *)&Frame.Data.game_information;
	
	Frame.CmdID = cmdid; //����
	Frame.FrameHeader.data_length = dwLength;//���ݳ���
	Frame.FrameHeader.seq++; //֡��
	for(i = 0;i < dwLength;i++)
	{
		*addr++ = *pchMessage++;//���ݿ���
	}
	append_crc8_check_sum((unsigned char *)&Frame.FrameHeader,sizeof(Frame.FrameHeader));//����֡ͷУ��
	i = sizeof(Frame.FrameHeader) + sizeof(Frame.CmdID)  + sizeof(Frame.CRC16) + dwLength;//����ʵ��֡�ĳ���
	append_crc16_check_sum((unsigned char *)&Frame,i); //������֡У��

  USART_Send_BUFF((uint8_t *)&Frame,i);               //֡����
}

void Send_Judge_Update(void)
{
	Client_Show_Data.data1 = (float)SendToJudgementData.ShootLevel;
	Client_Show_Data.data2 = (float)SendToJudgementData.SuperCapacitorComment;
	Client_Show_Data.data3 = (float)SendToJudgementData.data3;
	Client_Show_Data.mask	 = (u8)SendToJudgementData.State_Mask;
}
