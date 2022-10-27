#ifndef ANTICHAVIREMENT_H
#define ANTICHAVIREMENT_H

#include "stm32f10x.h"


//Utiliser SPI1
//Adresses des registres à configurer
#define BW_RATE 		0x2C
#define POWER_CTL 	0x2D
#define DATA_FORMAT 0x31
//Const à ajouter selon fonction
#define Lecture			| (1<<7)
#define Ecriture	  & ~(1<<7)
#define MultBytes		| (1<<6)
#define SingBytes		& ~(1<<6)


typedef struct{
	int AccX;
	int AccY;
	int AccZ;
} Accelero_TypeDef ;


void Chavirement_Config();
void Chavirement_Accelero_Read(Accelero_TypeDef * ptr);
#endif
