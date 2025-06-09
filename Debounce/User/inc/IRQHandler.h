#ifndef __IRQHANDLER__H__
#define __IRQHANDLER__H__

#include "System_setup.h"
#include "Button.h"

extern volatile uint32_t TIM2_Counter;	// lưu thời điểm TIM2
extern volatile uint8_t EXTI0_Flag;

void TIM2_IRQHandler();
void EXTI0_IRQHandler();

#endif  //!__IRQHANDLER__H__