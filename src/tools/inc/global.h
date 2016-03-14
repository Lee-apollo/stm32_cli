/*
 * global.h
 *
 *  Created on: 22. 9. 2015
 *      Author: z003jsvn
 */

#ifndef MY_GLOBAL_H_
#define MY_GLOBAL_H_

//#include <stdio.h>
#include "myStdlib.h"
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
//#include <assert.h>



#define UNDEF_U8  (uint8_t)-1
#define UNDEF_U16 (uint16_t)-1
#define UNDEF_U32 (uint32_t)-1

#define UNUSED(x) (void)(x)

#define assert(x) UNUSED(x)

#define MIN(x,y) ((x) < (y)) ? (x) : (y)
#define MAX(x,y) ((x) > (y)) ? (x) : (y)

#define ARRAY_SIZE(x) (sizeof((x))/sizeof((x)[0]))

#define TO_UPPER(x) (((x) >= 'a') && ((x) <= 'z')) ? ((x) + 'A' - 'a') : (x)

#endif /* MY_GLOBAL_H_ */
