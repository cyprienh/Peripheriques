#ifndef DRIVER_ADC_H
#define DRIVER_ADC_H

#include "stm32f10x.h"

void ADC_Init(ADC_TypeDef *ADC, char Channel);
float ADC_Read(ADC_TypeDef *ADC);
float ADC_Read_Temp(ADC_TypeDef *ADC);

#endif
