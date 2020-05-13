#include "Can_Task.h"

/**
  * @brief  CAN��������
  * @param  unused
  * @retval void
	��ȡOS��Ϣ����������ݣ�
	    ����Ҫ��ȡCAN1Ҫ���͵�����
	ͨ��OS:CAN1��������
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
//                //CAN��������
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
//                //CAN��������
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
