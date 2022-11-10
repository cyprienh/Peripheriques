#ifndef ANTICHAVIREMENT_H
#define ANTICHAVIREMENT_H

#include "stm32f10x.h"


//Utiliser SPI1
//Adresses des registres à configurer
#define BW_RATE 		0x2C
#define POWER_CTL 	0x2D
#define DATA_FORMAT 0x31
#define DATA_X0 0x32
#define DATA_X1 0x33
#define DATA_Y0 0x34
#define DATA_Y1 0x35
#define DATA_Z0 0x36
#define DATA_Z1 0x37
//Const à ajouter selon fonction
#define Lecture			|(1<<7)
#define Ecriture	  &~(1<<7)
#define MultBytes		|(1<<6)
#define SingBytes		&~(1<<6)


typedef struct{
	short int AccX;
	short int AccY;
	short int AccZ;
} Accelero_TypeDef ;


void Chavirement_Config(void);
void Chavirement_Accelero_Read(Accelero_TypeDef * ptr);
#endif
