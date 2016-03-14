/*
 * utils.c
 *
 *  Created on: 25. 9. 2015
 *      Author: z003jsvn
 */

#include "global.h"

#include "utils.h"

bool_t isNumber(char inputChar)
{
	bool_t retval = FALSE;
	if ('0' <= inputChar && inputChar <= '9')
	{
		retval = TRUE;
	}
	return retval;
}

int constrain(int input, int limitLow, int limitHigh)
{
	int output = input;
	output = MAX(output, limitLow);
	output = MIN(output, limitHigh);
	return output;
}

int scale(int input, int inputMin, int inputMax, int outputMin, int outputMax)
{
	int inputRange = inputMax - inputMin;
	int outputRange = outputMax - outputMin;

	int output = (((input - inputMin) * outputRange) / inputRange) + outputMin;
	return output;
}

bool_t getNumberFromString(const char * input, int * output)
{
	if (NULL == input || NULL == output)
	{
		return FALSE;
	}

	int length = strlen(input);
	if (0 ==length)
	{
		return FALSE;
	}

	int number = 0;
	bool_t isValidNumber = TRUE;

	for (int i = 0; i < length; i++)
	{
		if ((FALSE == isNumber(input[i])) &&
			('-' != input[i]))
		{
			isValidNumber = FALSE;
			break;
		}
	}

	if (TRUE == isValidNumber)
	{
		number = myAtoi(input);
	}
	*output = number;

	return isValidNumber;
}

void _delayOneMs(void)
{
	int test = 0;
	for (int i = 0; i < 10000; i++)
	{
		test++;
	}
}

/*void delayMs(int count)
{
	for(int i = 0; i < count; i++)
	{
		_delayOneMs();
	}
}*/
