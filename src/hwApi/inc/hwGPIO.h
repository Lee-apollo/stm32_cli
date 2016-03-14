/*
 * gpio.h
 *
 *  Created on: 1. 10. 2015
 *      Author: z003jsvn
 */

#ifndef HW_HWGPIO_H_
#define HW_HWGPIO_H_

#include "global.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----- LED definitions ------------------------------------------------------


#define GPIO_PORTx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define PIN_MASK(_N)              (1 << (_N))
#define RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

typedef uint8_t GPIO_Pin_t;
//typedef uint8_t GPIO_Mode_t;
typedef uint8_t GPIO_Port_t;

typedef enum
{
	eGPIO_PORT_A = 0,
	eGPIO_PORT_B,
	eGPIO_PORT_C,
	eGPIO_PORT_D,
	eGPIO_PORT_E,
	eGPIO_PORT_H = 7,
	eGPIO_PORT_COUNT
} eGPIO_Port;

typedef enum
{
	eGPIO_MODE_Input = GPIO_MODE_INPUT,
	eGPIO_MODE_OUTPUT_PP = GPIO_MODE_OUTPUT_PP,
	eGPIO_MODE_OUTPUT_OD = GPIO_MODE_OUTPUT_OD,
	eGPIO_MODE_AF_PP = GPIO_MODE_AF_PP,
	eGPIO_MODE_AF_OD = GPIO_MODE_AF_OD,
} eGPIO_Mode;

typedef struct
{
	GPIO_Port_t port;
	GPIO_Pin_t pin;
} GPIO_t;

// ----------------------------------------------------------------------------

void gpioInit(GPIO_t * gpio, eGPIO_Mode mode);

void gpioSet(GPIO_t * gpio);

void gpioReset(GPIO_t * gpio);

bool_t gpioGetState(GPIO_t * gpio);

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

#endif /* HW_HWGPIO_H_ */
