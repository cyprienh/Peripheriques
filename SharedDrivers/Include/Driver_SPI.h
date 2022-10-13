#ifndef DRIVER_SPI_H
#define DRIVER_SPI_H

#include "stm32f10x.h"

void SPI_Init(SPI_TypeDef * SPI);
void SPI_Send(SPI_TypeDef * SPI, char * message);
#endif





