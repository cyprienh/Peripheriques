#include "Transmission.h"
#include "stm32f10x.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"

#include "Bordage.h"
#include "AntiChavirement.h"
#include "RTC.h"

	float Bordage_a;
	int Bordage_theta;
	float Voltage_Bat = 0.0;
	
	char AChavire;
	char Chavirement;

void Transmission_Init() {
	Timer_Struct_TypeDef Transmission_Timer;
	
	UART_Init_TX(USART3);
	
	Transmission_Timer.Timer = TIM4;		// Roughly every 3 seconds
	Transmission_Timer.ARR = 20000;
	Transmission_Timer.PSC = 10000;

	Timer_Init(&Transmission_Timer);
	Timer_Start(TIM4);
	
	//Timer_ActiveIT(TIM4 , 20, &(Transmission_SendRegInfo));
	
	ADC_Init(ADC1, 14);	
	ADC_ActiveIT(ADC1 , 10, &(Read_Battery));
}

void Transmission_SendRegInfo() { 
	char Transmission_date[21] = "00/00/00 - 00:00:00\n\0";
	char Transmission_InfoBordage[18] = "Ouverture : 000 \n\0";
	char Transmission_InfoChavirement[22] = "Le bateau a chavire \n\0";
	char Transmission_InfoBatterie[26] = "Batterie faible : 00.0V \n\0";
	char LineBreak[2] = "\n\0";
	
	ADC_Read(ADC1);	
	
	RTC_Get_Date_Time(I2C1, Transmission_date);
	Transmission_ConvertirBordage(Bordage_theta, Transmission_InfoBordage);
	
	UART_Print(USART3, Transmission_date);
	UART_Print(USART3, Transmission_InfoBordage);
	UART_Print(USART3, (char *)Transmission_ConvertirAllure((int)Bordage_a));
	
	if (AChavire == 1) 
			UART_Print(USART3, Transmission_InfoChavirement);
			AChavire = 0;
	
	if (Voltage_Bat < 10.0) {
		Transmission_ConvertirBatterie(Voltage_Bat, Transmission_InfoBatterie);
		UART_Print(USART3, Transmission_InfoBatterie);
	}
	
	UART_Print(USART3, LineBreak);
}

void Read_Battery() {
	Voltage_Bat = (ADC1->DR * (3.3f/4096.0f))*13.0;
	
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
void Transmission_ConvertirBordage (int theta, char * message) {
	if (theta > 0) {
		message[12] = '+';
	} else {
		message[12] = '-';	
	}
	
	message[13] = (char)(theta/10+48);
	message[14] = (char)((theta % 10)+48);
}

// Formats the message for ascii
void Transmission_ConvertirBatterie (float batterie, char * message) {
	message[18] = (char)((int)(batterie/10)+48);
	message[19] = (char)((((int)(batterie))%10)+48);
	message[21] = (char)(((int)(batterie*10))%10+48);
}

