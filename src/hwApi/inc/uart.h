#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define BAUDRATE              115200
#define TXPIN                 GPIO_PIN_6
#define RXPIN                 GPIO_PIN_7
#define DATAPORT              GPIOB
#define UART_PRIORITY         15
#define UART_RX_SUBPRIORITY   0
#define MAXCLISTRING          100 // Biggest string the user will type

extern UART_HandleTypeDef huart1;

void uartInit();

void uartSendChar(char sendChar);
char uartGetChar(void);
void uartPrint(char string[]);

#endif // UART_H_
