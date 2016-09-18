#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "headers.h"

/* Function : int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) 
 * Inputs:
 *      uint8_t *src : source data location pointer
 *      uint8_t *dst : destination data location pointer 
 *      uint32_t length: number of bytes that should be moved 
 *                       from the source to the location 
 * Output:
 *      returns a success/failure handle
 */ 
int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length);

/* Function : int8_t my_memzero(uint8_t *src, uint32_t length)  
 * Inputs:
 *      uint8_t *src : source data location pointer
 *      uint32_t length: number of bytes that should be
 *                       initialized to zero 
 * Output:
 *      returns a success/failure handle
 */ 
int8_t my_memzero(uint8_t *src, uint32_t length);

/* Function : int8_t my_memzero(uint8_t *src, uint32_t length)  
 * Inputs:
 *      uint8_t *src : source data location pointer
 *      uint32_t length: length of the string to be reversed 
 *   
 * Output:
 *      returns a success/failure handle
 */ 
int8_t my_reverse(uint8_t *src, uint8_t length);

#endif
