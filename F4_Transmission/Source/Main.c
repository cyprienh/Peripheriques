#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "stm32f10x.h"
#include "Transmission.h"


int main (void) {
  int theta = 90;
	int alpha = 47;
	char Transmission_InfoBordage[] = "Ouverture de voile : XXX";
	
	// Formattage message
	UART_Init_TX(USART3);
	UART_Print(USART3, Transmission_ConvertirBordage(theta, Transmission_InfoBordage));
	UART_Print(USART3, (char *)Transmission_ConvertirAllure(alpha));
	do {		
		
	} while (1);
}
