/*
 * circular_buffer.h
 *
 *  Created on: Oct 10, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_CIRCULAR_BUFFER_H_
#define INCLUDES_CIRCULAR_BUFFER_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

/* Struct that defines the attributes of the buffer */

struct buffer {
    void *buffer_start;
    void *buffer_end;
    void *head;
    void *tail;
    uint8_t num_elements;
    uint8_t size;
};

/* Enumerated types that defines the state of the Buffer */

enum Buffer_States {
    SUCCESS,     /* Operation returned successfully */
    NULL_VALUE,  /* Operation returned NULL values */
    BUFFER_FULL, /* Buffer state is FULL */
    BUFFER_EMPTY,/* Buffer is EMPTY */
    INVALID      /* This should not have happened!! */
};

/* Function: enum Buffer_States Init_Buffer(struct buffer *buf, uint8_t size)
 *
 * Parameters:
 * struct buffer *buf : pass the pointer to the start of the buffer.
 * uint 8_t size : the amount of contiguous memory blocks that you would like
 *        to allocate to the circular buffer.
 *
 * Return:
 *      An enum depending upon the failure/success of the operation.
 *
 * Description: to initialize the buffer given the starting memory pointer.
 *
 */
enum Buffer_States Init_Buffer(struct buffer *buf, uint8_t size);

/* Function:enum Buffer_States Buffer_Overflow(struct buffer *buf)
 *
 * Parameters:
 * struct buffer *buf : pass the pointer to the start of the buffer.
 *
 * Return:
 *      An enum depending upon the failure/success of the operation.
 *
 * Description: to check if there is an overflow in the buffer. If more
 *          data has been written to it than it can take.
 *
 */
enum Buffer_States Buffer_Overflow(struct buffer *buf);

/* Function:enum Buffer_States Add_to_Buffer(struct buffer *buf)
 *
 * Parameters:
 * struct buffer *buf : pass the pointer to the start of the buffer.
 *
 *
 * Return:
 *      An enum depending upon the failure/success of the operation.
 *
 * Description: to add an element to the buffer given its location.
 *
 */
enum Buffer_States Add_to_Buffer(struct buffer *buf, void *data);

/* Function:enum Buffer_States Buffer_Empty(struct buffer *buf)
 *
 * Parameters:
 * struct buffer *buf : pass the pointer to the start of the buffer.
 *
 * Return:
 *      An enum depending upon the failure/success of the operation.
 *
 * Description: to check if the buffer is empty or not.
 *
 */
enum Buffer_States Buffer_Empty(struct buffer *buf);

/* Function:enum Buffer_States Remove_from_Buffer(struct buffer *buf)
 *
 * Parameters:
 * struct buffer *buf : pass the pointer to the start of the buffer.
 *
 * Return:
 *      An enum depending upon the failure/success of the operation.
 *
 * Description: to remove an element from the buffer.
 *
 */
enum Buffer_States Remove_from_Buffer(struct buffer *buf, void *data);

enum Buffer_States Free_Buffer(struct buffer *buf);


#endif /* INCLUDES_CIRCULAR_BUFFER_H_ */
