//����ʾ������ʾ
#include "USART_Wave_ShanWAI.h"
//������������
float DataScope_OutPut_Buffer[8]={1,2,3,4,5,6,7,8};

//���� һ���ַ�(�ֽ�)������
/*eg��
 UART_PutChar(UART4, 67);//�������ֽ��յ� C
 UART_PutChar(UART4, 68);//�������ֽ��յ� D
*/
void UART_PutChar(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx, (u8)ch);//����һ���ֽ�(8λ)�����ݣ�0-255���յ�����ASCLLֵ
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

//���� һ���ַ�(һ������)������
/*eg:
���������յ�������a�����4���ֽڵ����ݣ�MNOP
   u8 a[4]={77,78,79,80};
   UART_PutCharArr(UART4, a, 4); 
*/
void UART_PutCharArr(USART_TypeDef* USARTx, u8 *ch, u32 len) //int8  int32
{
  while(len--)
  {
    UART_PutChar(USARTx, *(ch++));	
  }
}


/*eg

*/
void UART_PutFloatArr(USART_TypeDef* USARTx, float ch )
{
	static  Data data1;
	 data1.f=ch;	
   UART_PutChar(USARTx, data1.c[0]);	
	 UART_PutChar(USARTx,data1.c[1]);	
	 UART_PutChar(USARTx, data1.c[2]);	
   UART_PutChar(USARTx, data1.c[3]);	
//   UART_PutChar(USARTx, data1.f);	

}

/*eg

*/
void vcan_sendware(USART_TypeDef* USARTx)
{
    #define CMD_WARE     3
		   u8 a[4]={77,78,79,80};

    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��Է���ǰ����
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��Է��ͺ�����
		
    UART_PutCharArr(USARTx, cmdf, sizeof(cmdf));    
    UART_PutCharArr(UART4, a, 4); 
//    UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[0]);
//    UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[1]);
//		UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[2]);		
//		UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[3]);
//		UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[4]);
//		UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[5]);
//	  UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[6]);
//		UART_PutFloatArr(USARTx,DataScope_OutPut_Buffer[7]);
    UART_PutCharArr(USARTx, cmdr, sizeof(cmdr));    

}

