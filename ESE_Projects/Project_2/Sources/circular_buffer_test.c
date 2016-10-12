/*
 * circular_buffer_test.c
 *
 *  Created on: Oct 12, 2016
 *      Author: vidur
 */

#include "circular_buffer_test.h"

int test_buffer_full(uint8_t size_of_buffer, uint8_t additions_to_buffer)
{
    	struct buffer buf;
    	uint8_t temp = 10;
    	uint8_t flag = 0;

    	Init_Buffer(&buf, size_of_buffer);

    	uint8_t i = 0;
    	for(i=0; i<additions_to_buffer; i++) {
    		if(Add_to_Buffer(&buf, &temp) == BUFFER_FULL){
    			flag = 1;
    			MY_LOG("The Buffer is FULL!\n");
    		}
    	}

    	if(flag && (additions_to_buffer > size_of_buffer)) {
    		MY_LOG("Test SUCCESSFUL!\n");
    	} else if ((additions_to_buffer < size_of_buffer) && !flag) {
    		MY_LOG("Test SUCCESSFUL!\n");
    	} else {
    		MY_LOG("Test FAILED!\n");
    	}

    	/* Need to Free the space before exiting */
    	Free_Buffer(&buf);

    	return 0;
}

int test_buffer_empty(uint8_t size_of_buffer, uint8_t additions_to_buffer,\
							uint8_t deletions_from_buffer)
{
	struct buffer buf;
	uint8_t data;
	uint8_t flag = 0;

	Init_Buffer(&buf, size_of_buffer);

	uint8_t i = 0;
	//MY_LOG("Testing for Buffer Full. This is just a safety check\n");
	test_buffer_full(size_of_buffer, additions_to_buffer);
	//MY_LOG("You are advised to check your parameters if the above test fails!\n");

	for(i=0; i<deletions_from_buffer; i++) {
		if(Remove_from_Buffer(&buf, &data) == BUFFER_EMPTY) {
			flag = 1;
			MY_LOG("Buffer EMPTY!\n");
		}
	}

	if ( flag && deletions_from_buffer > additions_to_buffer) {
		MY_LOG("Test SUCCESSFUL\n");
	} else if ((additions_to_buffer > deletions_from_buffer) && !flag) {
		MY_LOG("Test SUCCESSFUL!\n");
	} else {
		MY_LOG("Test FAILED!\n");
	}

	/* Need to Free the space before exiting */
	   Free_Buffer(&buf);

	 return 0;
}

int test_buffer_overflow(uint8_t size_of_buffer, uint8_t additions_to_buffer)
{
	struct buffer buf;

	Init_Buffer(&buf, size_of_buffer);

	uint8_t i = 0;
	uint8_t flag = 0;
	uint8_t temp = 10;

	for(i=0; i<additions_to_buffer; i++) {
		if(Add_to_Buffer(&buf, &temp) == BUFFER_FULL){
    			flag = 1;
    			MY_LOG("The Buffer is FULL!\n");
    	}
	}

	if(buf.buffer_start ==  buf.tail) {
		MY_LOG("Test SUCCESSFUL!\n");
	} else {
		MY_LOG("Test FAILED!\n");
	}

	/* Need to Free the space before exiting */
		Free_Buffer(&buf);

	return 0;
}

int test_empty_remove()
{
	struct buffer buf;
	uint8_t data;

	Init_Buffer(&buf, 4);

	if(Remove_from_Buffer(&buf, &data) == BUFFER_EMPTY) {
		MY_LOG("Test SUCCESSFUL!\n");
	} else {
		MY_LOG("Test FAILED!\n");
	}

	/* Need to Free the space before exiting */
	Free_Buffer(&buf);

	return 0;
}
