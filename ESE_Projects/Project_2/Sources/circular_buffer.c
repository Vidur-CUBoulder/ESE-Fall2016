/*
 * circular_buffer.c
 *
 *  Created on: Oct 10, 2016
 *      Author: vidur
 */

#include "circular_buffer.h"

enum Buffer_States Init_Buffer(struct buffer *buf, uint8_t size)
{
    buf->buffer_start = (struct buffer *)malloc(sizeof(uint8_t) * size);
    buf->buffer_end = buf->buffer_start + (sizeof(uint8_t) * (size-1));
    buf->size = size;
    buf->head = buf->tail = buf->buffer_start;
    buf->num_elements = 0;

    return SUCCESS;
}

enum Buffer_States Free_Buffer(struct buffer *buf)
{
    free(buf->buffer_start);

    return SUCCESS;
}

enum Buffer_States Buffer_Overflow(struct buffer *buf)
{
    if (buf == NULL) {
        return NULL_VALUE;
    }

    if ( (buf->tail > buf->buffer_end) ) {
        printf("Overflow!\n");
        buf->tail = buf->buffer_start;

        return SUCCESS;
    }

    return INVALID;
}

enum Buffer_States Add_to_Buffer(struct buffer *buf, void *data)
{
    if (buf == NULL) {
        return NULL_VALUE;
    }

    if (Buffer_Overflow(buf) == SUCCESS) {
        return BUFFER_FULL;
    }

    memcpy(buf->tail, data, sizeof(uint8_t));
    buf->tail = buf->tail + sizeof(uint8_t);
    ++(buf->num_elements);

    return SUCCESS;
}

enum Buffer_States Buffer_Empty(struct buffer *buf)
{
    if(buf == NULL) {
        return NULL_VALUE;
    }

    if ( (buf->head == buf->tail) && (buf->num_elements == 0) ) {
        printf("Empty!\n");

        return SUCCESS;
    }
}

enum Buffer_States Remove_from_Buffer(struct buffer *buf, void *data)
{
    if(buf == NULL) {
        return NULL_VALUE;
    }

    if( Buffer_Empty(buf) == SUCCESS ) {
        return BUFFER_EMPTY;
    }

    memcpy(data, buf->head, sizeof(uint8_t));
    buf->head = buf->head + sizeof(uint8_t);
    --(buf->num_elements);

    return SUCCESS;
}

enum Buffer_States Print_Buffer(struct buffer *buf)
{
    if(buf == NULL) {
        return NULL_VALUE;
    }

    struct buffer *temp_buf = NULL;
    temp_buf = buf;

    int8_t data;
    int8_t i = 0;
    for(i=0; i<4; i++) {
        memcpy(&data, temp_buf->head, sizeof(uint8_t));
        printf("data: %d\n", data);
        temp_buf->head = temp_buf->head + sizeof(uint8_t);
    }

    return SUCCESS;
}
