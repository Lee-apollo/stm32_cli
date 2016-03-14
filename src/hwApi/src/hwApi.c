/*
 * hwApi.c
 *
 *  Created on: 30. 9. 2015
 *      Author: z003jsvn
 */

#include "serial.h"
#include "hwGPIO.h"
#include "hwServo.h"
#include "myStdlib.h"

void hwInit(void)
{
	serialInit();
	servoInit();
	return;
}

void hwExit(void)
{
	serialPrintf("\nReboot");
	return;
}
