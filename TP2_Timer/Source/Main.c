
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
	MyTimer_Struct_TypeDef Timer;
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=9;
	GPIO_StructA0.GPIO_Conf=AltOut_Ppull;
	MyGPIO_Init(&GPIO_StructA0);
	
	Timer.Timer = TIM1;
	Timer.ARR = 9;
	Timer.PSC = 71;

	MyTimer_Base_Init(&Timer);
	MyTimer_Base_Start(TIM1);
	MyTimer_PWM(TIM1, 2);
	MyTimer_PWM_Set_Duty_Cycle(TIM1, 2, 0.2);
	
	MyTimer_ActiveIT(TIM1,10,&(test));
	
	do {
	} while (1);
	
}
