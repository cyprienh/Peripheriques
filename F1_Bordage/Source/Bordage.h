#ifndef BORDAGE_H
#define BORDAGE_H

#define DT_0 	0.06
#define DT_90	0.097

#define A (DT_90-DT_0)/(180-45)
#define B (180*DT_0-45*DT_90)/(180-45)

#define Atheta (90.0-0)/(180.0-45.0)
#define Btheta -45.0

#define BORDAGE_TIMER_INCREMENTAL TIM1
#define BORDAGE_TIMER_PWM					TIM2

#define GPIO_AB GPIOA
#define PIN_A		8
#define PIN_B		9

#define GPIO_Z 	GPIOD
#define PIN_Z 	2

	extern float Bordage_a;
	extern int Bordage_theta;

// F1 - Bordage
void Bordage_Init(void);
void Bordage_Calibration(void);		// EN TOUT PREMIER -> INTERRUPT HANDLER
float Bordage_Get_Angle(void);

#endif
