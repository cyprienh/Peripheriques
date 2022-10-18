#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include "stm32f10x.h"

#define MAX_STRING_LENGTH 64
#define UART_ReadByte(USART) (USART->DR)

void UART_Init_TX(USART_TypeDef * USART); 
void UART_Init_RX(USART_TypeDef * USART); 
void UART_Print(USART_TypeDef * USART, char * str);
void UART_Read(USART_TypeDef * USART, char* message);
char UART_ReadChar(USART_TypeDef * USART);

// char UART_ReadByte(USART_TypeDef * USART);


#endif
