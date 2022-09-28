
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"

void test(void){
	MyGPIO_Struct_TypeDef GPIO_StructA0;
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	MyGPIO_Init(&GPIO_StructA0);
	MyGPIO_Toggle(GPIOA, 0);
	return;
}

int main (void) {
	MyGPIO_Struct_TypeDef GPIO_StructA0;
	MyTimer_Struct_TypeDef Timer2;
	char previous = 0;
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	MyGPIO_Init(&GPIO_StructA0);
	
	Timer2.Timer = TIM1;
	Timer2.ARR = 999;
	Timer2.PSC = 35999;

	MyTimer_Base_Init(&Timer2);
	MyTimer_Base_Start(TIM1);
	
	MyTimer_ActiveIT(TIM1,10,&(test));
	
	do {
		/*if(previous == 0 && TIM2->CNT == 999) {
			previous = 1;
			
		} else if(TIM2->CNT == 0) {
			previous = 0;
		}*/
	} while (1);
	
}
