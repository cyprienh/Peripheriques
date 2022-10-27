#include "Transmission.h"
#include "stm32f10x.h"
#include "Driver_UART.h"
#include "Driver_STD.h"

const char * Transmission_ConvertirAllure (int alpha) {
	const char *ventdebout = "Le voilier navigue en vent debout";
	const char *aupres = "Le voilier navigue au près";
	const char *aulargue = "Le voilier navigue en vent debout";
	const char *augrandlargue = "Le voilier navigue au grand largue";
	const char *enventarriere = "Le voilier navigue en vent arrière";
	
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

char * Transmission_ConvertirBordage (int theta, char * message) {
	if (theta > 0) {
		message[21] = ' ';
	} else {
		message[21] = '-';	
	}
	message[22] = (char)((theta % 10)-48);
	message[23] = (char)((theta/10%10)-48);
	
	return message;
}

