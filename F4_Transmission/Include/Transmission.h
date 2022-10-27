#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "stm32f10x.h"

//extern signed char Orientation_RX;

void Transmission_Init(void);

const char * Transmission_ConvertirAllure (int alpha);
char * Transmission_ConvertirBordage (int theta, char * message);
char * Transmission_ConvertirBatterie (float batterie, char * message);

void Transmission_SendRegInfo(void);

#endif
