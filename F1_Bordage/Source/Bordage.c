#include "Bordage.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

	
void Bordage_Init(void) {
	GPIO_Struct_TypeDef GPIO_StructTI1;
	GPIO_Struct_TypeDef GPIO_StructTI2;
	GPIO_Struct_TypeDef GPIO_StructZ;
	
	GPIO_StructTI1.GPIO=GPIO_AB;
	GPIO_StructTI1.GPIO_Pin=PIN_A;
	GPIO_StructTI1.GPIO_Conf=In_PullDown;
	GPIO_Init(&GPIO_StructTI1);
	
	GPIO_StructTI2.GPIO=GPIO_AB;
	GPIO_StructTI2.GPIO_Pin=PIN_B;
	GPIO_StructTI2.GPIO_Conf=In_PullDown;
	GPIO_Init(&GPIO_StructTI2);
	
	GPIO_StructZ.GPIO=GPIO_Z;
	GPIO_StructZ.GPIO_Pin=PIN_Z;
	GPIO_StructZ.GPIO_Conf=In_PullDown;
	GPIO_Init(&GPIO_StructZ);
	
	// AJOUTER IF
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;		// Start TIM1 CLK
	
	BORDAGE_TIMER_INCREMENTAL->CCMR1 = (BORDAGE_TIMER_INCREMENTAL->CCMR1 & ~(0x3 << 0)) | (0x1 << 0);		// TIFP1 <- TI1
	BORDAGE_TIMER_INCREMENTAL->CCMR1 = (BORDAGE_TIMER_INCREMENTAL->CCMR1 & ~(0x3 << 8)) | (0x1 << 8);		// TIFP2 <- TI2
	
	BORDAGE_TIMER_INCREMENTAL->CCER &= ~(0x1 << 1);		// TI1FP1 non-inverted, TI1FP1=TI1
	BORDAGE_TIMER_INCREMENTAL->CCMR1 &= ~(0xF << 4);
	BORDAGE_TIMER_INCREMENTAL->CCER |= (0x1 << 0);
	
	BORDAGE_TIMER_INCREMENTAL->CCER &= ~(0x1 << 5);		// TI1FP2 non-inverted, TI1FP2=TI2
	BORDAGE_TIMER_INCREMENTAL->CCMR1 &= ~(0xF << 12);
	BORDAGE_TIMER_INCREMENTAL->CCER |= (0x1 << 4);
	
	BORDAGE_TIMER_INCREMENTAL->SMCR = (BORDAGE_TIMER_INCREMENTAL->SMCR & ~(0x7 << 0)) | (0x3 << 0);	// Both input active & rising + falling edge
	
	BORDAGE_TIMER_INCREMENTAL->PSC = 0;			// 360*4
	BORDAGE_TIMER_INCREMENTAL->ARR = 1440;			// 360*4
	
	BORDAGE_TIMER_INCREMENTAL->CR1 |= (0x1 << 0);			// Counter enable
}

void Bordage_Calibration(void) {
	while(!GPIO_Read(GPIO_Z, PIN_Z));
	BORDAGE_TIMER_INCREMENTAL->CNT = 0;
}


float Bordage_Get_Angle(void) {
	return BORDAGE_TIMER_INCREMENTAL->CNT / 4.0;
}
