#include "Delay.h"
#include "stm32f10x_tim.h"

volatile uint32_t TIM2_Counter = 0;

void delay_ms(uint32_t time)
{
    TIM2_Counter = 0;
    while (TIM2_Counter < time)
    {
        // wait
    }
}