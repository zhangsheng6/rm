

//´®¿Ú1

#ifndef __USARTREVICE_H__
#define __USARTREVICE_H__

#include "init.h"


#define  BSP_USART1_DMA_RX_BUF_LEN               30u                   
#define  RC_FRAME_LENGTH                         18u

void USART1_Configuration(uint32_t baud_rate);
void ReviceHandloop(void );
typedef enum
{
	MeMoryOne = 0,
	MeMoryTwo = 1,
}ReviceState;


#endif
