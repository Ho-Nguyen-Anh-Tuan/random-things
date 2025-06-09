#include "IRQHandler.h"
#include "Button.h"

volatile uint32_t TIM2_Counter = 0;
volatile uint8_t EXTI0_Flag = 0;

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM2_Counter++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void EXTI0_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		EXTI0_Flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}