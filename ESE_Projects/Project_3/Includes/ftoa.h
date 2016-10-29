/*
 * ftoa.h
 *
 *  Created on: Oct 12, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_FTOA_H_
#define INCLUDES_FTOA_H_

#include "memory.h"
#include "uart.h"
#include <math.h>

int intToStr(int x, char *str, int d);
void my_ftoa(float n, char *res, int afterpoint);

#endif /* INCLUDES_FTOA_H_ */
