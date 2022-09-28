
#include "Driver_GPIO.h"
#include "stm32f10x.h"

void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr) {
	int mode;
	int cnf;
	
	if(GPIOStructPtr->GPIO==GPIOA){
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	} else if(GPIOStructPtr->GPIO==GPIOB){
		RCC->APB2ENR |= (0x01 << 3);
	} else if(GPIOStructPtr->GPIO==GPIOC){ 
		RCC->APB2ENR |= (0x01 << 4);
	} else if(GPIOStructPtr->GPIO==GPIOD){ 
		RCC->APB2ENR |= (0x01 << 5);
	}
	
	switch (GPIOStructPtr->GPIO_Conf) { 		// Enable relevant clock for GPIO
		case In_Floating: 
			mode = 0;
			cnf = 1;
			break;
		case In_PullDown: 	
			mode = 0;
			cnf = 2;
			break;
		case In_PullUp: 	
			mode = 0;
			cnf = 2;
			break;			
		case In_Analog: 		
			mode = 0;
			cnf = 0;
			break;
		case Out_Ppull: 
			mode = 2;
			cnf = 0;
			break;			
		case Out_OD: 		
			mode = 2;
			cnf = 1;
			break;			
		case AltOut_Ppull: 	
			mode = 2;
			cnf = 2;
			break;
		case AltOut_OD: 
			mode = 2;
			cnf = 3;
			break;			
		default: 
			break;
	}
	
	if(GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL = (GPIOStructPtr->GPIO->CRL & ~(0x3 << 4*GPIOStructPtr->GPIO_Pin)) | (mode << 4*GPIOStructPtr->GPIO_Pin);
		GPIOStructPtr->GPIO->CRL = (GPIOStructPtr->GPIO->CRL & ~(0x3 << 4*GPIOStructPtr->GPIO_Pin+2)) | (cnf << 4*GPIOStructPtr->GPIO_Pin+2);
	} else {
		GPIOStructPtr->GPIO->CRH = (GPIOStructPtr->GPIO->CRH & ~(0x3 << 4*(GPIOStructPtr->GPIO_Pin-8))) | (mode << 4*(GPIOStructPtr->GPIO_Pin-8)); 
		GPIOStructPtr->GPIO->CRH = (GPIOStructPtr->GPIO->CRH & ~(0x3 << 4*(GPIOStructPtr->GPIO_Pin-8)+2)) | (cnf << 4*(GPIOStructPtr->GPIO_Pin-8)+2); 
	}
	
	if(GPIOStructPtr->GPIO_Conf == In_PullDown) {
		GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);
	} else if(GPIOStructPtr->GPIO_Conf == In_PullUp) {
		GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);
	}
}

