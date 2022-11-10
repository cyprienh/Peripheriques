#include "Driver_ADC.h"

void ADC_Init(ADC_TypeDef *ADC, char Channel) {
	
	RCC->CFGR = (RCC->CFGR & ~(0x3 << 14)) | (0x2 << 14);		// Set ADCCLK Speed
	if(ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC1 Clock
	} else if(ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN; // Enable ADC2 Clock
	}
	
	ADC->CR2 |= (0x1 << 0); 						// Enable ADC 
	ADC->CR2 |= (0x1 << 2);							// Start calibration
	
	while((ADC->CR2 >> 2) & 0x1) {			// Wait for calibration
	}
	
	ADC->CR2 |= (0x1 << 20);						// Set ADC to external trigger
	ADC->CR2 |= (0x7 << 17);						// Set ADC to software trigger
	
	ADC->SQR3 = (ADC->SQR3 & ~(0x1f << 0)) | (Channel << 0);	// Set channel as first of sequence
	// ADC->SQR1 = (ADC->SQR1 & ~(0xf << 20)) | (0 << 20);				// Set number of channels in sequence

	ADC1->SMPR1 |= (0x7 << 18);					// Set sample time to max
}

float ADC_Read(ADC_TypeDef *ADC) {
	float res;
	
	ADC->CR2 |= (0x1 << 22);					// Start conversion
	
	while((ADC->SR >> 1) & 0x1) {			// Wait for end of conversion
	}
		
	res = ADC->DR * (3.3f/4096.0f);
	
	return res;			// Return result in Volts
}

float ADC_Read_Temp(ADC_TypeDef *ADC) {
	ADC->CR2 |= (0x3 << 22);					// Start conversion
	
	while((ADC->SR >> 1) & 0x1) {			// Wait for end of conversion
	}
	
	return ((1430 - (ADC->DR * (3.3f/4096.0f) * 1000))/4.3f) + 25;			// Return result in �C
}
