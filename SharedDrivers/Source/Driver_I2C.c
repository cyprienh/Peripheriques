#include "Driver_I2C.h"
#include "Driver_GPIO.h"

void I2C_Init(I2C_TypeDef* I2C) {
	GPIO_Struct_TypeDef GPIOSDA;
	GPIO_Struct_TypeDef GPIOSCL;
	
	GPIOSDA.GPIO = GPIOB;
	GPIOSCL.GPIO = GPIOB;
	GPIOSDA.GPIO_Conf = AltOut_OD;
	GPIOSCL.GPIO_Conf = AltOut_OD;
	
	if(I2C == I2C1) {
		GPIOSDA.GPIO_Pin = 7;
		GPIOSCL.GPIO_Pin = 6;
	} else if (I2C == I2C2) {
		GPIOSDA.GPIO_Pin = 11;
		GPIOSCL.GPIO_Pin = 10;
	}
	
	GPIO_Init(&GPIOSDA);
	GPIO_Init(&GPIOSCL);
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;	
	
	I2C->CR1 |= I2C_CR1_SWRST;
	I2C->CR1 &= ~I2C_CR1_SWRST;

	I2C->CR2 = (I2C->CR2 & ~(0x3f << 0)) | (36 << 0); 		// FREQ to APB1 ?
	
	I2C->CCR &= ~(0x1 << 15);															// Standard mode
	I2C->CCR = (I2C->CCR & ~(0x7ff << 0)) | (360 << 0); 	// 100kHz
	I2C->TRISE = (I2C->TRISE & ~(0x3f << 0)) | (37 << 0);	// 1000ns
	
	I2C->CR1 |= (0x1 << 0);																// Peripheral enable
}

void I2C_Write(I2C_TypeDef* I2C, char Slave_Address, char Data_Address, char* data, char length) {
	int i;
	while(((I2C->SR2 >> 1) & 0x1));		// BUSY bit
	
	I2C->CR1 |= (0x1 << 8);						// Start communication
	while(!((I2C->SR1 >> 0) & 0x1));	// SB bit
		
	I2C->DR = (I2C->DR & ~(0xff << 0)) | (Slave_Address << 1) | (0x0 << 0);	// Bit 0 = R/W (0=transmit, 1=receive)
	while(!((I2C->SR1 >> 1) & 0x1));	// ADDR bit
	while(!((I2C->SR2 >> 0) & 0x1));	// Read SR2 (any)
	
	I2C->DR = (I2C-> DR & ~(0xff << 0)) | Data_Address;	// Send Data Address to Slave
	while(!((I2C->SR1 >> 7) & 0x1));	// TxE bit; data received
		
	for(i=0; i<length; i++) {					// Send n bytes
		I2C->DR = (I2C-> DR & ~(0xff << 0)) | data[i];	// Send 0x68
		while(!((I2C->SR1 >> 7) & 0x1));// TxE bit; data received
	}

	I2C->CR1 |= (0x1 << 9);	// Close communication
}

void I2C_Read(I2C_TypeDef* I2C, char Slave_Address, char Data_Address, char* data, char length) {
	int i;
	while(((I2C->SR2 >> 1) & 0x1));	// BUSY bit
	
	I2C->CR1 |= (0x1 << 8);	// Start communication
	while(!((I2C->SR1 >> 0) & 0x1));	// SB bit
		
	I2C->DR = (I2C->DR & ~(0xff << 0)) | (Slave_Address << 1) | (0x0 << 0);	// Bit 0 = R/W (0=transmit, 1=receive)
	while(!((I2C->SR1 >> 1) & 0x1));	// ADDR bit
	while(!((I2C->SR2 >> 0) & 0x1));	// Read SR2 (any)
	
	I2C->DR = (I2C-> DR & ~(0xff << 0)) | Data_Address;	// Send Data Address to Slave
	while(!((I2C->SR1 >> 7) & 0x1));	// TxE bit; data received
	
	I2C->CR1 |= (0x1 << 8);	// Repeated start
	while(!((I2C->SR1 >> 0) & 0x1));	// SB bit
	
	I2C->DR = (I2C->DR & ~(0xff << 0)) | (Slave_Address << 1) | (0x1 << 0);	// Bit 0 = R/W (0=transmit, 1=receive)
	while(!((I2C->SR1 >> 1) & 0x1));	// ADDR bit
	while(!((I2C->SR2 >> 0) & 0x1));	// Read SR2 (any)
	
	for(i=0; i<length; i++) {	// Read n bytes
		while(!((I2C->SR1 >> 6) & 0x1));	// RxNE bit; data received
		data[i] = I2C->DR & 0xff;
	}

	I2C->CR1 |= (0x1 << 9);	// Close communication
}
