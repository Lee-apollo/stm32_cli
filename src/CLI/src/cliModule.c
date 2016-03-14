/*
 * cliModule.c
 *
 *  Created on: 22. 9. 2015
 *      Author: z003jsvn
 */

#include "global.h"
#include "cliModule.h"
#include "cmd.h"
//#include "myStdlib.h"
#include "utils.h"
#include "serial.h"
#include <string.h>

static char commandBuffer [MAX_COMMAND_LEN + 1];

command_t cliCommands[COMMANDS_COUNT];

void cliProcessCommand()
{
	int argc = 0;
	const char * argv[10];

	char * token = strtok(commandBuffer, " ");
	int idx = 0;
	argv[idx++] = token;

	while(token != NULL)
	{
		token = strtok(NULL, " ");
		argv[idx++] = token;
	}

	argc = idx - 1;

	// Check for empty ENTER press
	if (NULL == argv[0])
	{
		return;
	}

	int result = -1;
	bool_t commandFound = FALSE;
	for(int idx = 0; idx < COMMANDS_COUNT; idx++)
	{
		if (cliCommands[idx].name == NULL || cliCommands[idx].function == NULL)
		{
			break;
		}
		result = strcmp(argv[0], cliCommands[idx].name);

		// result = 0 if both strings are equal
		if (result == 0)
		{
			cliCommands[idx].function(argc, argv);
			commandFound = TRUE;
		}
	}

	if (commandFound == FALSE)
	{
		serialPrintf("\nUnknown command - '%s'", argv[0]);
	}
}

bool_t cliRegisterCommand(command_t * newCmd)
{
	bool_t retval = FALSE;

	if (newCmd == NULL)
	{
		return FALSE;
	}

	if (newCmd->function == NULL || newCmd->name == NULL || newCmd->info == NULL)
	{
		return FALSE;
	}

	for(int idx = 0; idx < COMMANDS_COUNT; idx++)
	{
		if (cliCommands[idx].allocated == FALSE)
		{
			cliCommands[idx] = *newCmd;
			cliCommands[idx].allocated = TRUE;
			retval = TRUE;
			break;
		}
	}

	return retval;
}

int cliGetInputString(char * buffer, uint16_t bufferSize)
{
	uint16_t charIdx = 0;

	while(1)
	{
		if (charIdx > bufferSize - 1)
		{
			charIdx = 0;
			break;
		}

		char inputChar = myGetchar();

		if ((inputChar == '\r') || (inputChar == '\n'))
		{
			break;
		};

		//TODO replace with serialPrintf
		serialPutChar(inputChar);
		//serialPrintf("%c", inputChar);
		buffer[charIdx] = TO_UPPER(inputChar);
		charIdx++;
	}
	buffer[charIdx] = '\0';

	return (int)charIdx;
}

void cliGetUserCommand(void)
{
	cliGetInputString(commandBuffer, ARRAY_SIZE(commandBuffer));
}

int cliGetUserChoice(char ** menuItems, int menuItemsLength)
{
	bool_t resultFound = FALSE;

	int selectedItem = 0;

	char tmpBuffer[20] = {0};

	while(resultFound == FALSE)
	{
		serialPrintf("\nSelect:");
		for (int i = 0; i < menuItemsLength; i++)
		{
			serialPrintf("\n%d.%s", i+1, menuItems[i]);
		}

		serialPrintf("\nInput:");
		cliGetInputString(tmpBuffer, ARRAY_SIZE(tmpBuffer));
		serialPrintf("\n");

		// Control-C character
		if ('\x03' == tmpBuffer[0])
		{
			return -1;
		}

		if (FALSE == getNumberFromString(tmpBuffer, &selectedItem))
		{
			continue;
		}

		if (selectedItem > 0 && selectedItem <= menuItemsLength)
		{
			resultFound = TRUE;
		}
	}
	// convert selectedItem to item index
	return selectedItem - 1;
}


void cliInit(void)
{
	memset(cliCommands, 0, sizeof(cliCommands));

	cmdInit();
}
