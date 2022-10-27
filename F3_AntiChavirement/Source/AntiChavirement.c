#include "stm32f10x.h"
#include "MySPI.h"
#include "AntiChavirement.h"


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
	MySPI_Send(0xA);
	MySPI_Set_NSS();

}



void Chavirement_Accelero_Read(Accelero_TypeDef * ptr){
	
	
	
}

