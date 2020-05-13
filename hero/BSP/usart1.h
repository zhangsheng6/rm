#ifndef __USART1_H__
#define __USART1_H__

#include "main.h"


#define  BSP_USART1_DMA_RX_BUF_LEN               30u                   
#define  RC_FRAME_LENGTH                         18u

void USART1_Configuration(uint32_t baud_rate);

#endif
