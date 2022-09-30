
#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "stm32f10x.h"

int main (void) {
	float Vr;
	GPIO_Struct_TypeDef GPIO_StructA0;
	GPIO_Struct_TypeDef GPIO_StructA1;
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	GPIO_Init(&GPIO_StructA0);
	
	GPIO_StructA1.GPIO=GPIOA;
	GPIO_StructA1.GPIO_Pin=1;
	GPIO_StructA1.GPIO_Conf=In_Analog;
	GPIO_Init(&GPIO_StructA1);
	
	ADC_Init(ADC1, 1);
	
	// Faire des trucs avec l'interrupt EOC
	do {
		Vr = ADC_Read(ADC1);
		if(Vr > 2.0f) {
			GPIO_Set(GPIOA, 0);
		} else {
			GPIO_Reset(GPIOA, 0);
		}
	} while (1);
	
}
