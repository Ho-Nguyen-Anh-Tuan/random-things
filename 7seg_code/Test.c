#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

//#define Led7Seg_A	GPIO_Pin_0
//#define Led7Seg_B	GPIO_Pin_1
//#define Led7Seg_C	GPIO_Pin_2
//#define Led7Seg_D	GPIO_Pin_3
//#define Led7Seg_E	GPIO_Pin_4
//#define Led7Seg_F	GPIO_Pin_5
//#define Led7Seg_G	GPIO_Pin_6

//uint8_t L7Seg_Code[10] = {
//    0xC0, // 0: 0b1100 0000
//    0xF9, // 1: 0b1111 1001
//    0xA4, // 2: 0b1010 0100
//    0xB0, // 3: 0b1011 0000
//    0x99, // 4: 0b1001 1001
//    0x92, // 5: 0b1001 0010
//    0x82, // 6: 0b1000 0010
//    0xF8, // 7: 0b1111 1000
//    0x80, // 8: 0b1000 0000
//    0x90  // 9: 0b1001 0000
//};

/*------------ Pin Port cho cau B ----------------*/

#define Led7Seg_A	GPIO_Pin_2
#define Led7Seg_B	GPIO_Pin_5
#define Led7Seg_C	GPIO_Pin_3
#define Led7Seg_D	GPIO_Pin_1
#define Led7Seg_E	GPIO_Pin_0
#define Led7Seg_F	GPIO_Pin_6
#define Led7Seg_G	GPIO_Pin_4

uint8_t L7Seg_Code[10] = {
    0x10, // 0: 001 0000
    0x57, // 1: 101 0111
    0x48, // 2: 100 1000
    0x41, // 3: 100 0001
    0x07, // 4: 000 0111
    0x21, // 5: 010 0001
    0x20, // 6: 010 0000
    0x53, // 7: 101 0011
    0x00, // 8: 000 0000
    0x01  // 9: 000 0001
};

//------------------------------------------------

#define LED1	GPIO_Pin_0
#define LED2	GPIO_Pin_1
#define LED3	GPIO_Pin_2
#define LED4	GPIO_Pin_3
#define LED5	GPIO_Pin_4
#define LED6	GPIO_Pin_5

/* 7 seg RCC */
#define RCC_Led7Seg_Signal	RCC_APB2Periph_GPIOA
#define RCC_Led7Seg_Power		RCC_APB2Periph_GPIOB

/* 7 seg GPIO */
#define Led7Seg_Signal_GPIO	GPIOA
#define Led7Seg_Power_GPIO	GPIOB


void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_Led7Seg_Signal | RCC_Led7Seg_Power, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
	GPIO_InitTypeDef GPIO_Initstruct;
	
	/* Initalize GPIO A */ 
	GPIO_Initstruct.GPIO_Pin = Led7Seg_A | Led7Seg_B | Led7Seg_C | Led7Seg_D |
														Led7Seg_E | Led7Seg_F | Led7Seg_G;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Led7Seg_Signal_GPIO, &GPIO_Initstruct);
	
	/* Initalize GPIO B */
	GPIO_Initstruct.GPIO_Pin = LED1 | LED2 | LED3 | LED4 | LED5 | LED6;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Led7Seg_Power_GPIO, &GPIO_Initstruct);
}

void TIM_Config(){
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	
	// Goal: count up 1 every 0.1ms
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // xung clock mcu : 1 = 72MHz
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;	// 0,1ms count++
	TIM_InitStruct.TIM_Period = 0xFFFF;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
	TIM_Cmd(TIM2, ENABLE);
}	

void delay_ms(uint32_t TimeDelay){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < TimeDelay * 10);
}


/* Test quet led */

//int main(){
//	RCC_Config();
//	GPIO_Config();
//	TIM_Config();
//	
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
//	
//	while(1){
//		uint8_t i, j;
//		
//		for(i = 0; i < 100; i++){
//			for(j = 0; j < 11; j++){
//				
//				
//				/* hang chuc */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//				delay_ms(4);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//				
//				/* hang don vi */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i%10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//				delay_ms(4);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//			}
//		}	
//	}
//}

/*-------------------------------------------------------------------
			Cau A
*/

