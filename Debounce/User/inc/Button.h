#ifndef __BUTTON__H__
#define __BUTTON__H__

#include "System_setup.h"

#define  DEBOUNCE_TIME  10


typedef enum {NOT_OK = 0, OK = !NOT_OK} DebounceState;

typedef struct {
    uint8_t state;           // Trạng thái ổn định hiện tại của nút (1: released, 0: pressed) Pull up
    uint8_t lastReading;     // Lần đọc trạng thái gần nhất
    uint32_t lastDebounceTime; // Thời điểm thay đổi trạng thái gần nhất
} ButtonDebounce;


DebounceState debounceButton(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ButtonDebounce *btn);

#endif  //!__BUTTON__H__