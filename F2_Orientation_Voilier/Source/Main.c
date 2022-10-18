#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"
#include "Orientation.h"

// ------------------------------------------------
// Xbee connecté au USART3
// Plateau Dir to PB1
// Plateau PWM to PB0

// augmenter ARR
// ajouter interruption
// ------------------------------------------------

int main (void) {
	int set = 0;
	float Plateau_DutyCycle;
	Orientation_RX = 0;
	
	Orientation_Init();																// Init GPIO and Timer and USART RX
	Orientation_ActiveIT(&(Orientation_Receive));			// Init Interrupt on USART RX
	
	do {		
		if (Orientation_RX <= 0) {											// Turning left
			Plateau_DutyCycle = (float)(-Orientation_RX)/100;
			
			Timer_PWM(TIM3, 3);												
			Timer_PWM_Set_Duty_Cycle(TIM3, 3, Plateau_DutyCycle);
			GPIO_Reset(GPIOA, 7);											// Set dir bit to 0
			set = 1;
			
		}	else {																		// Turning right
			Plateau_DutyCycle = (float)Orientation_RX/100;
			
			Timer_PWM(TIM3, 3);												
			Timer_PWM_Set_Duty_Cycle(TIM3, 3, Plateau_DutyCycle);
			GPIO_Set(GPIOA, 7);												// Set dir bit to 1
			set = 1;
		}
		
	} while (1);
}
