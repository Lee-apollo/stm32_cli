#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

typedef enum
{
    eTimer1,
    eTimer2,
    eTimer3,
    eTimer4,
} eTimer;

void TIM_Timer4_Init();
void InitializePWM();
void updatePulseWidth(eTimer timer, uint32_t pulse, uint32_t channel);
#endif // UART_H_
