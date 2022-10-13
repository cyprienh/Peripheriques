#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void (*IRQHandlerPointer) (void) ;

void Timer_Init(Timer_Struct_TypeDef * Timer) {
	
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

void Timer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*IT_function)(void)) {
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

void Timer_PWM(TIM_TypeDef *Timer, char Channel) {
	switch(Channel) {
		case 1:
			Timer->CCER |= (0x1 << 0); // Enable output
			Timer->CCER &= ~(0x1 << 1); // Set output polarity to active high
			Timer->CCER |= (0x1 << 2); // Enable complementary output
			Timer->CCMR1 &= ~(0x3);		// CC1S to output
			Timer->CCMR1 = (Timer->CCMR1 & ~(0x7 << 4)) | (0x6 << 4); // Set PWM Mode 1
			
			Timer->EGR |= (0x1 << 0); 
			break;
		case 2:
			Timer->CCER |= (0x1 << 4); // Enable output
			Timer->CCER &= ~(0x1 << 5); // Set output polarity to active high
			Timer->CCER |= (0x1 << 6); // Enable complementary output
			Timer->CCMR1 &= ~(0x3 << 8);		// CC1S to output
			Timer->CCMR1 = (Timer->CCMR1 & ~(0x7 << 12)) | (0x6 << 12);
		
			Timer->EGR |= (0x1 << 0);
			break;
		case 3:
			Timer->CCER |= (0x1 << 8); // Enable output
			Timer->CCER &= ~(0x1 << 9); // Set output polarity to active high
			Timer->CCER |= (0x1 << 10); // Enable complementary output
			Timer->CCMR2 &= ~(0x3);		// CC1S to output
			Timer->CCMR2 = (Timer->CCMR1 & ~(0x7 << 4)) | (0x6 << 4);
		
			Timer->EGR |= (0x1 << 0);
			break;
		case 4:
			Timer->CCER |= (0x1 << 12); // Enable output
			Timer->CCER &= ~(0x1 << 13); // Set output polarity to active high
			Timer->CCER |= (0x1 << 14); // Enable complementary output
			Timer->CCMR2 &= ~(0x3 << 8);		// CC1S to output
			Timer->CCMR2 = (Timer->CCMR1 & ~(0x7 << 12)) | (0x6 << 12);
		
			Timer->EGR |= (0x1 << 0);
			break;
		default:
			return;
	}
	if(Timer == TIM1) {
		Timer->BDTR |= (0x1 << 15); // MOE
		// Timer->BDTR |= (0x1 << 11); // OSSR 
		
	}
}

void Timer_PWM_Set_Duty_Cycle(TIM_TypeDef *Timer, char Channel, float DutyCycle) {
	int Tpwm = Timer->ARR+1;
	int Th = (int)(Tpwm*DutyCycle);
	switch(Channel) {
		case 1:
			Timer->CCR1 = Th;
			return;
		case 2:
			Timer->CCR2 = Th;
			return;
		case 3:
			Timer->CCR3 = Th;
			return;
		case 4:
			Timer->CCR4 = Th;
			return;
		default:
			return;
	}
}

void Timer_Incremental() {
	GPIO_Struct_TypeDef GPIO_StructTI1;
	GPIO_Struct_TypeDef GPIO_StructTI2;
	
	GPIO_StructTI1.GPIO=GPIOA;
	GPIO_StructTI1.GPIO_Pin=8;
	GPIO_StructTI1.GPIO_Conf=In_PullDown;
	GPIO_Init(&GPIO_StructTI1);
	
	GPIO_StructTI2.GPIO=GPIOA;
	GPIO_StructTI2.GPIO_Pin=9;
	GPIO_StructTI2.GPIO_Conf=In_PullDown;
	GPIO_Init(&GPIO_StructTI2);
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;		// Start TIM1 CLK
	
	TIM1->CCMR1 = (TIM1->CCMR1 & ~(0x3 << 0)) | (0x1 << 0);		// TIFP1 <- TI1
	TIM1->CCMR1 = (TIM1->CCMR1 & ~(0x3 << 8)) | (0x1 << 8);		// TIFP2 <- TI2
	
	TIM1->CCER &= ~(0x1 << 1);		// TI1FP1 non-inverted, TI1FP1=TI1
	TIM1->CCMR1 &= ~(0xF << 4);
	TIM1->CCER |= (0x1 << 0);
	
	TIM1->CCER &= ~(0x1 << 5);		// TI1FP2 non-inverted, TI1FP2=TI2
	TIM1->CCMR1 &= ~(0xF << 12);
	TIM1->CCER |= (0x1 << 4);
	
	TIM1->SMCR = (TIM1->SMCR & ~(0x7 << 0)) | (0x3 << 0);	// Both input active & rising + falling edge
	
	TIM1->ARR = 1440;			// 360*4
	
	TIM1->CR1 |= (0x1 << 0);			// Counter enable
}

float Timer_Get_Angle() {
	return TIM1->CNT / 4.0;
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
