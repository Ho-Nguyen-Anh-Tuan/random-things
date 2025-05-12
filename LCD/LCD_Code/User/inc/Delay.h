#ifndef __DELAY__H__
#define __DELAY__H__

#include "stm32f10x_tim.h"

extern volatile uint32_t TIM2_Counter;

void delay_ms(uint32_t time);

#endif //!__DELAY__H__