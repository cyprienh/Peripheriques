#include "stm32f10x.h"
#include "MySPI.h"
#include "AntiChavirement.h"

// ================================
// 		F3 - Anti-chavirement
//		Maïlis Dy
// ================================

void Chavirement_Config(){
	MySPI_Clear_NSS();
	MySPI_Send(BW_RATE Ecriture MultBytes); //BW_Rate en écriture
	MySPI_Send(0x9);
	MySPI_Set_NSS();
	MySPI_Clear_NSS();
	MySPI_Send(POWER_CTL Ecriture MultBytes); //POWER_CTL en écriture
	MySPI_Send(0x8);
	MySPI_Set_NSS();
	MySPI_Clear_NSS();
	MySPI_Send(DATA_FORMAT Ecriture MultBytes);//DATA_FORMAT en écriture
	MySPI_Send(0xB);
	MySPI_Set_NSS();
}

void Chavirement_Accelero_Read(Accelero_TypeDef * ptr){
	int X0;
	int X1;
	int Y0;
	int Y1;
	int Z0;
	int Z1;
	//Lecture des infos de X
	MySPI_Clear_NSS();
	MySPI_Send(DATA_X0 Lecture MultBytes); 
	X0 = MySPI_Read();
	X1 = MySPI_Read();
	Y0 = MySPI_Read();
	Y1 = MySPI_Read();
	Z0 = MySPI_Read();
	Z1 = MySPI_Read();
	MySPI_Set_NSS();
	
	ptr->AccX = ptr->AccX &~(255);
	ptr->AccX = ptr->AccX &~(255<<8);
	ptr->AccY = ptr->AccY &~(255);
	ptr->AccY = ptr->AccY &~(255<<8);
	ptr->AccZ = ptr->AccZ &~(255);
	ptr->AccZ = ptr->AccZ &~(255<<8);
	
	ptr->AccX = ptr->AccX | X0 | (X1<<8);
	ptr->AccY = ptr->AccY | Y0 | (Y1<<8);
	ptr->AccZ = ptr->AccZ | Z0 | (Z1<<8);
}

