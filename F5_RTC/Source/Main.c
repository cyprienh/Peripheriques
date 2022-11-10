#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "Driver_I2C.h"

#include "RTC.h"
#include "stm32f10x.h"

char test[20] = "00/00/00 - 00:00:00\n";

int main (void) {
	
	I2C_Init(I2C1);
	
	RTC_Set_Time_Date(I2C1, 0,33,11,4,10,11,22);
	
	do {
		RTC_Get_Date_Time(I2C1, test);
	} while (1);
}
