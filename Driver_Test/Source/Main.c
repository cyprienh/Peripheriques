
#include "Driver_GPIO.h"
#include "stm32f10x.h"

int main (void) {
	char previous = 0;
	MyGPIO_Struct_TypeDef GPIO_StructA0;
	MyGPIO_Struct_TypeDef GPIO_StructA1;
	MyGPIO_Struct_TypeDef GPIO_StructA2;
	MyGPIO_Struct_TypeDef GPIO_StructB0;
	MyGPIO_Struct_TypeDef GPIO_StructC0;
	MyGPIO_Struct_TypeDef GPIO_StructD0;
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	MyGPIO_Init(&GPIO_StructA0);
	
	GPIO_StructA1.GPIO=GPIOA;
	GPIO_StructA1.GPIO_Pin=15;
	GPIO_StructA1.GPIO_Conf=In_Floating;
	MyGPIO_Init(&GPIO_StructA1);
	
	GPIO_StructA2.GPIO=GPIOA;
	GPIO_StructA2.GPIO_Pin=8;
	GPIO_StructA2.GPIO_Conf=In_PullDown;
	MyGPIO_Init(&GPIO_StructA2);
	
	GPIO_StructB0.GPIO=GPIOB;
	GPIO_StructB0.GPIO_Pin=0;
	GPIO_StructB0.GPIO_Conf=In_PullUp;
	MyGPIO_Init(&GPIO_StructB0);
	
	GPIO_StructC0.GPIO=GPIOC;
	GPIO_StructC0.GPIO_Pin=0;
	GPIO_StructC0.GPIO_Conf=In_Analog;
	MyGPIO_Init(&GPIO_StructC0);
	
	GPIO_StructD0.GPIO=GPIOD;
	GPIO_StructD0.GPIO_Pin=0;
	GPIO_StructD0.GPIO_Conf=Out_OD;
	MyGPIO_Init(&GPIO_StructD0);
	

	do {
		if (previous == 0 && MyGPIO_Read(GPIOA, 15)) {
			previous = 1;
			MyGPIO_Toggle(GPIOA, 0);
		} else {
			previous = 0;
		}
		
	} while (1);
	
}
