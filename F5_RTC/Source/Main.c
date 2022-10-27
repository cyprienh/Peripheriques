#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "MyI2C.h"
#include "stm32f10x.h"

char data[1];
char address;

void I2C_Callback() {
	
}

int main (void) {
	GPIO_Struct_TypeDef GPIOB6;
	GPIO_Struct_TypeDef GPIOB7;
	MyI2C_RecSendData_Typedef I2C_Data;
	
	GPIOB6.GPIO = GPIOB;
	GPIOB6.GPIO_Pin = 6;
	GPIOB6.GPIO_Conf = Out_OD;
	
	GPIOB7.GPIO = GPIOB;
	GPIOB7.GPIO_Pin = 7;
	GPIOB7.GPIO_Conf = Out_OD;
	
	GPIO_Init(&GPIOB6);
	GPIO_Init(&GPIOB7);
	
	//data[0] = 0x01 << 1;
	address = 0x2;
	
	I2C_Data.SlaveAdress7bits = 0x68;
	I2C_Data.Ptr_Data = data;
	I2C_Data.Nb_Data = 1;
	
	MyI2C_Init(I2C1, 2, I2C_Callback);
	
	/*data[0] = (0x0 << 4) | (0x0 << 0);
	MyI2C_PutString(I2C1, 0x00, &I2C_Data);
	data[0] = (0x4 << 4) | (0x8 << 0);
	MyI2C_PutString(I2C1, 0x01, &I2C_Data);
	data[0] = (0x1 << 6) | (0x1 << 4) | (0x0 << 0);
	MyI2C_PutString(I2C1, 0x02, &I2C_Data);*/
	
	do {		
		MyI2C_GetString(I2C1, address, &I2C_Data);
	} while (1);
}
