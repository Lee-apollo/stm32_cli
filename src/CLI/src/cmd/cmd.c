/*
 * basic_commands.c
 *
 *  Created on: 22. 9. 2015
 *      Author: z003jsvn
 */


#include "global.h"
#include "cmd.h"
#include "cliModule.h"
#include "serial.h"
#include "utils.h"

// Include all commands
#include "cmdSystem.h"
#include "cmdGPIO.h"

void cmdInit(void)
{
	cmdSystemInit();
	cmdGPIOInit();
}

/*typedef enum
{
  eTypeInt,
  eTypeString,
  eTypeStepper,
  eTypeNotUsed
} eVariableType_t;

typedef struct
{
	eVariableType_t type;
	char name[10];
	union
	{
		char string[10];
		int32_t number;
	};
} termVariable_t;

termVariable_t termVariables[10];

*/

/*
void printVariable(termVariable_t * variable)
{
	serialPutString("\nName: ");
	serialPutString(variable->name);
	serialPutString("\nType: ");

	switch(variable->type)
	{
		case eTypeInt:
			serialPutString("int");
			break;

		case eTypeString:
			serialPutString("string");
			break;

		case eTypeStepper:
			serialPutString("stepper");
			break;

		case eTypeNotUsed:
			serialPutString("NOT USED");
			break;
		default:
			break;
		}
}

void cmdListFunction(int argc, const char * argv[])
{
	for (int i = 0; i < ARRAY_SIZE(termVariables); i++)
	{
		printVariable(&termVariables[i]);
	}
	return;
}
*/
