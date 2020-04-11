#include "stm32f10x.h"
#include "stm32f10x_conf.h"

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    uint16_t TxData = 0;
    uint16_t RxData = 0;
    
    /* Enable peripheral clocks for USART1 on GPIOA */
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_USART1 |
        RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_AFIO, ENABLE);
        
    /* Configure PA9 and PA10 as USART1 TX/RX */
    
    /* PA9 = alternate function push/pull output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* PA10 = floating input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure and initialize usart... */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        
    USART_Init(USART1, &USART_InitStructure);
    
    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);

    /*Function to Enable or Disable the APB2 and right-click to goto function definition*/
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
	  /* Configure PC13 for On-board LED */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		
	  /*Function call for GPIO_Init*/
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

    while (1)
    {
			TxData = 0xDA;
			
			/* Write a byte */
			USART_SendData(USART1, TxData);
                
      /* Wait until the byte has been transmitted */
      while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
			
      /* Wait until there's data in the receive data register */
      while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        
      /* Read a byte */
      RxData = USART_ReceiveData(USART1);
			
			if(TxData == RxData){
				
				/* SET the On-board LED on PC13 */
				GPIOC->BRR  = GPIO_Pin_13;
			}
			
    }
}
