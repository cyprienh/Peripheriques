#include "Driver_UART.h"
#include "Driver_GPIO.h"
#include "Driver_STD.h"

void UART_Init_TX (USART_TypeDef * USART) {
	GPIO_Struct_TypeDef GPIO_StructTX;
	GPIO_StructTX.GPIO_Conf=AltOut_Ppull;
	
	if (USART == USART1) {				// Set CLK & Config GPIO TX
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	} else if (USART == USART2) {
		GPIO_StructTX.GPIO=GPIOA;
		GPIO_StructTX.GPIO_Pin=2;
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	
	} else if (USART == USART3) {
		GPIO_StructTX.GPIO=GPIOB;
		GPIO_StructTX.GPIO_Pin=10;
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	GPIO_Init(&GPIO_StructTX);
	
	USART->CR1 |= (0x1 << 13); 		// USART Enable
	USART->CR1 &= ~(0x1 << 12); 		// Set word length to 8 bits
	USART->CR2 &= ~(0x3 << 12); 	// 1 Stop bit
	USART->CR1 &= ~(0x1 << 10);		// Disable parity control
	//USART->CR1 &= ~(0x1 << 9);		// Set to even parity
	
	if (USART == USART1) {
		USART->BRR = 0x1D4C;				// Set baud rate to 9600	
	} else if (USART == USART2 || USART == USART3) {
		USART->BRR = 0xEA6;					// Set baud rate to 9600	
	} 
	
	USART->CR2 &= ~(0x1 << 11);		// CLK Disable
	USART->CR1 |= (0x1 << 3); 		// Enable transmitter
}

void UART_Init_RX (USART_TypeDef * USART) {
	GPIO_Struct_TypeDef GPIO_StructRX;
	GPIO_StructRX.GPIO_Conf=AltOut_Ppull;
	
	if (USART == USART1) {				// Set CLK & Config GPIO TX
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	} else if (USART == USART2) {
		GPIO_StructRX.GPIO=GPIOA;
		GPIO_StructRX.GPIO_Pin=3;
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	
	} else if (USART == USART3) {
		GPIO_StructRX.GPIO=GPIOC;
		GPIO_StructRX.GPIO_Pin=11;
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	GPIO_Init(&GPIO_StructRX);
	
	USART->CR1 |= (0x1 << 13); 		// USART Enable
	USART->CR1 &= ~(0x1 << 12); 		// Set word length to 8 bits
	USART->CR2 &= ~(0x3 << 12); 	// 1 Stop bit
	USART->CR1 &= ~(0x1 << 10);		// Disable parity control
	//USART->CR1 &= ~(0x1 << 9);		// Set to even parity
	
	if (USART == USART1) {
		USART->BRR = 0x1D4C;				// Set baud rate to 9600	
	} else if (USART == USART2 || USART == USART3) {
		USART->BRR = 0xEA6;					// Set baud rate to 9600	
	} 
	
	USART->CR2 &= ~(0x1 << 11);		// CLK Disable
	USART->CR1 |= (0x1 << 2); 		// Enable receiver
}

void UART_Print(USART_TypeDef * USART, char * str) {
	int i;
	for (i = 0; i < String_Length(str) ; i++) {
		USART->DR=str[i];
		while (((USART->SR >> 7) & 0x1) != 1);	
	}
	
	while (((USART->SR >> 6) & 0x1) != 1);		// Wait for transmission complete
}

char UART_ReadChar(USART_TypeDef * USART) {
	
	while (((USART->SR >> 5) & 0x1) != 1);
	return USART->DR;
}

/*
char UART_ReadByte(USART_TypeDef * USART) {
	return USART->DR;
}
*/

void UART_Read(USART_TypeDef * USART, char* message) {
	char fin = 0;
	char taille = 0;
	char current;
	
	while(fin == 0 && taille <= MAX_STRING_LENGTH) {
		while (((USART->SR >> 5) & 0x1) != 1);
		current = USART->DR;
		if(current == '\r') {
			message[taille] = 0;
			fin = 1;
		} else {
			message[taille] = current;
		}	
		taille++;
	}
}
