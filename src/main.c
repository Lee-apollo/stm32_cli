//#include "basic_commands.h"
//#include "serial.h"

#include <timer.h>
#include "global.h"
#include "cliModule.h"
#include "myStdlib.h"
#include "hwApi.h"
#include "timer.h"

#include "hwTimer.h"

int main(void)
{
	timer_start();
	hwInit();
	cliInit();

	serialPrintf("\nSTM32F4 Terminal v0.4\n>");

	char str[100];
	sprintf(str, "\nSystemCoreClock: %u\n", SystemCoreClock);

	serialPrintf(str);
	serialPrintf("\nSTM32F4 Terminal v0.4\n>");

	while(1)
	{
		cliGetUserCommand();
		// Process command
		cliProcessCommand();
		serialPrintf("\n>");
	}

	return 0;
}
