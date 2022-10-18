#ifndef DRIVER_TIMER_H
#define DRIVER_TIMER_H

#include "stm32f10x.h"

typedef struct {
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} Timer_Struct_TypeDef ;


/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse  ) contenant les
informations de base
* @Note -> Fonction à lancer systématiquement avant d ’ aller plus en détail dans les
conf plus fines (PWM, codeur inc... )
*************************************************************************************************
*/

void Timer_Init(Timer_Struct_TypeDef * Timer);
void Timer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*IT_function)(void));
void Timer_PWM(TIM_TypeDef *Timer, char Channel);
void Timer_PWM_Set_Duty_Cycle(TIM_TypeDef *Timer, char Channel, float DutyCycle);

#define Timer_Start(Timer) (Timer->CR1 |= 0x1)
#define Timer_Stop(Timer) (Timer->CR1 &= ~0x1)

#endif
