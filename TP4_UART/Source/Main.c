
#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "stm32f10x.h"

int main (void) {
	USART1->CR1 |= (0x1 << 12); 	// Set word length to 9 bits
	USART1->CR1 |= (0x1 << 10);		// Enable parity control
	USART1->CR1 &= ~(0x1 << 9);		// Set to even parity
	
	USART1->CR1 |= (0x1 << 3); 		// Enable transmitter
	USART1->CR2 |= (0x3 << 12); 	// 1 Stop bit
	USART1->CR2 &= ~(0x1 << 11);		// CLK Disable
	
	
	
	do {
	} while (1);
	
}
