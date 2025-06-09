#include "Button.h"
#include "Delay.h"
#include "IRQHandler.h"

DebounceState debounceButton(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ButtonDebounce *btn)
{
    uint8_t reading = GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);

    if (reading != btn->lastReading)
        btn->lastDebounceTime = TIM2_Counter;   // khi có điện áp thay đổi thì lưu lại thời gian
    
    // kiểm tra đủ thời gian debounce chưa
    if ((TIM2_Counter - btn->lastDebounceTime) >= DEBOUNCE_TIME)
    {
        if (reading != btn->state)  // so sánh trạng thái hiện tại với trạng thái nút nhấn
        {
            btn->state = reading;   // gán trạng thái đã ổn định cho nút nhấn

            if (btn->state == 0)    // Nếu pull down thì state == 1?
                return OK;
        }
    }

    btn->lastReading = reading;
    
    return NOT_OK;
}