//串口示波器显示
#include "USART_Wave_ShanWAI.h"
//发送数据数组
float DataScope_OutPut_Buffer[8]={1,2,3,4,5,6,7,8};

//发送 一个字符(字节)的数据
/*eg：
 UART_PutChar(UART4, 67);//串口助手接收到 C
 UART_PutChar(UART4, 68);//串口助手接收到 D
*/
void UART_PutChar(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx, (u8)ch);//发送一个字节(8位)的数据：0-255，收到的是ASCLL值
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

//发送 一串字符(一组数组)的数据
/*eg:
串口助手收到了数组a里面的4个字节的数据，MNOP
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

    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试发送前命令
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试发送后命令
		
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

