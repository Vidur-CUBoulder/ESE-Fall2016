#include "project_1.h"

void project_1_report() {

    uint8_t array[32] = {0};

    uint8_t *aptr_1 = array;
    
    //Initialization operations...
    //1. Init from 0-15 to 31-46 
    int8_t cntr = 0;
    for(cntr = 0; cntr<16; cntr++) {
        *(aptr_1 + cntr) = (31 + cntr);
    }

    //2. Init from aptr_3 to the end using memzero
    my_memzero((array + 16), (uint32_t)16); 

    //1. memmove to move 8 bytes from from aptr_1 to aptr_3
    
    uint8_t *aptr_3 = (array + 16); 

    my_memmove(aptr_1, aptr_3, 8);

    //2. memmove to move 16 Bytes from aptr_2 to aptr_1
   
    uint8_t *aptr_2 = (array + 8); 
    
    my_memmove(aptr_2, aptr_1, 16); 

    //3. my_reverse on the entire array..
    
    my_reverse(array, 32);

    dump_memory(array, 32);

}
