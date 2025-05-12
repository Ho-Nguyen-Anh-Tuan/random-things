#ifndef __SETUP__H__
#define __SETUP__H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void RCC_Config();

void GPIO_Config();

void TIM_Config();

void UART_Config();

void NVIC_Config();

#endif //!__SETUP__H__