
#include "data.h"
#include "stdlib.h"

int8_t *my_itoa(int8_t *str, int32_t data, int32_t base)
{
    if(str == NULL && (base != 2 || base != 8 || base != 16) ) {
        return NULL;
    }

    int8_t sign = 0;
    int8_t temp_cnt = 0;
    int8_t cnt = 0;
    uint8_t i = 0; uint8_t temp = 0;

    /* Need to convert the number to a positive one \
       irrespective. We will handle the negative binaries \
       after we have obtained the binary number
     */
    if(data < 0) {
        sign = 1;
        data = data * (-1);
    }

    while(data != 0) {
        *(str+cnt) = data % base;
        data = data / base;
        cnt++;
    }

    cnt--;
    temp_cnt = cnt;

    for(i=0; i<=((cnt/2)); i++) {
        temp = *(str+i);
        *(str+i) = *(str+cnt);
        *(str+cnt) = temp;
        cnt--;
    }

    /* 2's Complement for Signed Numbers!(Only Binary) */
    if( (sign == 1) && (base == 2) ) {
        for(i=0; i<=(temp_cnt); i++) {
            (*(str+i) == 1) ? (*(str+i) = 0) : (*(str+i) = 1);
        } //end of the inverse ops.

        int8_t flip = 0;

        /* Adding 1 to the 1's complement now */
        for(i=temp_cnt; i>=0; i--) {
            if(*(str+i) == 1) {
                flip = 1;
                if( *(str+i+1) == 0 && flip == 1) {
                    *(str+i+1) = 1;
                    flip = 0;
                    break;
                } else {
                    continue;
                }
            } else {
                (*(str+i)) = 1;
                break;
            }
        }
    }

    return str;
}


int32_t big_to_little(int32_t data)
{
    int32_t a = ((data << 24) & 0xff000000);
    int32_t b = ((data << 8) & 0xff0000);
    int32_t c =((data >> 8) & 0xff00);
    int32_t d =((data >> 24) & 0xff);

    return (a | b | c | d) ;
}

int32_t little_to_big(int32_t data)
{
    int32_t a = ((data << 24) & 0xff000000);
    int32_t b = ((data << 8) & 0xff0000);
    int32_t c =((data >> 8) & 0xff00);
    int32_t d =((data >> 24) & 0xff);

    return (a | b | c | d) ;
}

void dump_memory(uint8_t *start, uint32_t length)
{
    if(start == NULL) {
        return;
    }

    uint8_t i = 0;
    while (i != length) {
        //printf("Addr.: %p; Value: 0x%.2x\n", (start+i), *(start+i));
        i++;
    }

    return;

}

int32_t my_atoi(uint8_t *str)
{
    if(str == NULL) {
        return -1;
    }

    uint8_t cntr = 0;
    int8_t sign = 1;
    uint32_t temp = 0;

    if (*str == '-') {
        cntr = 1;
        sign = -1;
    }

    //Determining the length of the array.
    while (*(str+cntr) != '\0') {
        cntr++;
    }

    int i= 0; int pow = 1;
    for(i=(cntr-1); i>=0; i--) {
        temp = temp + ((*(str+i) - '0') * pow);
        pow = pow * 10;
    }

    //Assigning the sign of the integer.
    temp = temp * sign;

    return temp;
}





