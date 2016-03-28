#ifndef HW_SERVO_H_
#define HW_SERVO_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define MIN_PULSE_WIDTH              1000 //us
#define MAX_PULSE_WIDTH              2000 //us

//timer pulse 840 = 1ms

#define microsecToTimerPulse(X) ((X * 840)/1000)

#define MIN_ANGLE             0
#define MAX_ANGLE             180 //us

#define SERVO_PIN                 GPIO_PIN_7
#define SERVO_PORT                GPIOB

void servoInit();
void servoSetPosition(int angle, uint32_t channel);
#endif // HW_SERVO_H_
