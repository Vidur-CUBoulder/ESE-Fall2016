#ifndef _DATA_H_
#define _DATA_H_

#include "headers.h"

/* Function : void dump_memory(uint8_t *start, uint32_t length)
 * Inputs:
 *      uint8_t *start : starting address from which the data should
 *               be dumped.
 *      uint32_t length: point to which the memory should be read.
 * Output:
 *      prints the memory dump.
 */ 
void dump_memory(uint8_t *start, uint32_t length);

/* Function : void my_atoi(uint8_t *str)
 * Inputs:
 *      uint8_t *str : string that has to be converted into an int.
 * Output:
 *      prints the integer 
 */ 
int32_t my_atoi(uint8_t *str);

/* Function : void my_atoi(uint8_t *str)
 * Inputs:
 *      uint8_t *str : string to hold the ASCII data.
 *      int32_t data : data to be converted to ASCII.
 *      int32_t base : the kind of ASCII to be converted to
 *                      hex, binary, decimal or octal
 * Output:
 *      returns the ASCII string to the caller.
 */ 
int8_t *my_itoa(int8_t *str, int32_t data, int32_t base); 

/* Function : void my_atoi(uint8_t *str)
 * Inputs:
 *      int32_t data : data to convert to little endian.
 * Output:
 *      returns the data after converting to little endian.
 */ 
int32_t big_to_little(int32_t data);

/* Function : void my_atoi(uint8_t *str)
 * Inputs:
 *      int32_t data : data to convert to big endian.
 * Output:
 *      returns the data after converting to big endian.
 */ 
int32_t little_to_big(int32_t data);

#endif
