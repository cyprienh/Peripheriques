#ifndef RTC_H
#define RTC_H

#include "stm32f10x.h"

void RTC_Set_Time_Date(I2C_TypeDef* I2C, int s, int min, int h, int w, int d, int m, int y);
void RTC_Get_Date_Time(I2C_TypeDef* I2C, char* time);

#endif
