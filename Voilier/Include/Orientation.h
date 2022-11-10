#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "stm32f10x.h"

extern signed char Orientation_RX;

void Orientation_Init(void);

void Orientation_ActiveIT(void (*IT_function)(void));
void Orientation_Receive_Handler(void); 
void Orientation_Receive(void);

#endif
