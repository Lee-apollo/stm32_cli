/*
 * serial.c
 *
 *  Created on: 22. 9. 2015
 *      Author: z003jsvn
 */

//#include "myStdlib.h"
#include "global.h"

#include "uart.h"
#include "serial.h"

extern void (*stdlibPrintfOutputCB)(char);
extern char (*stdlibGetCharCB)(void);

void serialInit(void)
{
	// Init stdlibPrintfOutputCB
	stdlibPrintfOutputCB = serialPutChar;
	stdlibGetCharCB = serialGetChar;
	uartInit();
	return;
}

void serialPutChar(char setChar)
{
	// TODO add better solution for windows newline
	if ('\n' == setChar)
	{
		uartSendChar('\r');
		uartSendChar('\n');
	}
	else
	{
		uartSendChar(setChar);
	}
}

char serialGetChar(void)
{
	return uartGetChar();
}

/*
void serialPutString(const char * data)
{
	const char * character = data;
	while( *character != '\0')
	{
		serialPutChar(*character);
		character++;
	}
}
*/

