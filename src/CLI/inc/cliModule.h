/*
 * cliModule.h
 *
 *  Created on: 22. 9. 2015
 *      Author: z003jsvn
 */

#ifndef CLIMODULE_H_
#define CLIMODULE_H_

#include "global.h"


/* -------- Definitions START --------------- */
#define COMMANDS_COUNT 8
#define MAX_COMMAND_LEN 20
/* -------- Definitions END--------------- */

/* -------- Datatypes START --------------- */

typedef struct
{
	const char * name;
	void         (*function)(int argc, const char * argv[]);
	const char * info;
	bool_t       allocated;
} command_t;

/* -------- Datatypes END --------------- */

/* --------- External variables START --------*/
extern command_t cliCommands[COMMANDS_COUNT];
/* --------- External variables END ---------*/

/* -------- Function prototypes START--------------- */
void   cliInit(void);
void   cliProcessCommand(void);
bool_t cliRegisterCommand(command_t * cmdSetting);
int    cliGetUserChoice(char ** menuItems, int menuItemsLength);
void   cliGetUserCommand(void);
int    cliGetInputString(char * buffer, uint16_t bufferSize);

/* -------- Function prototypes END--------------- */

#endif /* CLIMODULE_H_ */
