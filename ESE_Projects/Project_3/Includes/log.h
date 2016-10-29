/*
 * log.h
 *
 *  Created on: Oct 26, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_LOG_H_
#define INCLUDES_LOG_H_

#include "uart.h"
#include "ftoa.h"

void MY_LOG(char *data);

void LOG_BUFFER(uint8_t size);

void MY_LOG_PARAMS(char *data, uint32_t param);

void MY_LOG_FLOAT_PARAMS(char*data, float param, int8_t precision);

#endif /* INCLUDES_LOG_H_ */
