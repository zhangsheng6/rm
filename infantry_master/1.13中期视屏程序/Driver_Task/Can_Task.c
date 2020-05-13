#include "Can_Task.h"

/**
  * @brief  CAN发送任务
  * @param  unused
  * @retval void
	获取OS消息队列里的数据：
	    这里要获取CAN1要发送的数据
	通过OS:CAN1发送数据
*/
void Task_CANSend(void const *argument)
{
    CanSend_Type    CANSendData;
     static u16  flag_led1=0;

    for(;;)
    {
			osMessageQueueGet(CanSend_MessageQueue, &CANSendData, NULL,0xffff);
         if(CANSendData.CANx == CAN1 )
        {
            
//            do
//            {
//                //CAN故障重启
//                if(CAN1->ESR)
//                {
//                    CAN1->MCR |= 0x02;
//                    CAN1->MCR &= 0xFD;
//                }
//            }while(!(CAN1->TSR & 0x1C000000));
            
            CAN_Transmit(CAN1, &(CANSendData.SendCanTxMsg));
        }
        else
        {
//            do
//            {
//                //CAN故障重启
//                if(CAN2->ESR)
//                {
//                    CAN2->MCR |= 0x02;
//                    CAN2->MCR &= 0xFD;
//                }
//            }while(!(CAN2->TSR & 0x1C000000));
//            
            CAN_Transmit(CAN2, &(CANSendData.SendCanTxMsg));
        } 
				if(flag_led1++>=333)
		{
	 	  flag_led1=0;
			//LED1_TOGGLE
		}
    }
}
