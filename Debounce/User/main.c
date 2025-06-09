#include "System_setup.h"
#include "Delay.h"
#include "Button.h"
#include "IRQHandler.h"


uint8_t countMain = 0;
uint8_t exti0_count = 0;
uint8_t count1, count2, count3;

int main()
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	EXTI_Config();
	NVIC_Config();

	// tắt led 13
	GPIO_SetBits(GPIOC, GPIO_Pin_13);

	// khai báo soft timer
	SoftTimer timer1, timer2, timer3;

	// khởi tạo timer
	start_timer(&timer1, 500);
	start_timer(&timer2, 1000);
	start_timer(&timer3, 2000);

	ButtonDebounce myBtn = {1, 1, 0}; // Khởi tạo: released, lastReading = 1, lastDebounceTime = 0

	while (1)
	{
		// if (debounceButton(GPIOA, GPIO_Pin_0, &myBtn) == OK) 
		// {
		// 	countMain++;
		// }

		if (debounceButton(GPIOA, GPIO_Pin_0, &myBtn) && EXTI0_Flag) 
		{
			EXTI0_Flag = !EXTI0_Flag;
			exti0_count++;
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
		}		

		if (Is_Timer_Expired(timer1))
		{
			count1++;
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1));
			start_timer(&timer1, 500); // khởi động lại
		}

		if (Is_Timer_Expired(timer2))
		{
			count2++;
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2));
			start_timer(&timer2, 1000); // khởi động lại
		}

		if (Is_Timer_Expired(timer3))
		{
			count3++;
			GPIO_WriteBit(GPIOA, GPIO_Pin_3, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3));
			start_timer(&timer3, 2000); // khởi động lại
		}
	}
}

