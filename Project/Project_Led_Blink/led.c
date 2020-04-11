#include "stm32f10x.h"
GPIO_InitTypeDef GPIO_InitStructure; /*Declare Structure Variable and right-click to goto structure definition*/
static __IO uint32_t TimingDelay; /*Declare a variable for delay*/

/*GPIO Init function Declaration and Definition*/  
void InitGPIO()
{
	/*Function to Enable or Disable the APB2 and right-click to goto function definition*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/*Initialize Structure variables*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	/*Function call for GPIO_Init*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*Timer Init function Declartion and Definition*/
void InitTimer()
{
	/*Function call for Configuring Sys Tick and SystemCoreClock = 72MHz*/
	SysTick_Config(SystemCoreClock / 1000);
}

/*Free Running function for Handling SysTick*/
void SysTick_Handler(void)
{
	if (TimingDelay != 0x00)
		{
			TimingDelay--;
		}
}

/*Delay function Declartion and Definition */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

/*Main function*/
int main()
{
	InitGPIO();
	InitTimer();
	
	while(1)
		{
			/*CLEAR Pin C13*/
			GPIOC->BSRR = GPIO_Pin_13;
			Delay(1000);
			/*SET Pin C13*/
			GPIOC->BRR  = GPIO_Pin_13;
			Delay(1000);
		}
}
