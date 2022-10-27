
#include "Driver_GPIO.h"
#include "stm32f10x.h"
#include "MySPI.h"
#include "AntiChavirement.h"




/*char Chavirement_Read(char Adress){ //adresse du registre et nombre d'octets à lire

	char * Donnees;
	char inter;
	
	MySPI_Clear_NSS();
	MySPI_Send(Adress Lecture SingBytes);
	MySPI_Set_NSS();
	inter = MySPI_Read();
	*Donnees = inter;
	
	
	return inter;
}
*/


int main (void) {
	char * donnee;
	char interm;
	//char donneef;
	
	Accelero_TypeDef MyAccelero;
	
	
  MySPI_Init(SPI1); //Initialisation SPI
	Chavirement_Config();
	
	
	
	
	
	do {
		/*
		//TEST LECTURE de l'id de l'adxl345
		MySPI_Clear_NSS();
		MySPI_Send(0x00 Lecture SingBytes); //On envoit l'adresse où se trouve l'id + l'info qu'on veut être en lecture 
		//MySPI_Send(lectureid);
		inter = MySPI_Read();
		donnee = &inter;
		MySPI_Set_NSS();
		
		interm = Chavirement_Read(0x00);
		*donnee = interm;
		*/
		Chavirement_Accelero_Read(&MyAccelero);
		
	} while (1);
	
}
