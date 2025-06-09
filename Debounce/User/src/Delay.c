#include "Delay.h"
#include "IRQHandler.h"

void delay_ms(uint32_t time)
{
	uint32_t start_time = TIM2_Counter;
	while ((TIM2_Counter - start_time) < time)
	{
		// wait
	}
}

/**
  * @brief khởi tạo soft timer delay (ms)
  * @param  timer: địa chỉ timer cần khởi tạo
  * @param  delayTime: thời gian muốn delay (ms)
  * @retval None
  */
void start_timer(SoftTimer *timer, uint32_t delayTime)
{
	timer->start_tick = TIM2_Counter;	// lưu thời điểm bắt đầu đếm
	timer->delay_ms = delayTime; 		// gán thời gian delay
	timer->state = NOT_EXPIRED;			// đặt trạng thái ban đầu
}

/**
  * @brief kiểm tra timer hết thời gian chưa
  * @param  timer: timer cần kiểm tra
  * @retval timer state (OK or NOT_OK) 
  */
TimerState Is_Timer_Expired(SoftTimer timer)
{	
	/*thời điểm hiện tại - thời điểm bắt đầu timer >= thời gian delay */
	if ((TIM2_Counter - timer.start_tick) >= timer.delay_ms)
	{
		return EXPIRED;	// timer đếm xong
	}	
	
	return NOT_EXPIRED;
}