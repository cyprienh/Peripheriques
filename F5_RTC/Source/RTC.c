#include "RTC.h"
#include "Driver_I2C.h"

// ================================
// 		F5 - RTC
//		Cyprien Heusse
// ================================

// Write the correct values into the RTC's registers to set date & time
void RTC_Set_Time_Date(I2C_TypeDef* I2C, int s, int min, int h, int w, int d, int m, int y) {
	char data[1];
	if(s<60 && min<60 && h<24 && w<=7 && d<=31 && m<=12 && y<100) {
		data[0] = (s/10 << 4) | (s%10 << 0);									// Seconds
		I2C_Write(I2C, 0x68, 0x00, data, 1);
		data[0] = (min/10 << 4) | (min%10 << 0);							// Minutes
		I2C_Write(I2C, 0x68, 0x01, data, 1);
		data[0] =  (0x1 << 6) | (h/10 << 4) | (h%10 << 0);		// Hours
		I2C_Write(I2C, 0x68, 0x02, data, 1);
		data[0] = (w%10 << 0);																// Week day
		I2C_Write(I2C, 0x68, 0x03, data, 1);
		data[0] = (d/10 << 4) | (d%10 << 0);									// Day
		I2C_Write(I2C, 0x68, 0x04, data, 1);
		data[0] = (m/10 << 4) | (m%10 << 0);									// Month
		I2C_Write(I2C, 0x68, 0x05, data, 1);
		data[0] = (y/10 << 4) | (y%10 << 0);									// Year
		I2C_Write(I2C, 0x68, 0x06, data, 1);
		data[0] = 0x11;																				// Control
		I2C_Write(I2C, 0x68, 0x07, data, 1);
	}
}

// Build String from RTC's data by reading the values and converting them to String
void RTC_Get_Date_Time(I2C_TypeDef* I2C, char* time) {
	char data[1];
	I2C_Read(I2C, 0x68, 0x02, data, 1);
	time[11] = ((data[0] >> 4) & 0x3) + 48;
	time[12] = (data[0] & 0xf) + 48;
	I2C_Read(I2C, 0x68, 0x01, data, 1);
	time[14] = ((data[0] >> 4) & 0x7) + 48;
	time[15] = (data[0] & 0xf) + 48;
	I2C_Read(I2C, 0x68, 0x00, data, 1);
	time[17] = ((data[0] >> 4) & 0x7) + 48;
	time[18] = (data[0] & 0xf) + 48;
	
	I2C_Read(I2C, 0x68, 0x04, data, 1);
	time[0] = ((data[0] >> 4) & 0x3) + 48;
	time[1] = (data[0] & 0xf) + 48;
	I2C_Read(I2C, 0x68, 0x05, data, 1);
	time[3] = ((data[0] >> 4) & 0x1) + 48;
	time[4] = (data[0] & 0xf) + 48;
	I2C_Read(I2C, 0x68, 0x06, data, 1);
	time[6] = ((data[0] >> 4) & 0xf) + 48;
	time[7] = (data[0] & 0xf) + 48;
}
