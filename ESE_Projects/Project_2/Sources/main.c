/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"

#ifdef BBB
#define MY_LOG() printf
#endif

int main(void)
{

#ifdef LOG_ENABLED

	char *data = "Testing123, Serial Print Test, no params\n";
	MY_LOG(data);

	MY_LOG_PARAMS("This is an integer number: ", 200);
	MY_LOG("\n");
	MY_LOG_PARAMS("This is an integer number: ", 4096);
	MY_LOG("\n");
	MY_LOG_PARAMS("This is an integer number: ", 123456);
	MY_LOG("\n");


	#ifdef ENABLE_FOR_FLOAT
		MY_LOG_FLOAT_PARAMS("This is a floating point number: ", 1543.321, 4);
	#endif

#endif

#ifdef BLINK_LED

	init_uart();
	config_receive();
	config_leds();

	int counter = 0;
	char input;
	int pulsewidth = 0;

	while(1) {

		while(!(UART0->S1 & 0x20)) {
		}
		input = UART0->D;

		if(input == 'd') {
			counter++;
		}
		else if(input == 'a'){
			counter--;
		} else {
			//Reset the counter
			counter = 0;
		}
		turn_on_leds(counter);

	}
#endif

#ifdef PWM_ADJUST

	/* Initialize the UART */
	init_uart();

	/* Config the UART to receive */
	config_receive();

	char input;
	uint16_t pulsewidth = 0;

	while(1) {

		while(!(UART0->S1 & 0x20)) {
		}
		input = UART0->D;

		if(input == 'w') {
			pulsewidth+=300;
		}
		else if(input == 's') {
				pulsewidth -= 300;
		} else {
			/* turn off the LED */
			pulsewidth = 0;
		}

#ifdef BLUE_LED
		init_PWM_Blue(pulsewidth);
#endif

#ifdef RED_LED
		init_PWM_Red(pulsewidth);
#endif

#ifdef GREEN_LED
		init_PWM_Green(pulsewidth);
#endif

}
#endif

#ifdef PROFILER

#ifdef FRDM_BUF

	double sys_clock = 0.047; // in microsecs
	double count, net_time;

	counter_init();

	struct buffer buf;
	int8_t data = 10;
	int8_t out = 0;

	start_counter();
	Init_Buffer(&buf, 10);
	stop_counter();
	count = TPM0_CNT;
	net_time = count * sys_clock;
	count = 0;
	net_time = 0;

	start_counter();
	Add_to_Buffer(&buf, &data);
	stop_counter();
	count = TPM0_CNT;
	net_time = count * sys_clock;
	count = 0;
	net_time = 0;

	start_counter();
	Remove_from_Buffer(&buf, &out);
	stop_counter();
	count = TPM0_CNT;
	net_time = count * sys_clock;
	count = 0;
	net_time = 0;

	start_counter();
	Free_Buffer(&buf);
	stop_counter();
	count = TPM0_CNT;
	net_time = count * sys_clock;
	count = 0;
	net_time = 0;

#endif


#ifdef FRDM
	/* HardSet the default system clock in micro seconds */
	double sys_clock = 0.047; // in microsecs
	double count, net_time;

	char *src = "Testing123, Serial Print Test, no params";
	counter_init();

	char *res = NULL;
	res = (char *)malloc(sizeof(char)*15);

	//Reset the counter register
	TPM0_CNT = 0x00000000;

	/* Profiling for custom function */
	start_counter();
	my_ftoa(123.524, res, 3);
	stop_counter();

	count = TPM0_CNT;

	net_time = count * sys_clock;

	free(res);
	free(src);
#endif

#ifdef BBB

	struct timeval before, after;

	gettimeofday(&before, NULL);

	MY_LOG("Hello There!\n");

	gettimeofday(&after, NULL);

	printf("Time Taken(microsecs): %lf\n", (double)time_diff(before, after));

#endif

#endif

//Circular Buffer Integration.

#ifdef CIRC_BUF_1

	uint8_t size = 3;
	/* This is the working function for circular buffer */
	LOG_BUFFER(size);

#endif

#ifdef TEST_CIRCULAR_BUFFER

	MY_LOG("Testing for Buffer Full!\n");
	test_buffer_full(5, 4);
	MY_LOG("Testing for Buffer Empty!\n");
	test_buffer_empty(5, 3, 4);
	MY_LOG("Testing for Buffer Overflow!\n");
	test_buffer_overflow(3, 4);
	MY_LOG("Testing for remove on empty buffer\n");
	test_empty_remove();

#endif


return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
