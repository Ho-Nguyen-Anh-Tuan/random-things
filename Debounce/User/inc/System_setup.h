#ifndef __SYSTEM_SETUP__H__
#define __SYSTEM_SETUP__H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "misc.h"

void RCC_Config();
void GPIO_Config();
void TIM_Config();
void EXTI_Config();
void NVIC_Config();

#endif  //!__SYSTEM_SETUP__H__