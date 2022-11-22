#include "Driver_ADC.h"

void (*ADCHandlerPointer) (void) ;

void ADC_Init(ADC_TypeDef *ADC, char Channel) {
	
	RCC->CFGR = (RCC->CFGR & ~(0x3 << 14)) | (0x2 << 14);		// Set ADCCLK Speed
	if(ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC1 Clock
	} else if(ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN; // Enable ADC2 Clock
	}
							
	ADC->CR2 |= ADC_CR2_ADON;						// Enable ADC 						
	ADC->CR2 |= ADC_CR2_CAL;						// Start calibration
	
	while((ADC->CR2 >> 2) & 0x1) {			// Wait for calibration
	}
						
	ADC->CR2 |= ADC_CR2_EXTTRIG;				// Set ADC to external trigger		
	ADC->CR2 |= (0x7 << 17);						// Set ADC to software trigger
	
	ADC->SQR3 = (ADC->SQR3 & ~(0x1f << 0)) | (Channel << 0);	// Set channel as first of sequence
	// ADC->SQR1 = (ADC->SQR1 & ~(0xf << 20)) | (0 << 20);		// Set number of channels in sequence
}

void ADC_ActiveIT(ADC_TypeDef *ADC , char Prio, void (*IT_function)(void)) {
	char IRQn;
	
	ADCHandlerPointer = IT_function;
	
	ADC->CR1 |= ADC_CR1_EOCIE;					// Enable interrupt
	
	IRQn = 18;													// Same IRQn for ADC12
	
	NVIC->IP[IRQn] = Prio << 4;
	// IRQn >> 5 pour diviser par 32 car les 32 premiers IRQn sont dans ISER[0] etc ...
	// (1 << IRQn) fonctionne en soit car on est en dessous de 31 
	// Mais (1 << (IRQn & 0x1F)) permet de faire un modulo 32 pour que ça fonctionne même avec plus.
	NVIC->ISER[IRQn >> 5] = (1 << (IRQn & 0x1F)); 
	//NVIC_SetPriority(IRQn,Prio);
	//NVIC_EnableIRQ(IRQn);
}



void ADC_Read(ADC_TypeDef *ADC) {
	//float res;
						
	ADC->CR2 |= ADC_CR2_SWSTART;				// Start conversion
	
	//while((ADC->SR >> 1) & 0x1) {			// Wait for end of conversion
	//}
		
	//res = ADC->DR * (3.3f/4096.0f);
	
	//return res;			// Return result in Volts
}



float ADC_Read_Temp(ADC_TypeDef *ADC) {
	ADC->CR2 |= (0x3 << 22);					// Start conversion
	
	while((ADC->SR >> 1) & 0x1) {			// Wait for end of conversion
	}
	
	return ((1430 - (ADC->DR * (3.3f/4096.0f) * 1000))/4.3f) + 25;			// Return result in °C
}


void ADC1_2_IRQHandler(void) {
	ADC1->SR &= ~(0x1); //Clear EOC Flag
	if (ADCHandlerPointer != 0)
		(*ADCHandlerPointer) ();
}

