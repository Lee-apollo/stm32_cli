/*
 * hwGPIO.c
 *
 *  Created on: 1. 10. 2015
 *      Author: z003jsvn
 */

//#include "global.h"
#include "hwGPIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------
#if 0
uint32_t hwSimPort [eGPIO_PORT_COUNT] = {0};
uint32_t hwSimDDR [eGPIO_PORT_COUNT] = {0};

// DDR - 0 = input, 1 = output

void gpioInit(GPIO_t * gpio, eGPIO_Mode mode)
{
	//printf("\nGPIO Init pin: %d, port: %d, ", gpio->pin, gpio->port);
	if (mode == eGPIO_MODE_Input)
	{
		//printf("mode: input");
		hwSimDDR[gpio->port] &= ~(1 << gpio->pin);
	}
	else if (mode == eGPIO_MODE_OUTPUT_PP)
	{
		//printf("mode: output");
		hwSimDDR[gpio->port] |= (1 << gpio->pin);
	}
	/*else
	{
		printf("\nERROR GPIO init");
	}*/
}

void gpioSet(GPIO_t * gpio)
{
	//printf("\nGPIO SET pin: %d, port: %d", gpio->pin, gpio->port);
	hwSimDDR[gpio->port] |= (1 << gpio->pin);
}

void gpioReset(GPIO_t * gpio)
{
	hwSimDDR[gpio->port] &= ~(1 << gpio->pin);
	//printf("\nGPIO RESET pin: %d, port: %d", gpio->pin, gpio->port);
}

bool_t gpioGetState(GPIO_t * gpio)
{
	return ((hwSimDDR[gpio->port] & (1 << gpio->pin)) == 0) ? FALSE: TRUE;
}

//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//
#endif

// ----------------------------------------------------------------------------
void gpioInit(GPIO_t * gpio, eGPIO_Mode mode)
{
	  // Enable GPIO Peripheral clock
	  RCC->AHB1ENR |= RCC_MASKx(gpio->port);

	  GPIO_InitTypeDef GPIO_InitStructure;

	  // Configure pin in output push/pull mode
	  GPIO_InitStructure.Pin = (1 << gpio->pin);
	  GPIO_InitStructure.Mode = mode;
	  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	  GPIO_InitStructure.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIO_PORTx(gpio->port), &GPIO_InitStructure);
}
void gpioSet(GPIO_t * gpio)
{
    HAL_GPIO_WritePin(GPIO_PORTx(gpio->port), (1 << gpio->pin), GPIO_PIN_SET);
}

void gpioReset(GPIO_t * gpio)
{
	HAL_GPIO_WritePin(GPIO_PORTx(gpio->port), (1 << gpio->pin), GPIO_PIN_RESET);
}

bool_t gpioGetState(GPIO_t * gpio)
{
	return (bool_t)HAL_GPIO_ReadPin(GPIO_PORTx(gpio->port), (1 << gpio->pin));
}

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
