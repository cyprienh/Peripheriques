
#include "Driver_GPIO.h"
#include "stm32f10x.h"
#include "MySPI.h"
#include "AntiChavirement.h"
#include "math.h"



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
Accelero_TypeDef MyAccelero;
float Angle;
float Xg;
float Yg;
float Zg;



int main (void) {
	//char * donnee;
	//char interm;
	//char adresseTest;
	
	
	int Chavirement = 0;
	Angle = 0;
	
	MyAccelero.AccX = 0;
	MyAccelero.AccY = 0;
	MyAccelero.AccZ = 0;
	
  MySPI_Init(SPI1); //Initialisation SPI
	Chavirement_Config();
	
	
	
	
	
	do {
		/*
		//TEST LECTURE de l'id de l'adxl345
		MySPI_Clear_NSS();
		MySPI_Send(0x00 Lecture SingBytes); //On envoit l'adresse où se trouve l'id + l'info qu'on veut être en lecture 
		//MySPI_Send(lectureid);
		adresseTest = MySPI_Read();
		MySPI_Set_NSS();
		*/
		
		Chavirement_Accelero_Read(&MyAccelero); //récupération des valeurs de l'accéléro
		
		//Composantes normalisées
		Xg = MyAccelero.AccX * 4e-3;
		Yg = MyAccelero.AccY * 4e-3;
		Zg = MyAccelero.AccZ * 4e-3;
		if (Yg*Zg<0){
			Angle = atan(-(Yg/Zg));
		} else 
			Angle = atan(Yg/Zg);
		if (Angle >= 0.698){ //40 degre convertit en rad
			Chavirement = 1;
		}	else 
			Chavirement = 0;
		
			
	} while (1);
	
}
