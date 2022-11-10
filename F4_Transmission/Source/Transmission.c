#include "Transmission.h"
#include "stm32f10x.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Bordage.h"


	float Bordage_a;
	int Bordage_theta;

void Transmission_Init() {
	Timer_Struct_TypeDef Transmission_Timer;
	
	UART_Init_TX(USART3);
	
	Transmission_Timer.Timer = TIM4;		// Roughly every 3 seconds
	Transmission_Timer.ARR = 20000;
	Transmission_Timer.PSC = 10000;

	Timer_Init(&Transmission_Timer);
	Timer_Start(TIM4);
	ADC_Init(ADC1, 14);
	
	Timer_ActiveIT(TIM4 , 20, &(Transmission_SendRegInfo));
}

void Transmission_SendRegInfo() { 
	char Transmission_InfoBordage[] = "Ouverture : XXX \n";
	// char Transmission_InfoBatterie[] = "Batterie : X.XXmV \n";
	
	
	UART_Print(USART3, Transmission_ConvertirBordage(Bordage_theta, Transmission_InfoBordage));
	UART_Print(USART3, (char *)Transmission_ConvertirAllure((int)Bordage_a));
	//UART_Print(USART3, Transmission_ConvertirBatterie((ADC_Read(ADC1)*13), Transmission_InfoBatterie));
}

// Chooses correct message
const char * Transmission_ConvertirAllure (int alpha) {
	const char *ventdebout = "Le voilier navigue en vent debout\n";
	const char *aupres = "Le voilier navigue au pres\n";
	const char *aulargue = "Le voilier navigue en vent debout\n";
	const char *augrandlargue = "Le voilier navigue au grand largue\n";
	const char *enventarriere = "Le voilier navigue en vent arriere\n";
	
	if ((45 >= alpha && alpha >= 0) || (359 >= alpha && alpha >= 315)) {
		return ventdebout;
	} else if ((65 >= alpha && alpha >= 45) || (315 >= alpha && alpha >= 295)) {
		return aupres;
	} else if ((120 >= alpha && alpha >= 65) || (295 >= alpha && alpha >= 240)) {
		return aulargue;
	} else if ((170 >= alpha && alpha >= 120) || (240 >= alpha && alpha >= 190)) {
		return augrandlargue;
	} else {
		return enventarriere;
	}
}

// Formats the message for ascii
char * Transmission_ConvertirBordage (int theta, char * message) {
	if (theta > 0) {
		message[12] = '+';
	} else {
		message[12] = '-';	
	}
	
	message[13] = (char)((theta/10%10)+48);
	message[14] = (char)((theta % 10)+48);
	
	return message;
}

// Formats the message for ascii
char * Transmission_ConvertirBatterie (float batterie, char * message) {
	message[11] = (char)((int)batterie+48);
	message[12] = (char)((int)(batterie*10)%10+48);
	message[13] = (char)((int)(batterie*100)%10+48);
	
	return message;
}

