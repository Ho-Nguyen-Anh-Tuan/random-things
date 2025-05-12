#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

#define Led7Seg_A	GPIO_Pin_0
#define Led7Seg_B	GPIO_Pin_1
#define Led7Seg_C	GPIO_Pin_2
#define Led7Seg_D	GPIO_Pin_3
#define Led7Seg_E	GPIO_Pin_4
#define Led7Seg_F	GPIO_Pin_5
#define Led7Seg_G	GPIO_Pin_6

#define LED1	GPIO_Pin_0
#define LED2	GPIO_Pin_1

#define RCC_Led7Seg_Signal	RCC_APB2Periph_GPIOA
#define RCC_Led7Seg_Power		RCC_APB2Periph_GPIOB

#define Led7Seg_Signal_GPIO	GPIOA
#define Led7Seg_Power_GPIO	GPIOB


void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_Led7Seg_Signal | RCC_Led7Seg_Power, ENABLE);
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
	GPIO_Initstruct.GPIO_Pin = LED1 | LED2;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Led7Seg_Power_GPIO, &GPIO_Initstruct);
}

void TIM_Config(){
	TIM_TimeBaseInitTypeDef TIM_Initstruct;
	
	TIM_Initstruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Initstruct.TIM_Period = 0xFFFF;
	TIM_Initstruct.TIM_Prescaler = 7200 - 1;	// 0.1ms/tick
	
	TIM_TimeBaseInit(TIM2, &TIM_Initstruct);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint32_t time){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < time * 10);
}

void delay(uint32_t time){
	for(uint32_t i = 0; i < time; i++);
}

uint8_t L7Seg_Code[10] = {
    0xC0, // 0: 0b1100 0000
    0xF9, // 1: 0b1111 1001
    0xA4, // 2: 0b1010 0100
    0xB0, // 3: 0b1011 0000
    0x99, // 4: 0b1001 1001
    0x92, // 5: 0b1001 0010
    0x82, // 6: 0b1000 0010
    0xF8, // 7: 0b1111 1000
    0x80, // 8: 0b1000 0000
    0x90  // 9: 0b1001 0000
};

int main(){
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	// led 1 = 0
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	// led 2 = 0;
	
	while(1){
		uint8_t i, j;
		
		for(i = 0; i < 100; i++){
			for(j = 0; j < 24; j++){
				
				/* hang chuc */
				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i/10]);
				GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
				delay(5000);
				GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
				
				/* hang don vi */
				GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[i%10]);
				GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
				delay(5000);
				GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
			}
		}
	}
}

// --------------------------------------------------------------------

//#include "stm32f10x.h"       // Thu vi?n device header
//#include "stm32f10x_rcc.h"   // Thu vi?n c?u hình clock
//#include "stm32f10x_gpio.h"  // Thu vi?n c?u hình GPIO

//// Ð?nh nghia các chân n?i v?i LED 7 do?n (ch? dùng 7 chân: A-G)
//#define LED7SEG_A   GPIO_Pin_0
//#define LED7SEG_B   GPIO_Pin_1
//#define LED7SEG_C   GPIO_Pin_2
//#define LED7SEG_D   GPIO_Pin_3
//#define LED7SEG_E   GPIO_Pin_4
//#define LED7SEG_F   GPIO_Pin_5
//#define LED7SEG_G   GPIO_Pin_6

//// Ð?nh nghia c?ng và clock cho LED 7 do?n
//#define RCC_LED7SEG   RCC_APB2Periph_GPIOA
//#define LED7SEG_PORT  GPIOA

//// M?ng mã hi?n th? cho các s? 0-9 trên LED 7 do?n (Common Anode: logic 0 d? b?t)
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

//// C?u hình clock cho GPIOA
//void RCC_Config(void) {
//    RCC_APB2PeriphClockCmd(RCC_LED7SEG, ENABLE);
//}

//// C?u hình các chân c?a PORTA làm d?u ra
//void GPIO_Config(void) {
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin = LED7SEG_A | LED7SEG_B | LED7SEG_C |
//                                  LED7SEG_D | LED7SEG_E | LED7SEG_F | LED7SEG_G;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // Ch? d? d?y
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // T?c d? 50MHz
//    GPIO_Init(LED7SEG_PORT, &GPIO_InitStructure);
//}

////void TIM_Config(){
////	TIM_TimeBaseInitTypeDef TIM_InitStructure;
////	
////	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
////	TIM_InitStructure.TIM_Prescaler = 7200 - 1;					// 0.1ms count++
////	TIM_InitStructure.TIM_Period = 0xFFFF;
////	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
////	
////	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
////	TIM_Cmd(TIM2, ENABLE);
////}

