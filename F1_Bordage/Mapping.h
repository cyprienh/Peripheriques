#define DT_00 0.0
#define DT_90 0.0

#define BORDAGE_TIMER_INCREMENTAL TIM1
#define BORDAGE_TIMER_PWM					TIM2

#define ORIENTATION_UART					USART3
#define ORIENTATION_TIMER_PWM			TIM3

#define	CHAVIREMENT_SPI						SPI1

// F1 - Bordage
void Bordage_Init();
void Bordage_Calibration_Handler();		// EN TOUT PREMIER -> INTERRUPT HANDLER
float Bordage_Get_Angle();

// F2 - Orientation
void Orientation_Init();
void Orientation_Receive_Handler(); 	// INTERRUPT HANDLER

// F3 - Chavirement
void Chavirement_Init();							// Driver ?? -> SPI_Init();
void Chavirement_Config();
int Chavirement_Read();								// Lecture de l'accéléromètre

// F4 - Communication
// RIEN -> Utilisation driver UART
