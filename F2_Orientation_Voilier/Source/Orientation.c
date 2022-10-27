#include "Orientation.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"

signed char Orientation_RX;

void (*Orientation_IRQHandlerPointer) (void);

/* -----------------------
// Init Orientation
// Set PWM output to PB0
// Set Dir output to PB1
// Set Timer 3
----------------------- */
void Orientation_Init() {
	Timer_Struct_TypeDef Plateau_Timer;
	GPIO_Struct_TypeDef GPIO_Plateau_PWM;
	GPIO_Struct_TypeDef GPIO_Plateau_Dir;
	
	// Plateau PWM
	GPIO_Plateau_PWM.GPIO=GPIOB;
	GPIO_Plateau_PWM.GPIO_Pin=0;
	GPIO_Plateau_PWM.GPIO_Conf=AltOut_Ppull;
	GPIO_Init(&GPIO_Plateau_PWM);
	
	// Plateau Dir
	GPIO_Plateau_Dir.GPIO=GPIOB;
	GPIO_Plateau_Dir.GPIO_Pin=1;
	GPIO_Plateau_Dir.GPIO_Conf=Out_Ppull;
	GPIO_Init(&GPIO_Plateau_Dir);
	
	UART_Init_RX(USART3);
	
	Plateau_Timer.Timer = TIM3;		// 20.5kHz
	Plateau_Timer.ARR = 999;
	Plateau_Timer.PSC = 2;

	Timer_Init(&Plateau_Timer);
	Timer_Start(TIM3);
}

/* -----------------------
// Active Interrupt
// IRQn = 39
// Prio = 10
----------------------- */
void Orientation_ActiveIT(void (*IT_function)(void)) {
	char Prio = 10;
	char IRQn = 39; 									// USART 3 IRQn in RM0008
	
	USART3->CR1 |= (0x1 << 5); 				// Enable RXNEIE (Interrupt when RX) 

	Orientation_IRQHandlerPointer = IT_function;
	
	NVIC->IP[IRQn] = Prio << 4;
	NVIC->ISER[IRQn >> 5] = (1 << (IRQn & 0x1F)); 
}

void Orientation_Receive(void) {
	Orientation_RX = UART_ReadByte(USART3);
}

void USART3_IRQHandler(void) {
	USART3->SR &= ~(0x1 << 5);			// Clear flag
	
	if (Orientation_IRQHandlerPointer != 0)
		(*Orientation_IRQHandlerPointer) ();
}

