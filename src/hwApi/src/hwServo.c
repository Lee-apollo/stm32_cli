/*
 * servo.c
 *
 *  Created on: Mar 12, 2016
 *      Author: apollo
 */

#include "hwTimer.h"
#include "hwServo.h"

void servoInit()
{
    TIM_Timer4_Init();
    InitializePWM();
}

void servoSetPosition(int angle, uint32_t channel)
{
    uint32_t TIM_channel = 0;
    switch (channel)
    {
    case 1:
        TIM_channel = TIM_CHANNEL_1;
        break;

    case 2:
        TIM_channel = TIM_CHANNEL_2;
        break;

    case 3:
        TIM_channel = TIM_CHANNEL_3;
        break;

    case 4:
        TIM_channel = TIM_CHANNEL_4;
        break;

    default:
        return;
    }

    if ((MIN_ANGLE <= angle) && (angle <= MAX_ANGLE))
    {

        uint32_t pulseWidthUs = ((angle * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH)) / MAX_ANGLE) + MIN_PULSE_WIDTH;

        uint32_t timerPulse =  microsecToTimerPulse(pulseWidthUs);

        updatePulseWidth(eTimer4, timerPulse, TIM_channel);
    }
}


