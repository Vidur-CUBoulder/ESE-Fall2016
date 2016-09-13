/*
 * TODO : Change the main() function. Or best, remove it
 * completely ?
 */ 

#include "data.h"

int main()
{
    int32_t data = 0x23;
    int32_t res = 0;

    res = big_to_little(data);
    printf("%x\n", res); 
    
    return 0;

}

int8_t *my_itoa(int8_t *str, int32_t data, int32_t base)
{
    if(str == NULL) {
        return "Null String";
    }

    int8_t sign = 0;
    int8_t temp_cnt = 0;

    /* Need to convert the number to a positive one \
       irrespective. We will handle the negative binaries \
       after we have obtained the binary number 
    */
    if(data < 0) {
        sign = 1;
        data = data * (-1);
    }

    int8_t cnt = 0;
    while(data != 0) {
       *(str+cnt) = data % 2;
        data = data / 2;
        cnt++;
    }
    
    cnt--;
    temp_cnt = cnt; 
    uint8_t i = 0; uint8_t temp = 0;
    for(i=0; i<=((cnt/2)+1); i++) {
        temp = *(str+i);
        *(str+i) = *(str+cnt);
        *(str+cnt) = temp;
        cnt--;
    }

    if( sign == 1 ) {
        for(i=0; i<=temp_cnt; i++) {
            *(str+cnt) = ~(*(str+cnt));
            printf("%d ", *(str+cnt)); 
        } //end of the inverse ops.
    
    }

    printf("\n");

    return str;
}


int32_t big_to_little(int32_t data)
{
    return (((data >> 24) & 0xff) | ((data << 8) & 0xff0000) | ((data >> 8) & 0xff00) | ((data << 24) & 0xff000000) );
}

int32_t little_to_big(int32_t data)
{
    printf("%x\n", data);

    int32_t tmp = 0;

    //return (((data << 24) & 0xff000000) | ((data << 8) & 0xff0000) | ((data >> 8) & 0xff00) | ((data >> 24) & 0xff) );
    printf("%x\n",(((data >> 24) & 0xff) | ((data << 8) & 0xff0000) | ((data >> 8) & 0xff00) | ((data << 24) & 0xff000000) ));

}

void dump_memory(uint8_t *start, uint32_t length)
{
    if(start == NULL) {
        return;
    }

    uint8_t i = 0;
    while (i != length) {
        printf("%p; 0x%.2x\n", (start+i), *(start+i));
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
    int sign = 1;
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
    for(i=(cntr-1); i>0; i--) {
        temp = temp + ((*(str+i) - '0') * pow);
        pow = pow * 10;
    }

    //Assigning the sign of the integer.
    temp = temp * sign;

    return temp;
}
    



