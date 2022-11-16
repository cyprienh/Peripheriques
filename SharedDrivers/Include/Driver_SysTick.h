#ifndef DRIVER_SYSTICK_H
#define DRIVER_SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void (*IT_function)(void));

#endif
