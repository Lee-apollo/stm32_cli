/*
 * systemCommands.c
 *
 *  Created on: 30. 9. 2015
 *      Author: z003jsvn
 */

#include "cmd.h"
#include "global.h"
#include "serial.h"
#include "utils.h"
#include "hwApi.h"


//TODO Lepe poresit zavislost mezi CLI commandem pro servo a hwServo - mozna pridat pres hwApi
#include "hwServo.h"

void cmdExitFunction(int argc, const char * argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	// TODO add real reboot
	//serialPrintf("\nExit - reboot\n");
	hwExit();
}

void cmdHelpFunction(int argc, const char * argv[])
{
	bool_t commandFound = FALSE;

	if (argc > 1)
	{
		for(int idx = 0; (cliCommands[idx].name != NULL && cliCommands[idx].function != NULL); idx++)
		{
			if (0 == strcmp(cliCommands[idx].name, argv[1]))
			{
				serialPrintf("\n%s - %s", cliCommands[idx].name, cliCommands[idx].info);
				commandFound = TRUE;
			}
		}
	}

	if (commandFound == FALSE)
	{
		//serialPutString("\nHelp function v0.1");
		if (NULL != argv[1])
		{
			serialPrintf("\nUnknown command - '%s'", argv[1]);
		}

		serialPrintf("\nAvailable commands:");

		for(int idx = 0; (cliCommands[idx].name != NULL && cliCommands[idx].function != NULL); idx++)
		{
			serialPrintf("\n%s - %s", cliCommands[idx].name, cliCommands[idx].info);
		}
	}
}


void cmdServoFunction(int argc, const char * argv[])
{
    if (argc !=  3)
    {
        serialPrintf("\nUsage: SRV channel angle(0-180)");
    }
    else
    {
        int servoChannel = atoi(argv[1]);
        int servoAngle = atoi(argv[2]);

        serialPrintf("\nServo channel: %d, angle: %d", servoChannel, servoAngle);
        servoSetPosition(servoAngle,  servoChannel);
    }
}


void cmdSystemInit(void)
{
	command_t tmp = (command_t) {"EXIT", cmdExitFunction, "Exit terminal", FALSE};
	cliRegisterCommand(&tmp);

	tmp = (command_t) {"HELP", cmdHelpFunction, "Shows basic help for commands", FALSE};
	cliRegisterCommand(&tmp);

    tmp = (command_t) {"SRV", cmdServoFunction, "Servo - SRV channel angle", FALSE};
    cliRegisterCommand(&tmp);

}