////void delay_ms(uint32_t time){
////	TIM_SetCounter(TIM2, 0);
////	while(TIM_GetCounter(TIM2) < time * 10){}
////}

//// Hàm delay don gi?n (không chính xác v? th?i gian)
//void delay(uint32_t time) {
//    for(uint32_t i = 0; i < time; i++);
//}

//int main(void) {
//    RCC_Config();
//    GPIO_Config();

//    while(1) {
//        // Duy?t t? 0 d?n 9 và hi?n th? t?ng s? trên LED 7 do?n
//        for (int num = 0; num < 10; num++) {
//            // Ghi giá tr? tuong ?ng vào c?ng (ch? có 7 chân A-G, bit th? 7 c?a s? hex s? b? b? qua)
//            GPIO_Write(LED7SEG_PORT, L7Seg_Code[num]);
//            delay(500000); // Delay, di?u ch?nh giá tr? này cho phù h?p v?i mô ph?ng
//        }
//    }
//}

//------------------------------------------------------------------------

//#include "stm32f10x.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_tim.h"

//#define Led7Seg_A    GPIO_Pin_0
//#define Led7Seg_B    GPIO_Pin_1
//#define Led7Seg_C    GPIO_Pin_2
//#define Led7Seg_D    GPIO_Pin_3
//#define Led7Seg_E    GPIO_Pin_4
//#define Led7Seg_F    GPIO_Pin_5
//#define Led7Seg_G    GPIO_Pin_6

//#define LED1        GPIO_Pin_0  // Ch?n digit 1 (hàng ch?c)
//#define LED2        GPIO_Pin_1  // Ch?n digit 2 (hàng don v?)

//#define RCC_Led7Seg_Signal  RCC_APB2Periph_GPIOA
//#define RCC_Led7Seg_Power   RCC_APB2Periph_GPIOB

//#define Led7Seg_Signal_GPIO  GPIOA
//#define Led7Seg_Power_GPIO   GPIOB

//void RCC_Config(){
//    RCC_APB2PeriphClockCmd(RCC_Led7Seg_Signal | RCC_Led7Seg_Power, ENABLE);
//}

//void GPIO_Config(){
//    GPIO_InitTypeDef GPIO_Initstruct;
//    
//    // C?u hình các chân di?u khi?n LED 7 do?n (PA0 - PA6)
//    GPIO_Initstruct.GPIO_Pin = Led7Seg_A | Led7Seg_B | Led7Seg_C | Led7Seg_D |
//                                Led7Seg_E | Led7Seg_F | Led7Seg_G;
//    GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(Led7Seg_Signal_GPIO, &GPIO_Initstruct);
//    
//    // C?u hình các chân ch?n digit (PB0, PB1)
//    GPIO_Initstruct.GPIO_Pin = LED1 | LED2;
//    GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(Led7Seg_Power_GPIO, &GPIO_Initstruct);
//}

//void TIM_Config(){
//    TIM_TimeBaseInitTypeDef TIM_Initstruct;
//    TIM_Initstruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_Initstruct.TIM_Period = 0xFFFF;
//    TIM_Initstruct.TIM_Prescaler = 7200 - 1;  // 0.1ms per tick
//    TIM_TimeBaseInit(TIM2, &TIM_Initstruct);
//    TIM_Cmd(TIM2, ENABLE);
//}

//void delay_ms(uint32_t time){
//    TIM_SetCounter(TIM2, 0);
//    while(TIM_GetCounter(TIM2) < time * 10);
//}

//// Mã hi?n th? cho các s? 0-9 (Common Anode: 0 d? b?t)
//uint8_t L7Seg_Code[10] = {
//    0xC0, // 0
//    0xF9, // 1
//    0xA4, // 2
//    0xB0, // 3
//    0x99, // 4
//    0x92, // 5
//    0x82, // 6
//    0xF8, // 7
//    0x80, // 8
//    0x90  // 9
//};

//int main(){
//    RCC_Config();
//    GPIO_Config();
//    TIM_Config();
//    
//    // Reset ban d?u các chân ch?n digit
//    GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//    GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//    
//    while(1){
//        // Quét liên t?c d? hi?n th? s? c? d?nh:
//        // LED1 hi?n th? "1" (digit hàng ch?c)
//        // LED2 hi?n th? "2" (digit hàng don v?)
//        for (int i = 0; i < 100; i++) {
//            // Hi?n th? s? "1" cho LED1
//            GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[1]);
//            GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
//            delay_ms(5);
//            GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
//            
//            // Hi?n th? s? "2" cho LED2
//            GPIO_Write(Led7Seg_Signal_GPIO, L7Seg_Code[2]);
//            GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
//            delay_ms(5);
//            GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
//        }
//    }
//}





