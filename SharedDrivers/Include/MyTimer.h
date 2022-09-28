#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct {
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;


/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse  ) contenant les
informations de base
* @Note -> Fonction à lancer systématiquement avant d ’ aller plus en détail dans les
conf plus fines (PWM, codeur inc... )
*************************************************************************************************
*/

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer);
void MyTimer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*IT_function)(void));
void MyTimer_PWM(TIM_TypeDef *Timer, char Channel);

#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~0x1)

#endif
