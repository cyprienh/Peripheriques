#include "Driver_SysTick.h"

void (*SysTickHandler) (void) ;

// Enable SysTick & Setup SysTick interrupt every ms
void SysTick_Init(void (*IT_function)(void)) {
	int IRQn = SysTick_IRQn;
	
	SysTickHandler = IT_function;
	
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE;
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	
	SysTick->LOAD = 9000;
	
	NVIC->IP[IRQn] = 15 << 4;
	NVIC->ISER[IRQn >> 5] = (1 << (IRQn & 0x1F));
}


void SysTick_Handler(void) {
	if (SysTickHandler != 0)
		(*SysTickHandler) ();
}
