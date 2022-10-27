
#include "Driver_GPIO.h"
#include "stm32f10x.h"
#include "MySPI.h"



//Utiliser SPI1
#define BW_RATE 		0x2C
#define POWER_CTL 	0x2D
#define DATA_FORMAT 0x31
#define Lecture			3<<6
#define Ecriture		1<<6

int Chavirement_Read(char Adress, int NombreOctets){ //adresse du registre et nombre d'octets à lire
	int i;
	char* Donnees;
	MySPI_Clear_NSS();
	MySPI_Send(Adress);
	for(i=0;i<NombreOctets;i++){
		MySPI_Read();
	}
	MySPI_Set_NSS();
}

void Chavirement_Config(){
	MySPI_Clear_NSS();
	MySPI_Send(BW_RATE & Ecriture); //BW_Rate en écriture
	MySPI_Send(0x9);
	MySPI_Set_NSS();
	MySPI_Clear_NSS();
	MySPI_Send(POWER_CTL & Ecriture); //POWER_CTL en écriture
	MySPI_Send(0x8);
	MySPI_Set_NSS();
	MySPI_Clear_NSS();
	MySPI_Send(DATA_FORMAT & Ecriture);//DATA_FORMAT en écriture
	MySPI_Send(0xA);
	MySPI_Set_NSS();

}


int main (void) {
	char donnee;
	GPIO_Init();
	
  MySPI_Init(SPI1);
	Chavirement_Config();
	
	MySPI_Clear_NSS();
	MySPI_Send(0x00 & Lecture);
	donnee = MySPI_Read();
	MySPI_Set_NSS();
	
	
	
	
	do {
	} while (1);
	
}
