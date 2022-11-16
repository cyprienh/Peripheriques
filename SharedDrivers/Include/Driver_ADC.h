#ifndef DRIVER_ADC_H
#define DRIVER_ADC_H

#include "stm32f10x.h"

void ADC_Init(ADC_TypeDef *ADC, char Channel);
void ADC_Read(ADC_TypeDef *ADC);
float ADC_Read_Temp(ADC_TypeDef *ADC);

void ADC_ActiveIT(ADC_TypeDef *ADC , char Prio, void (*IT_function)(void));

#endif
