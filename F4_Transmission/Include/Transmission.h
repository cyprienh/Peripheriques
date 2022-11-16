#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "stm32f10x.h"


void Transmission_Init(void);

void Read_Battery(void);

const char * Transmission_ConvertirAllure (int alpha);
void Transmission_ConvertirBordage (int theta, char * message);
void Transmission_ConvertirBatterie (float batterie, char * message);
void Transmission_SendRegInfo(void);

#endif
