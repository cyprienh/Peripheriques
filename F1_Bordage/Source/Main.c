
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Bordage.h"
#include "stm32f10x.h"

float val = 0.07;

int main (void) {
	float Bordage_a;
	float Bordage_Commande;
	GPIO_Struct_TypeDef GPIO_StructA1;
	Timer_Struct_TypeDef Timer;
	
	GPIO_StructA1.GPIO=GPIOA;
	GPIO_StructA1.GPIO_Pin=1;
	GPIO_StructA1.GPIO_Conf=AltOut_Ppull;
	GPIO_Init(&GPIO_StructA1);
	
	Timer.Timer = TIM2;
	Timer.ARR = 1999; //719
	Timer.PSC = 719;//1999

	Timer_Init(&Timer);
	Timer_Start(TIM2);
	Timer_PWM(TIM2, 2);
	
	//Timer_ActiveIT(TIM2,10,&(test));
	
	Bordage_Init();
	//Bordage_Calibration();
	// 45 -> 0
	// 180 -> 90
	while(1) {
		Timer_PWM_Set_Duty_Cycle(TIM2, 2, val);
	}
	
	do {
		Bordage_a = Bordage_Get_Angle() - 180.0;
		if(Bordage_a > 45.0 && Bordage_a < 180.0) {
			Bordage_Commande = (2.0*Bordage_a)/3.0-30.0;
		} else if(Bordage_a < -45.0 && Bordage_a > -180.0) {
			Bordage_Commande = (2.0*(-Bordage_a))/3.0-30.0;
		} else {
			Bordage_Commande = 0.0;
		}
		
	} while (1);
}
