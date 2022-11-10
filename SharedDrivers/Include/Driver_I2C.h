#ifndef DRIVER_I2C_H
#define DRIVER_I2C_H

#include "stm32f10x.h"

void I2C_Init(I2C_TypeDef* I2C);

void I2C_Read(I2C_TypeDef* I2C, char Slave_Address, char Data_Address, char* data, char length);
void I2C_Write(I2C_TypeDef* I2C, char Slave_Address, char Data_Address, char* data, char length);

#endif
