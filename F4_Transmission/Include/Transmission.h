#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "stm32f10x.h"

//extern signed char Orientation_RX;

const char * Transmission_ConvertirAllure (int alpha);
char * Transmission_ConvertirBordage (int theta, char * message);

#endif
