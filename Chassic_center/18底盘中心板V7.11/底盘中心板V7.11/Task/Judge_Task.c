#include "init.h"

extern u16 USART2_RX_STA;
client_show_data_t Client_Show_Data;
ReadJudgementState_e	ReadJudgementState=NONE_STATE;
//裁判系统数据解析
void Judge_DataVerify(u8 *Buff)
{
	Dateframe_t	*frame;
  if(Buff!=NULL)
  {
		if(USART2_RX_STA&0x8000)//接收完成
		{
			frame=(Dateframe_t *)Buff;
			//将进行帧头与整帧数据CRC校验  帧头CRC8  整帧CRC16
			if(verify_crc8_check_sum((uint8_t *)frame, HEADER_LEN)&&verify_crc16_check_sum((uint8_t *)frame, HEADER_LEN + CMD_LEN + frame->FrameHeader.data_length + CRC_LEN))
			{
				Real_Monitor.Judgement_Recive_FrameCounter++;
				LED3_Runsign(30);
				judgement_data_handler(Buff);  //通过校验进行数据解析
			}
			USART2_RX_STA = 0;
		}
	}
}


void Send_FrameData(judge_data_id_e cmdid, uint8_t * pchMessage,uint8_t dwLength)
{
	uint8_t i;
	uint8_t *addr;
	static Dateframe_t Frame = {.FrameHeader.sof = 0xA5};// 帧
	
	addr = (uint8_t *)&Frame.Data.game_information;
	
	Frame.CmdID = cmdid; //命令
	Frame.FrameHeader.data_length = dwLength;//数据长度
	Frame.FrameHeader.seq++; //帧数
	for(i = 0;i < dwLength;i++)
	{
		*addr++ = *pchMessage++;//数据拷贝
	}
	append_crc8_check_sum((unsigned char *)&Frame.FrameHeader,sizeof(Frame.FrameHeader));//加入帧头校验
	i = sizeof(Frame.FrameHeader) + sizeof(Frame.CmdID)  + sizeof(Frame.CRC16) + dwLength;//计算实际帧的长度
	append_crc16_check_sum((unsigned char *)&Frame,i); //加入整帧校验

  USART_Send_BUFF((uint8_t *)&Frame,i);               //帧发送
}

void Send_Judge_Update(void)
{
	Client_Show_Data.data1 = (float)SendToJudgementData.ShootLevel;
	Client_Show_Data.data2 = (float)SendToJudgementData.SuperCapacitorComment;
	Client_Show_Data.data3 = (float)SendToJudgementData.data3;
	Client_Show_Data.mask	 = (u8)SendToJudgementData.State_Mask;
}
