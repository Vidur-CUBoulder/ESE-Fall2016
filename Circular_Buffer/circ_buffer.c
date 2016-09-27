#include "circ_buffer.h"

enum Buffer_States Init_Buffer(struct buffer *buf, uint8_t size)
{
    buf->buffer_start = (struct buffer *)malloc(sizeof(uint8_t) * size);
    buf->buffer_end = buf->buffer_start + (sizeof(uint8_t) * (size-1));
    buf->size = size;
    buf->head = buf->tail = buf->buffer_start;
    buf->num_elements = 0;

    return SUCCESS;
}

enum Buffer_States Buffer_Overflow(struct buffer *buf)
{
    if (buf == NULL) {
        return NULL_VALUE;
    }

    if (buf->tail > buf->buffer_end) {
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

int main()
{
    struct buffer buf;
    uint8_t temp_1 = 10;
    uint8_t temp_2 = 20;
    uint8_t temp_3 = 30;
    uint8_t out = 0;

    Init_Buffer(&buf, 4);

    Add_to_Buffer(&buf, &temp_1);
    Add_to_Buffer(&buf, &temp_2);
    Add_to_Buffer(&buf, &temp_3);
    Add_to_Buffer(&buf, &temp_3);
    Add_to_Buffer(&buf, &temp_3);
    
    Remove_from_Buffer(&buf, &out);
    printf("%d\n", out);
    Remove_from_Buffer(&buf, &out);
    printf("%d\n", out);
    Remove_from_Buffer(&buf, &out);
    printf("%d\n", out);
    Remove_from_Buffer(&buf, &out);

    return 0;
}




