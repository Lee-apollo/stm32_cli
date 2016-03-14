/*
 * main.c
 *
 *  Created on: 2. 10. 2015
 *      Author: z003jsvn
 */

#include <stdarg.h>
#include "myStdlib.h"

// Printf output callback function
void (*stdlibPrintfOutputCB)(char) = NULL;

// Getchar output callback function
char (*stdlibGetCharCB)(void) = NULL;

enum eNumberFormat
{
	eFormatDEC,
	eFormatHEX,
	eFormatOCT,
	eFormatBIN
};

/* -------- PRIVATE ------------------------ */

static bool_t _isNumber(char inputChar, enum eNumberFormat numberFormat)
{
	bool_t retval = FALSE;
	switch (numberFormat)
	{
	case eFormatDEC:
		retval = isNumberDec(inputChar);
		break;

	case eFormatHEX:
		retval = isNumberHex(inputChar);
		break;

	case eFormatOCT:
		retval = isNumberOct(inputChar);
		break;

	case eFormatBIN:
		retval = isNumberBin(inputChar);
		break;

	default:
		retval = FALSE;
		break;
	}
	return retval;
}


/* -------- PUBLIC------------------------ */

bool_t isNumberDec(char inputChar)
{
	return ('0' <= inputChar && inputChar <= '9') ? TRUE : FALSE;
}

bool_t isNumberOct(char inputChar)
{
	return ('0' <= inputChar && inputChar <= '7') ? TRUE : FALSE;
}

bool_t isNumberBin(char inputChar)
{
	return ('0' <= inputChar && inputChar <= '1') ? TRUE : FALSE;
}

bool_t isNumberHex(char inputChar)
{
	return ((TRUE == isNumberDec(inputChar)) ||
			('a' <= inputChar && inputChar <= 'f') ||
			('A' <= inputChar && inputChar <= 'F')) ?
			TRUE :
			FALSE;
}

bool_t isChar(char inputChar)
{
	return (('a' <= inputChar && inputChar <= 'z') || ('A' <= inputChar && inputChar <= 'Z')) ? TRUE : FALSE;
}

bool_t isSpace(char inputChar)
{
	return (' ' == inputChar) ? TRUE : FALSE;
}

char numToChar(int num)
{
	char retval = '\0';
	if (0 <= num && num <= 9)
	{
		retval = num + '0';
	}
	else if (10 <= num && num <= 15)
	{
		retval = num -10 + 'A';
	}

	return retval;
}

int charToNum(char inputChar)
{
	int value = 0;

	if (TRUE == isNumberDec(inputChar))
	{
		value = inputChar - '0';
	}
	else if (TRUE == isNumberHex(inputChar))
	{
		inputChar = TO_UPPER(inputChar);
		value = inputChar - 'A' + 10;
	}
	return value;
}

int myAtoi (const char * str)
{
	int value = 0;
	int base = 10; // Default number base is 10

	enum eNumberFormat numberFormat = eFormatDEC;

	bool_t isNegative = FALSE;

	while(TRUE == isSpace(*str))
	{
		str++;
	}

	if (*str == '-')
	{
		isNegative = TRUE;
		str++;
	}

	if(*str == '0')
	{
		str++;
		char c = TO_UPPER(*str);
		switch(c)
		{
		case 'X':
			numberFormat = eFormatHEX;
			base = 16;
			str++;
			break;

		case 'B':
			numberFormat = eFormatBIN;
			base = 2;
			str++;
			break;

		default:
			numberFormat = eFormatOCT;
			base = 8;
			break;
		}
	}

	while(*str != '\0')
	{
		char c = *str++;

		if (TRUE == _isNumber(c, numberFormat))
		{
			value *= base;
			int part = charToNum(c);
			value += part;
		}
		else
		{
			value = 0;
			break;
		}
	}

	if (TRUE == isNegative)
	{
		value *= -1;
	}

	return value;
}

char * myItoa (int value, char * str, int base)
{
	if (( 1 >= base) || NULL == str)
	{
		return NULL;
	}

	int isNegative = (value < 0) ? 1 : 0;
	value = abs(value);

	int length = isNegative; // Add space for minus character
	int number = 0;

	// Get number of digits, 0 has 1 digit
	number = value;
	do
	{
		number = number / base;
		length++;
	} while(number != 0);

	int charIdx = length - 1;

	do{
		number = value % base;
		value = value / base;
		str[charIdx--] = numToChar(number);
	} while(value != 0);

	if (isNegative == 1)
	{
		str[0] = '-';
	}

	str[length] = '\0';
	return str;
}

int parseString(void (*outputCallback)(char), const char *str, va_list args)
{
	const char * ptr = str;

	while(*ptr != '\0')
	{
		char c = *ptr++;

		if (c == '%')
		{
			c = *ptr++;
			switch(c)
			{
				case 'd':
				{
					int i = va_arg(args, int);
					char tmpString[MAX_INT_DIGIT_COUNT];

					char * tmpPtr = myItoa(i, tmpString, 10);
					while(*tmpPtr != '\0')
					{
						outputCallback(*tmpPtr++);
					}
					break;
				}

				case 's':
				{
					char * argString = va_arg(args, char *);
					char * tmpPtr = argString;

					while(*tmpPtr != '\0')
					{
						outputCallback(*tmpPtr++);
					}
					break;
				}

				default:
				{
					break;
				}
			}
		}
		else
		{
			outputCallback(c);
		}
	}
	return 1;
}

char myGetchar(void)
{
	if (stdlibGetCharCB == NULL)
	{
		return '\0';
	}
	return stdlibGetCharCB();
}

int serialPrintf(const char *str, ...)
{
  if (stdlibPrintfOutputCB == NULL)
  {
	  return 0;
  }

  va_list args;
  va_start(args, str);
  int retval = parseString(stdlibPrintfOutputCB, str, args);
  va_end(args);
  return retval;
}
