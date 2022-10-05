
#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"

int main (void) {
	GPIO_Struct_TypeDef GPIO_StructA0;
	char message[MAX_STRING_LENGTH];
	
	GPIO_StructA0.GPIO=GPIOA;
	GPIO_StructA0.GPIO_Pin=0;
	GPIO_StructA0.GPIO_Conf=Out_Ppull;
	GPIO_Init(&GPIO_StructA0);
	
	//UART_Init_TX(USART2);
	//UART_Print(USART2, message);
	
	do {
		UART_Init_RX(USART2);
		UART_Read(USART2, message);
		UART_Init_TX(USART2);
		UART_Print(USART2, message);
	} while (1);
}
