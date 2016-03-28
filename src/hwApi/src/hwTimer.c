/*
 * hwTimer4.c
 *
 *  Created on: Mar 12, 2016
 *      Author: apollo
 */

#include "hwTimer.h"

TIM_HandleTypeDef handleTimer4;

void TIM_Timer4_Init()
{
    __TIM4_CLK_ENABLE();

    handleTimer4.Instance = TIM4; //Select timer
    handleTimer4.Init.Prescaler = 100; //
    handleTimer4.Init.CounterMode = TIM_COUNTERMODE_UP;
    handleTimer4.Init.Period = 16800;
    handleTimer4.Init.RepetitionCounter = 0;
    handleTimer4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(&handleTimer4);
    //HAL_TIM_PWM_Start_IT(&handleTimer4);

    //HAL_TIM_Base_Init(&handleTimer4);     // Init timer
    //HAL_TIM_Base_Start_IT(&handleTimer4); // start timer interrupts
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
    //HAL_NVIC_EnableIRQ(TIM4_IRQn);
    /*
    //handleTimer4.Channel = 1;

    HAL_TIM_PWM_Init(&handleTimer4);
    */
    //HAL_TIM_Base_Init(&handleTimer4);     // Init timer
    //HAL_TIM_Base_Start_IT(&handleTimer4); // start timer interrupts

    /*
    HAL_TIM_ConfigClockSource(&handleTimer4, &sClockSourceConfig);

    TIM_ClockConfigTypeDef sClockSourceConfig;

    sClockSourceConfig.ClockFilter = 0x0;
    sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_RISING;
    sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV8;
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_IC_InitTypeDef sConfigOC;

    */
}

void TIM4_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&handleTimer4, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
    {
        if (__HAL_TIM_GET_ITSTATUS(&handleTimer4, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(&handleTimer4, TIM_FLAG_UPDATE);

            static int tmp = 0;
            tmp++;
        }
    }
}

void InitializePWM()
{
    __GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    TIM_OC_InitTypeDef outputChannelInit = {0,};

    outputChannelInit.OCMode = TIM_OCMODE_PWM1;
    outputChannelInit.Pulse = 840;
    outputChannelInit.OCPolarity = TIM_OCPOLARITY_HIGH;
    outputChannelInit.OCFastMode = TIM_OCFAST_DISABLE;
    outputChannelInit.OCIdleState = TIM_OCIDLESTATE_SET;

    //HAL_TIM_PWM_Start_IT(&handleTimer4);
    HAL_TIM_PWM_ConfigChannel(&handleTimer4, &outputChannelInit, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&handleTimer4, &outputChannelInit, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&handleTimer4, &outputChannelInit, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&handleTimer4, &outputChannelInit, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&handleTimer4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&handleTimer4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&handleTimer4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&handleTimer4, TIM_CHANNEL_4);
    //HAL_TIM_PWM_Start_IT(&handleTimer4, TIM_CHANNEL_1);
    //HAL_TIM_PWM_Start_IT(&handleTimer4, TIM_CHANNEL_2);
    //HAL_TIM_PWM_Start_IT(&handleTimer4, TIM_CHANNEL_3);
    //HAL_TIM_PWM_Start_IT(&handleTimer4, TIM_CHANNEL_4);

}

void updatePulseWidth(eTimer timer, uint32_t pulse, uint32_t channel)
{
    TIM_OC_InitTypeDef outputChannelInit = {0,};

    outputChannelInit.OCMode = TIM_OCMODE_PWM1;
    outputChannelInit.Pulse = pulse;
    outputChannelInit.OCPolarity = TIM_OCPOLARITY_HIGH;
    outputChannelInit.OCFastMode = TIM_OCFAST_DISABLE;
    outputChannelInit.OCIdleState = TIM_OCIDLESTATE_SET;

    //HAL_TIM_PWM_Start_IT(&handleTimer4);
    switch(timer)
    {
    case eTimer4:
        HAL_TIM_PWM_ConfigChannel(&handleTimer4, &outputChannelInit, channel);
        HAL_TIM_PWM_Start(&handleTimer4, channel);

        break;
    case eTimer1:
    case eTimer2:
    case eTimer3:
    default:
        break;
    }
    return;
}


