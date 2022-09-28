

#include "stm32f10x.h"

int main (void) {
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
	// APB2ENR |= 0x00011100(soit 0x1C)
	// LED verte (LD2) = PA5 (pin 21) ou PB13 (pin 34), if HIGH, LED is on
	// User Button = I/O PC13 (pin 2)
	
	
	// Bouton poussoir externe sur PA1
	// LED externe sur PA0
	
	// Configure poussoir en floating input
	GPIOA->CRL = (GPIOA->CRL & ~(0x3 << 4)) | ((0x0 << 4)); // MODE1
	GPIOA->CRL = (GPIOA->CRL & ~(0x3 << 6)) | ((0x1 << 6)); // CNF1
	
	// Configure LED en output push pull
	GPIOA->CRL = (GPIOA->CRL & ~(0x3 << 0)) | ((0x1 << 0)); // MODE0
	GPIOA->CRL = (GPIOA->CRL & ~(0x3 << 2)) | ((0x1 << 2)); // CNF0

	do {
		if ((GPIOA->IDR >> 1) & 0x1) {
			GPIOA->ODR |= 0x1;
		} else {
			GPIOA->ODR &= 0x0;
		}
		
	} while (1);
	
}
