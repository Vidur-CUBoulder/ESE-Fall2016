#include "project_1.h"

//#define BYTE_8_MEMMOVE
//#define BYTE_16_MEMMOVE
//#define REVERSE_32

void project_1_report() {

    uint8_t array[32] = {0};

    uint8_t *aptr_1 = array;
    //printf("%p; %d\n", aptr_1, *aptr_1);

    uint8_t *aptr_2 = (array + 8);
    //printf("%p; %d\n", aptr_2, *aptr_2);
   
    uint8_t *aptr_3 = (array + 16); 
    //printf("%p; %d\n", aptr_3, *aptr_3);

    //Initialization operations...
    //1. Init from 0-15 to 31-46 
    int8_t cntr = 0;
    for(cntr = 0; cntr<16; cntr++) {
        *(aptr_1 + cntr) = (31 + cntr);
        //printf("addr: %p; data: %d\n", \
            (aptr_1 + cntr), *(aptr_1 + cntr)); 
    }

    //2. Init from aptr_3 to the end using memzero
    my_memzero((array + 16), (uint32_t)16); 

    //OPERATIONS!...
    //1. memmove to move 8 bytes from from aptr_1 to aptr_3
    
    #ifdef BYTE_8_MEMEMOVE

    int8_t i = 0;
    printf("(BEFORE)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }
    
    my_memmove(aptr_1, aptr_3, 8);

    //DEBUG..
    printf("(AFTER)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }

    #endif

    #ifdef BYTE_16_MEMMOVE

    //2. memmove to move 16 Bytes from aptr_2 to aptr_1
    int8_t i = 0;
    printf("(BEFORE)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }

    my_memmove(aptr_2, aptr_1, 16); 

    printf("(AFTER)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }

    #endif

    #ifdef REVERSE_32
    //3. my_reverse on the entire array..
    int8_t i = 0;
    printf("(BEFORE)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }

    my_reverse(array, 32);

    printf("(AFTER)Printing the entire array!\n");
    for(i=0; i<32; i++) {
        printf("Addr: %p; Data: %d\n", \
            (array+i), *(array+i));
    }

    #endif

}
