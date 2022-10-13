
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "stm32f10x.h"

void test(void){
	GPIO_Struct_TypeDef GPIO_StructA0;
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	GPIO_Init(&GPIO_StructA0);
	GPIO_Toggle(GPIOA, 0);
	return;
}

int main (void) {
	float Bordage_a;
	float Bordage_Commande;
	GPIO_Struct_TypeDef GPIO_StructA0;
	Timer_Struct_TypeDef Timer;
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=9;
	GPIO_StructA0.GPIO_Conf=AltOut_Ppull;
	GPIO_Init(&GPIO_StructA0);
	
	Timer.Timer = TIM1;
	Timer.ARR = 9;
	Timer.PSC = 71;

	Timer_Init(&Timer);
	Timer_Start(TIM1);
	Timer_PWM(TIM1, 2);
	
	//Timer_ActiveIT(TIM1,10,&(test));
	
	Timer_Incremental();
	// 45 -> 0
	// 180 -> 90
	do {
		Bordage_a = Timer_Get_Angle() - 180.0;
		if(Bordage_a > 45.0 && Bordage_a < 180.0) {
			Bordage_Commande = (2.0*Bordage_a)/3.0-30.0;
		} else if(Bordage_a < -45.0 && Bordage_a > -180.0) {
			Bordage_Commande = (2.0*(-Bordage_a))/3.0-30.0;
		} else {
			Bordage_Commande = 0.0;
		}
		Timer_PWM_Set_Duty_Cycle(TIM1, 2, Bordage_Commande);
	} while (1);
}
