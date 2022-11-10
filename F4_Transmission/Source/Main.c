#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"
#include "Transmission.h"


int main (void) {
	GPIO_Struct_TypeDef GPIO_StructC4;
	
	GPIO_StructC4.GPIO=GPIOC;
	GPIO_StructC4.GPIO_Pin=4;
	GPIO_StructC4.GPIO_Conf=In_Analog;
	GPIO_Init(&GPIO_StructC4);
	
	Transmission_Init();
	ADC_Init(ADC1, 14); //Init ADC to read battery	
	
	do {		
		
	} while (1);
}
