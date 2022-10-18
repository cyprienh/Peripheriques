
#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"

// ------------------------------------------------
// Xbee connecté au USART3
// Plateau Dir to PA7
// Plateau PWM to PA6
// ------------------------------------------------

int main (void) {
	int set = 0;
	int Plateau_RX;
	float Plateau_DutyCycle;
	
	Timer_Struct_TypeDef Plateau_Timer;
	GPIO_Struct_TypeDef GPIO_Plateau_PWM;
	GPIO_Struct_TypeDef GPIO_Plateau_Dir;
	
	// Plateau PWM
	GPIO_Plateau_PWM.GPIO=GPIOA;
	GPIO_Plateau_PWM.GPIO_Pin=6;
	GPIO_Plateau_PWM.GPIO_Conf=AltOut_Ppull;
	GPIO_Init(&GPIO_Plateau_PWM);
	
	// Plateau Dir
	GPIO_Plateau_Dir.GPIO=GPIOA;
	GPIO_Plateau_Dir.GPIO_Pin=7;
	GPIO_Plateau_Dir.GPIO_Conf=Out_Ppull;
	GPIO_Init(&GPIO_Plateau_Dir);
	
	UART_Init_RX(USART3);
	
	Plateau_Timer.Timer = TIM3;		// 20.5kHz
	Plateau_Timer.ARR = 9;
	Plateau_Timer.PSC = 350;

	Timer_Init(&Plateau_Timer);
	Timer_Start(TIM3);
	
	do {
		// ReadByte bloquante jusqu'à recevoir l'octet
		Plateau_RX = UART_ReadByte(USART3);		
		
		if (Plateau_RX >= 0x9C) {										// Turning left
			// y(x) = -1.01 * (plateau_rx) + 255
			Plateau_DutyCycle = (-1.01*Plateau_RX + 255)/100;
			
			Timer_PWM(TIM3, 1);												
			Timer_PWM_Set_Duty_Cycle(TIM3, 1, Plateau_DutyCycle);
			GPIO_Reset(GPIOA, 7);											// Set dir bit to 0
			
		}	else {																		// Turning right
			Plateau_DutyCycle = (float)Plateau_RX/100;
			
			Timer_PWM(TIM3, 1);												
			Timer_PWM_Set_Duty_Cycle(TIM3, 1, Plateau_DutyCycle);
			GPIO_Set(GPIOA, 7);												// Set dir bit to 1
		}
		
		if (set == 1)
			while (1);
		
	} while (1);
}
