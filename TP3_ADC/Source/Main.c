
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"


int main (void) {
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC Clock1
	ADC1->CR2 |= (0x1 << 0); // Enable ADC 
	// Lancer calibration
	// Attendre fin calibration avec while bit not 1
	// Mettre ADC en mode external trigger
	// Activer un bit et lancer la conversion.
	do {
	} while (1);
	
}
