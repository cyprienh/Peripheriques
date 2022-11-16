
#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "Driver_I2C.h"
#include "Driver_SysTick.h"
#include "stm32f10x.h"

// 1 tick = 1ms
unsigned long tick;

// Handler, faire des trucs avec des modulos ..
void Test(){
	++tick;
}


int main (void) {
	
	SysTick_Init(&Test);
	
	do {
		if(tick % 100 == 0) {
		
		} else if (tick % 1000 == 0) {
			
		}
	} while (1);
}
