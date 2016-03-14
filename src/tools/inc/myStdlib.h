/*
 * myStdlib.h
 *
 *  Created on: 2. 10. 2015
 *      Author: z003jsvn
 */

#ifndef MYSTDLIB_H_
#define MYSTDLIB_H_

#include <stdarg.h>

#define NULL ((void *)0)

#define MAX_INT_DIGIT_COUNT 20

extern void (*stdlibPrintfOutputCB)(char);
extern char (*stdlibGetCharCB)(void);


#define abs(x) (((x) < 0) ? (-x) : (x))
#define TO_UPPER(x) (((x) >= 'a') && ((x) <= 'z')) ? ((x) + 'A' - 'a') : (x)

typedef enum
{
	FALSE = 0,
	TRUE
} bool_t;

bool_t isNumberDec(char inputChar);
bool_t isNumberHex(char inputChar);
bool_t isNumberOct(char inputChar);
bool_t isNumberBin(char inputChar);

bool_t isChar(char inputChar);

bool_t isSpace(char inputChar);

char numToChar(int num);

int charToNum(char inputChar);

int myAtoi (const char * str);

char * myItoa (int value, char * str, int base);

int serialPrintf(const char *str, ...);

char myGetchar(void);

#endif /* MYSTDLIB_H_ */
