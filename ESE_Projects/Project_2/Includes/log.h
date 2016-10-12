/* Header file for log.c */

#include "uart.h"
#include "circular_buffer.h"
#include "ftoa.h"

void MY_LOG(char *data);

void LOG_BUFFER(uint8_t size);

void MY_LOG_PARAMS(char *data, uint32_t param);

void MY_LOG_FLOAT_PARAMS(char*data, float param, int8_t precision);

