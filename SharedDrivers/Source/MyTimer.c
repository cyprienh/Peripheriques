#include "MyTimer.h"

void (*IRQHandlerPointer) (void) ;

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer) {
	
	if (Timer->Timer == TIM1) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;	
	} else if (Timer->Timer == TIM2) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	
	} else if (Timer->Timer == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
	} else if (Timer->Timer == TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;	
	}
	
	Timer->Timer->PSC = Timer->PSC;
	Timer->Timer->ARR = Timer->ARR;
}

void MyTimer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*IT_function)(void)) {
	char IRQn;
	
	IRQHandlerPointer = IT_function;
	
	Timer->DIER |= 0x1;		// Authorize Interrupts from Peripherical
	
	if(Timer == TIM1) {
		IRQn = 25;
	} else if(Timer == TIM2) {
		IRQn = 28;
	} else if(Timer == TIM3) {
		IRQn = 29;
	} else if(Timer == TIM4) {
		IRQn = 30;
	}
	
	NVIC->IP[IRQn] = Prio << 4;
	// IRQn >> 5 pour diviser par 32 car les 32 premiers IRQn sont dans ISER[0] etc ...
	// (1 << IRQn) fonctionne en soit car on est en dessous de 31 
	// Mais (1 << (IRQn & 0x1F)) permet de faire un modulo 32 pour que ça fonctionne même avec plus.
	NVIC->ISER[IRQn >> 5] = (1 << (IRQn & 0x1F)); 
	//NVIC_SetPriority(IRQn,Prio);
	//NVIC_EnableIRQ(IRQn);
}

void MyTimer_PWM(TIM_TypeDef *Timer, char Channel) {
	
}

void TIM1_UP_IRQHandler(void) {
	TIM1->SR &= ~(0x1); //Clear Interrupt Flag
	if (IRQHandlerPointer != 0)
		(*IRQHandlerPointer) ();
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~(0x1); //Clear Interrupt Flag
	if (IRQHandlerPointer != 0)
		(*IRQHandlerPointer) ();
}

void TIM3_IRQHandler(void) {
	TIM3->SR &= ~(0x1); //Clear Interrupt Flag
	if (IRQHandlerPointer != 0)
		(*IRQHandlerPointer) ();
}

void TIM4_IRQHandler(void) {
	TIM4->SR &= ~(0x1); //Clear Interrupt Flag
	if (IRQHandlerPointer != 0)
		(*IRQHandlerPointer) ();
}
