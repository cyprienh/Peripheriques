#include "Driver_GPIO.h"
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include "Driver_UART.h"
#include "Driver_STD.h"
#include "Driver_I2C.h"
#include "Driver_SysTick.h"
#include "MySPI.h"

#include "stm32f10x.h"
#include "math.h"

#include "Orientation.h"
#include "Bordage.h"
#include "Transmission.h"
#include "RTC.h"
#include "AntiChavirement.h"


// F3 
Accelero_TypeDef MyAccelero;
float Angle;
float Xg;
float Yg;
float Zg;

unsigned long tick = 0;

extern char Chavirement;
extern char AChavire;

void Tick_Handler() {
	++tick;
}

int main (void) {
	unsigned long last_tick = 0;
	
	// F1 
	// Bordage_a and Bordage_theta defined as external in bordage.c
	// To be used in transmission.c
	float Bordage_Commande;
	GPIO_Struct_TypeDef GPIO_StructA1;
	Timer_Struct_TypeDef Timer;
	
	// F2
	float Plateau_DutyCycle;
	
	// F3
	//Chavirement defined as external 
	
	// F4 
	GPIO_Struct_TypeDef GPIO_StructC4;
	
	// ------------------------------------------------
	//
	// F1 - Variable declaration and inits
	//
	// ------------------------------------------------
	
	// PWM init for sail's servo motor
	GPIO_StructA1.GPIO=GPIOA;
	GPIO_StructA1.GPIO_Pin=1;
	GPIO_StructA1.GPIO_Conf=AltOut_Ppull;
	GPIO_Init(&GPIO_StructA1);
	
	Timer.Timer = TIM2;
	Timer.ARR = 1999; 
	Timer.PSC = 719;	

	Timer_Init(&Timer);
	Timer_Start(TIM2);
	Timer_PWM(TIM2, 2);
	
	Bordage_Init();
	
	// ------------------------------------------------
	//
	// F2 - Variable declaration and inits
	//
	// ------------------------------------------------
	
	Orientation_RX = 0;
	
	Orientation_Init();																// Init GPIO and Timer and USART RX
	Orientation_ActiveIT(&(Orientation_Receive));			// Init Interrupt on USART RX
	
	
	// ------------------------------------------------
	//
	// F3 - Variable declaration and inits
	//
	// ------------------------------------------------
	
	Angle = 0;
	Chavirement = 0;
	AChavire = 0;
	MyAccelero.AccX = 0;
	MyAccelero.AccY = 0;
	MyAccelero.AccZ = 0;
	
	//Initialisation SPI
  MySPI_Init(SPI1); 		
	Chavirement_Config();
	
	// ------------------------------------------------
	//
	// F5 - Variable declaration and inits
	//
	// ------------------------------------------------
		
	I2C_Init(I2C1);
	RTC_Set_Time_Date(I2C1, 0,33,11,4,10,11,22);
	
	
	// ------------------------------------------------
	//
	// F4 - Variable declaration and inits
	//
	// ------------------------------------------------
	
	GPIO_StructC4.GPIO=GPIOC;
	GPIO_StructC4.GPIO_Pin=4;
	GPIO_StructC4.GPIO_Conf=In_Analog;
	GPIO_Init(&GPIO_StructC4);
	
	Transmission_Init();
	
	// ------------------------------------------------
	//
	// main
	//
	// ------------------------------------------------
	
	SysTick_Init(&Tick_Handler);
	
	do {		
		
		if(last_tick != tick) {
			last_tick = tick;
			
			// F1 & F3
			Bordage_a = Bordage_Get_Angle();
			if (Chavirement == 0) {
				if (Bordage_a > 180.0)																// Angle between ]-180;180]° not [0;360]°
					Bordage_a = Bordage_a-360.0;
				if(Bordage_a > 45.0 && Bordage_a < 180.0) {						
					Bordage_Commande = A*Bordage_a+B;
					Bordage_theta = (int)(Atheta*Bordage_a+Btheta);
				} else if(Bordage_a < -45.0 && Bordage_a > -180.0) {
					Bordage_Commande = A*(-Bordage_a)+B;
					Bordage_theta = (int)(Atheta*(-Bordage_a)+Btheta);
				} else {																							// Dead zone
					Bordage_Commande = DT_0;
					Bordage_theta = 0;
				}
			}
			else {
				Bordage_Commande = DT_0;															// Slacken the sail
				Bordage_theta = 0;
			}
			Timer_PWM_Set_Duty_Cycle(TIM2, 2, Bordage_Commande);
			
			// F2
			if (Orientation_RX <= 0) {															// Turning left
				Plateau_DutyCycle = (float)(-Orientation_RX)/100;
				
				Timer_PWM(TIM3, 3);												
				Timer_PWM_Set_Duty_Cycle(TIM3, 3, Plateau_DutyCycle);
				GPIO_Reset(GPIOB, 1);																	// Set dir bit to 0
				
			}	else {																								// Turning right
				Plateau_DutyCycle = (float)Orientation_RX/100;
				
				Timer_PWM(TIM3, 3);												
				Timer_PWM_Set_Duty_Cycle(TIM3, 3, Plateau_DutyCycle);
				GPIO_Set(GPIOB, 1);																		// Set dir bit to 1
			}
			
			// F3
			Chavirement_Accelero_Read(&MyAccelero); 								// Get accelerometer values
			
			// Normalised coordinates
			Xg = MyAccelero.AccX * 4e-3;
			Yg = MyAccelero.AccY * 4e-3;
			Zg = MyAccelero.AccZ * 4e-3;
			if (Yg*Zg < 0){
				Angle = atan(-(Yg/Zg));
			} else 
				Angle = atan(Yg/Zg);
			if (fabs(Angle) >= 0.698){ 															// 40 degrees in rad
				Chavirement = 1;
				AChavire = 1;
			}	else 
				Chavirement = 0;
			
			// F4 & F5 - interrupts or systick
			#if USE_INTERRUPT_TIMER == 0
				if(last_tick % 3000 == 0) {
					Transmission_SendRegInfo();
				}
			#endif
		}
		
	} while (1);
}

