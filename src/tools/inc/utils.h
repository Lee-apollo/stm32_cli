/*
 * utils.h
 *
 *  Created on: 25. 9. 2015
 *      Author: z003jsvn
 */

#ifndef UTILS_H_
#define UTILS_H_

int constrain(int input, int limitLow, int limitHigh);

int scale(int input, int inputMin, int inputMax, int outputMin, int outputMax);

bool_t getNumberFromString(const char * input, int * output);

void delayMs(int count);

#endif /* UTILS_H_ */
