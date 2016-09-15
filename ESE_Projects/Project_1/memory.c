#include "memory.h"

/*
int main() {

    uint8_t arr_1[] = { 'h', 'e', 'l', 'l', 'o', ' ', 't', 'h', 'e', 'r', 'e', '\0' };
    uint8_t len = 11;

    int8_t res = 0;

    printf("(PRE) %d %d %d %d %d\n", arr_1[0], \
            arr_1[1], arr_1[2], arr_1[3], arr_1[4]);
    
    res = my_reverse(arr_1, 11);

    printf("(PRE) %d %d %d %d %d\n", arr_1[0], \
            arr_1[1], arr_1[2], arr_1[3], arr_1[4]);


    return 0;
}
*/

int8_t my_reverse(int8_t *src, uint8_t length)
{
	int8_t *string_start = src; 

	/* Adding checks for corner cases */
	if ( length <= 0) {
		return -1;
	}

	if ( src == NULL ) {
		return -1;
	}

	int8_t rev_iter = 0;
	int8_t temp = 0;
        
        for(rev_iter=0; rev_iter<((length/2)); rev_iter++) {	
            temp = *(string_start + rev_iter);
            *(string_start + rev_iter) = \
                *(string_start + (length-1) - rev_iter);
            *(string_start + (length-1) - rev_iter) = temp;
        }

	printf("\n");

	return 0;
}

int8_t my_memzero(uint8_t *src, uint32_t length) {

    if (src == NULL) {
        return -1;
    }

    int i = 0;
    for( i = 0; i<length; i++) {
        *(src+i) = 0x0;
        //printf("Addr: %p; data: %d\n", \
            (src+i), *(src+i));
    }

    return 0;
}

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) {

    if ( src == NULL || dst == NULL ) {
        return -1;
    }

    int i = 0;
    for (i = 0; i<length; i++) {
        /* Return if there is a mem overlap */
        if((src+i) == (dst+i)) {
            return -1;
        }

        *(dst+i) = *(src+i);
    }

    return 0;
}

