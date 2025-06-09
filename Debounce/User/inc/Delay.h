#ifndef __DELAY__H__
#define __DELAY__H__

#include "System_setup.h"

typedef enum {NOT_EXPIRED = 0, EXPIRED = !NOT_EXPIRED} TimerState;

typedef struct
{
	uint32_t start_tick;	// thời điểm bắt đầu
	uint32_t delay_ms;		// thời gian delay (ms)
	TimerState state;		// trạng thái timer: còn chạy hoặc hết thời gian
} SoftTimer;


void delay_ms(uint32_t time);
void start_timer(SoftTimer *timer, uint32_t delayTime);
TimerState Is_Timer_Expired(SoftTimer timer);

#endif  //!__DELAY__H__