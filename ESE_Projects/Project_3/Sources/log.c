/*
 * log.c
 *
 *  Created on: Oct 26, 2016
 *      Author: vidur
 */

/* This function takes a pointer to data location and the length of the data
 * and prints the entire string onto the console.
 */

#include "log.h"

void MY_LOG(char *data)
{
	/* Initialize the UART */
	init_uart();

	/*Initialize the Transmit parameters */
	config_transmit();

	/* get the length of the passes string */
	int32_t length = strlen(data);

	while(1) {
		uint8_t i = 0;
		do {
		char ch = *(data+i);
		wait_for_buffer_empty();
		UART0_D = ch;
		i++;
		delay(10);
		} while(i != length);
		return;
	}

}

void MY_LOG_LEN(char *data, uint32_t length)
{
	/* Initialize the UART */
	init_uart();

	/*Initialize the Transmit parameters */
	config_transmit();

	while(1) {
		uint8_t i = 0;
		do {
		char ch = *(data+i);
		wait_for_buffer_empty();
		UART0_D = ch;
		i++;
		delay(10);
		} while(i != length);
		return;
	}

}


void MY_LOG_FLOAT_PARAMS(char*data, float param, int8_t precision)
{
	/* Init. the uart */
	init_uart();

	/*Init the transmit parameters */
	config_transmit();

	/*converting the param to ascii type */
	int8_t i = 0;
	int8_t length = strlen(data);

	int8_t *store_param = NULL;
	char ch;
	store_param = (int8_t *)malloc(sizeof(int8_t) * 20);

	my_ftoa(param, store_param, precision);
	uint8_t cnt = strlen(store_param);

	while(1) {
		i = 0;
		do {
			char ch = *(data+i);
			wait_for_buffer_empty();
			UART0->D = ch;
			i++;
			delay(50);
		} while(i != length);

		i = 0;
		do {
			ch = (char) *(store_param + i);
			wait_for_buffer_empty();
			UART0->D = ch;
			i++;
			delay(50);
		} while(i != cnt);

		free(store_param);
		return;
	}
}

void MY_LOG_PARAMS(char *data, uint32_t param)
{
	/* Init. the uart */
	init_uart();

	/*Init the transmit parameters */
	config_transmit();

	/*converting the param to ascii type */

	/*1. extract every digit in the param */
	int8_t i = 0;
	int8_t cnt = 0;
	int8_t length = strlen(data);
	int8_t *store_param = NULL;
	char ch;
	store_param = (int8_t *)malloc(sizeof(int8_t) * 20);

	while(param) {
		*(store_param+i) = param % 10;
		// convert to equiv. ASCII
		*(store_param + i) = *(store_param+ i) + 48;
		i++;
		cnt++;
		param = param/10;
	}

	// 2. Need to reverse the ASCII string
		my_reverse(store_param, cnt);

	/* 3. Dump on the terminal using UART */
	while(1) {
		i = 0;
		do {
			char ch = *(data+i);
			wait_for_buffer_empty();
			UART0->D = ch;
			i++;
			delay(20);
		} while(i != length);

		i = 0;
		do {
			ch = (char) *(store_param + i);
			wait_for_buffer_empty();
			UART0->D = ch;
			i++;
			delay(20);
		} while(i != cnt);

		free(store_param);
		return;
	}

}
