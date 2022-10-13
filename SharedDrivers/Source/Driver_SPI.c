#include "Driver_SPI.h"
#include "Driver_GPIO.h"
#include "Driver_STD.h"

void SPI_Init(SPI_TypeDef * SPI){
	//Initialisation en full duplex:
	SPI->CR1 &= ~(SPI_CR1_SPE);//Enable SPI
	SPI->CR1 &= ~(SPI_CR1_BIDIMODE); //Pas de bidirection
	SPI->CR1 &= ~(SPI_CR1_RXONLY); //Pas de read only
	SPI->CR1 &= ~(SPI_CR1_DFF);//Data Frame Format = 0 transmission 8 bits, 16 bits =1
	SPI->CR1 &= ~(SPI_CR1_LSBFIRST);//Transmission MSB First bit=0; LSB First bit=1
	SPI->CR1 |= (SPI_CR1_BR_0) | (SPI_CR1_BR_2);//Gestion du Baud Rate Control voir register description
	SPI->CR1 |= (SPI_CR1_MSTR);//Mise en mode Master
	
	//SPI->CR2 |= (SPI_CR2_TXEIE);//Enable l'interrupt TxBuff libre
	//SPI->CR2 |= (SPI_CR2_RXNEIE);//Enable l'interrupt réception de message
	
}


void SPI_Send(SPI_TypeDef * SPI, char * message){
	if (String_Length(message) <= 8){
		
	}
	
}


