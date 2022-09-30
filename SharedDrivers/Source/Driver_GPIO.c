
#include "Driver_GPIO.h"
#include "stm32f10x.h"

char modecnf[8] = {0x4,0x8,0x8,0x0,0x2,0x6,0xa,0xe};

void GPIO_Init(GPIO_Struct_TypeDef * GPIOStructPtr) {
	
	if(GPIOStructPtr->GPIO==GPIOA){
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	} else if(GPIOStructPtr->GPIO==GPIOB){
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	} else if(GPIOStructPtr->GPIO==GPIOC){ 
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	} else if(GPIOStructPtr->GPIO==GPIOD){ 
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	
	if(GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL = (GPIOStructPtr->GPIO->CRL & ~(0xf << 4*GPIOStructPtr->GPIO_Pin)) | (modecnf[GPIOStructPtr->GPIO_Conf] << 4*GPIOStructPtr->GPIO_Pin);
	} else {
		GPIOStructPtr->GPIO->CRH = (GPIOStructPtr->GPIO->CRH & ~(0xf << 4*(GPIOStructPtr->GPIO_Pin-8))) | (modecnf[GPIOStructPtr->GPIO_Conf] << 4*(GPIOStructPtr->GPIO_Pin-8)); 
	}
	
	if(GPIOStructPtr->GPIO_Conf == In_PullDown) {
		GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);
	} else if(GPIOStructPtr->GPIO_Conf == In_PullUp) {
		GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);
	}
}