//int main(){
//	RCC_Config();
//	GPIO_Config();
//	TIM_Config();
//	
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
//	
//	while(1){
//		uint32_t number = 31737;		// goal: 031737
//		
//		for(number = 31737;;){
//			// hàng tram ngàn 
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[number / 100000]); // 31737 / 100000 = 0
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//			
//			// hàng ch?c ngàn 
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(number / 10000) % 10]);	// 31737 / 10000 = 3 => 3 % 10 = 3
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//			
//			// hàng ngàn 
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(number / 1000) % 10]); // 31737 / 1000 = 3 => 31 % 10 = 1
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
//			
//			// hàng tram 
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(number / 100) % 10]);
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED4);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED4);
//			
//			// hàng ch?c
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(number / 10) % 10]);
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED5);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED5);
//			
//			// hàng don v?
//			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[number % 10]);
//			GPIO_SetBits(Led7Seg_Power_GPIO, LED6);
//			delay_ms(5);
//			GPIO_ResetBits(Led7Seg_Power_GPIO, LED6);
//		}
//		
//	}
//}

/*------------------------------------------------------------------ 
			Cau C
*/

//int main(){
//	RCC_Config();
//	GPIO_Config();
//	TIM_Config();
//	
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
//	
//	while(1){
//		uint16_t i, j;
//		
//		for(i = 0; i < 737; i++){			// goal: 737
//			for(j = 0; j < 12; j++){
//				
//				/* hang tram */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/100]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//				
//				/* hang chuc */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(i / 10) % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//				
//				/* hang don vi */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
//			}
//			
//		}
//		
//		while(i == 737){
//			/* hang tram */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/100]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//				delay_ms(10);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//				
//				/* hang chuc */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(i / 10) % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//				delay_ms(10);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//				
//				/* hang don vi */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
//				delay_ms(10);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
//		}
//	}
//}

/*------------------------------------------------------------------------- 
			Cau D
*/

//int main(){
//	RCC_Config();
//	GPIO_Config();
//	TIM_Config();
//	
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
//	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
//	
//	while(1){
//		uint16_t i, j;
//		
//		for(i = 737; i > 0; i--){			// goal: 737
//			for(j = 0; j < 12; j++){
//				
//				/* hang tram */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/100]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//				
//				/* hang chuc */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(i / 10) % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//				
//				/* hang don vi */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
//			}
//			
//		}
//		
//		while(i == 0){
//			/* hang tram */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/100]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//				
//				/* hang chuc */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(i / 10) % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//				
//				/* hang don vi */
//				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i % 10]);
//				GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
//				delay_ms(1);
//				GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
//		}
//	}
//}

/*-----------------------------------------------------------------------------
			Cau E
*/

int main(){
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
	
	uint16_t count_up = 0;
	uint16_t count_down = 999;
	
	while(1){
	
		for(int i = 0; i < 4; i++){
			/* 3 led dau count up */
			
			// hang tram
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_up / 100]);	// 973 /100 = 9
			GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
			
			// hang chuc
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(count_up / 10) % 10]);	// 973 / 10 = 97 -> 97 % 10 = 7
			GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
			
			// hang don vi
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_up % 10]);	// 973 % 10 = 3
			GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
			
			
			/* 3 led sau count down */
			
			// hang tram
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_down / 100]);	// 973 /100 = 9
			GPIO_SetBits(Led7Seg_Power_GPIO, LED4);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED4);
			
			// hang chuc
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(count_down / 10) % 10]);	// 973 / 10 = 97 -> 97 % 10 = 7
			GPIO_SetBits(Led7Seg_Power_GPIO, LED5);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED5);
			
			// hang don vi
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_down % 10]);	// 973 % 10 = 3
			GPIO_SetBits(Led7Seg_Power_GPIO, LED6);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED6);
			
		}
		
		if(count_up < 999)
			++count_up;
		if(count_down > 0)
			--count_down;
		
		while((count_up == 999) && (count_down == 0)){
			// hang tram
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_up / 100]);	// 973 /100 = 9
			GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
			
			// hang chuc
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(count_up / 10) % 10]);	// 973 / 10 = 97 -> 97 % 10 = 7
			GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
			
			// hang don vi
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_up % 10]);	// 973 % 10 = 3
			GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
			
			
			/* 3 led sau count down */
			
			// hang tram
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_down / 100]);	// 973 /100 = 9
			GPIO_SetBits(Led7Seg_Power_GPIO, LED4);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED4);
			
			// hang chuc
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[(count_down / 10) % 10]);	// 973 / 10 = 97 -> 97 % 10 = 7
			GPIO_SetBits(Led7Seg_Power_GPIO, LED5);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED5);
			
			// hang don vi
			GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[count_down % 10]);	// 973 % 10 = 3
			GPIO_SetBits(Led7Seg_Power_GPIO, LED6);
			delay_ms(5);
			GPIO_ResetBits(Led7Seg_Power_GPIO, LED6);
		}
	}
}


