/*
 * circular_buffer_test.h
 *
 *  Created on: Oct 12, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_CIRCULAR_BUFFER_TEST_H_
#define INCLUDES_CIRCULAR_BUFFER_TEST_H_

#include "log.h"
#include "circular_buffer.h"

int test_buffer_full(uint8_t size_of_buffer, uint8_t additions_to_buffer);

int test_buffer_empty(uint8_t size_of_buffer, uint8_t additions_to_buffer,\
							uint8_t deletions_from_buffer);

int test_buffer_overflow(uint8_t size_of_buffer, uint8_t additions_to_buffer);

int test_empty_remove();


#endif /* INCLUDES_CIRCULAR_BUFFER_TEST_H_ */
