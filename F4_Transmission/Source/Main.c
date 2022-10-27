#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"
#include "Transmission.h"


int main (void) {
	// Limite de roulis : interruption via Maïlis 
	
	Transmission_Init();
	ADC_Init(ADC1, 1); //Init ADC to read battery	
	
	do {		
		
	} while (1);
}
