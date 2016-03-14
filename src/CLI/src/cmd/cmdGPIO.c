/*
 * cmdGPIO.c
 *
 *  Created on: 9. 10. 2015
 *      Author: z003jsvn
 */

#include "global.h"
#include "utils.h"
#include "myStdlib.h"
#include "hwGPIO.h"
#include "cliModule.h"

#include "cmdGPIO.h"

#include <string.h>
/* Command for GPIO control */

typedef enum
{
	eRead,
	eWrite,
	eInit,
	eUndef
} eMode;

/* Usage
 * Init:
 *  "GPIO -i PE15 in"
 *  "GPIO -i PE15 out"
 * Read:
 *  "GPIO -r PE15"
 * Write
 *  "GPIO -w PE15 0"
 *  "GPIO -w PE15 1"
*/
void cmdGpioFunction(int argc, const char * argv[])
{
	// Parse command mode
	eMode cmdMode = eUndef;

	if (2 <= argc)
	{
		if (0 == strcmp("-I", argv[1]))
		{
			if (argc != 4)
			{
				// TODO add function for error printing
				serialPrintf("Invalid command format\n");
				return;
			}
			cmdMode = eInit;
		}
		else if (0 == strcmp("-R", argv[1]))
		{
			if (argc != 3)
			{
				serialPrintf("Invalid command format\n");
				return;
			}
			cmdMode = eRead;
		}
		else if (0 == strcmp("-W", argv[1]))
		{
			if (argc != 4)
			{
				serialPrintf("Invalid command format\n");
				return;
			}
			cmdMode = eWrite;
		}
		else
		{
			serialPrintf("Invalid command format\n");
			return;
		}

	}

	GPIO_t tmpGPIO;
	bool_t tmpValue = FALSE;

	// Parse pin and port number
	if (eUndef != cmdMode)
	{
		int pin = 0;
		int port = 0;

		char tmpStr[10] = {0};
		strcpy(tmpStr, argv[2]);
		if ('P' == tmpStr[0])
		{
			if ('A' <= tmpStr[1] && tmpStr[1] <= 'E')
			{
				port = tmpStr[1] - 'A';
			}
			else
			{
				serialPrintf("\nInvalid port");
				return;
			}

			// Copy arg string without prefix 'PA'
			if (FALSE == getNumberFromString(&tmpStr[2], &pin))
			{
				serialPrintf("\nInvalid pin number");
				return;
			}
		}
		tmpGPIO.pin = pin;
		tmpGPIO.port = port;

		// Parse init value
		if (eInit == cmdMode)
		{
			if (0 == strcmp("IN", argv[3])){ tmpValue = FALSE;}
			else if (0 == strcmp("OUT", argv[3])){ tmpValue = TRUE;}
			else
			{
				serialPrintf("\nInvalid init mode");
				return;
			}
		}

		// Parse write value
		if (eWrite == cmdMode)
		{
			if ((0 == strcmp("FALSE", argv[3])) || (0 == strcmp("0", argv[3])))
			{
			    tmpValue = FALSE;
			}
			else if ((0 == strcmp("TRUE", argv[3])) || (0 == strcmp("1", argv[3])))
			{
			    tmpValue = TRUE;
			}
			else
			{
				serialPrintf("\nInvalid write value");
				return;
			}
		}

	}


	// If mode is undef, ask user
	if (eUndef == cmdMode)
	{
		char tmpString[100] = {0};

		serialPrintf("\nPin number:");
		cliGetInputString(tmpString, ARRAY_SIZE(tmpString));

		int pin  = 0;
		if (FALSE == getNumberFromString(tmpString, &pin))
		{
			serialPrintf("\nInvalid pin number");
			return;
		}

		serialPrintf("\nPort number:");
		cliGetInputString(tmpString, ARRAY_SIZE(tmpString));

		int port = 0;
		if (FALSE == getNumberFromString(tmpString, &port))
		{
			serialPrintf("\nInvalid port number");
			return;
		}

		tmpGPIO.pin = pin;
		tmpGPIO.port = port;

		serialPrintf("\nMode:");
		char * actionItems[] = {"Init", "Read", "Write"};
		int result = cliGetUserChoice(actionItems, ARRAY_SIZE(actionItems));

		switch(result)
		{
		case -1:
			serialPrintf("\nInvalid choice");
			return;

		case 0:
			cmdMode = eInit;

			// Select GPIO mode
			char * initItems[] = {"Input", "Output"};

			result = cliGetUserChoice(initItems, ARRAY_SIZE(initItems));
			if (-1 == result)
			{
				serialPrintf("\nInvalid choice");
				return;
			}

			if (0 != result)
			{
				tmpValue = TRUE;
			}
			break;

		case 1:
			cmdMode = eRead;
			break;

		case 2:
			cmdMode = eWrite;
			char * valueSelectItems[] = {"FALSE", "TRUE"};

			// Select GPIO mode
			result = cliGetUserChoice(valueSelectItems, ARRAY_SIZE(valueSelectItems));
			if (-1 == result)
			{
				serialPrintf("\nInvalid choice");
				return;
			}

			if (0 != result)
			{
				tmpValue = TRUE;
			}
			break;

		default:
			break;
		}

	}

	// Set proper mode
	switch(cmdMode)
	{
		case eInit:
		{
			// Default mode is input mode
			eGPIO_Mode pinMode = (FALSE == tmpValue) ? eGPIO_MODE_Input : eGPIO_MODE_OUTPUT_PP;
			gpioInit(&tmpGPIO, pinMode);
			break;
		}

		case eRead:
		{
			serialPrintf("\nGPIO read - port :%d, pin: %d\nState: ", tmpGPIO.port, tmpGPIO.pin);
			bool_t pinState = gpioGetState(&tmpGPIO);
			if (TRUE == pinState)
			{
				serialPrintf("TRUE");
			}
			else
			{
				serialPrintf("FALSE");
			}
			break;
		}

		case eWrite:
		{
			if (FALSE == tmpValue)
			{
				gpioReset(&tmpGPIO);
			}
			else
			{
				gpioSet(&tmpGPIO);
			}
			break;
		}
		default:
		{
		}
	}


}

void cmdGPIOInit(void)
{
	command_t tmp = (command_t) {"GPIO",  cmdGpioFunction, "Control GPIO", FALSE};
	cliRegisterCommand(&tmp);
}
