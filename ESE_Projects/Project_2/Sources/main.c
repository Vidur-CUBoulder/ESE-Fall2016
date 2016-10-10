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

/* Setting the Global Clock Configurations to pre-defined values
 * Please refer to system_MKL25Z4.h for more information on this.*/
//#define CLOCK_SETUP 1

#define BLINK_LED

int main(void)
{

#ifdef TRIAL_SNIPPET
	init_uart();
	config_transmit();

	while(1) {
		wait_for_buffer_empty();
		UART0_D = 'Y';
		int i = 0;
		int j = 0;
		for(i=0; i<2; i++){
			for(j=0; j<7000; j++) {
				/*delay*/
			}
		}
		//disable_Tx_Rx();
	}
#endif

#ifdef LOG_ENABLED

	char *data = "Testing123, Serial Print Test, no params";

	MY_LOG(data, strlen(data));

#endif

#ifdef BLINK_LED

	__disable_irq();

	init_uart();
	config_receive();

	config_leds();

	__enable_irq();

	int counter = 0;
	char input;

	while(1) {
		/* Read from the console */
		//while( (UART0_S1 | 0x20) == 0xE0 ) {
			//delay(10);
			input = UART0_D;
		//}

		if(input == 'd') {
			counter++;
		}
		else if(input == 'a'){
			counter--;
		} else {
			/* Reset the counter */
			counter = 0;
		}
	turn_on_leds(counter);
	}
#endif

#ifdef PROFILER
	char *data = "Hello There!";
	counter_init();

	start_counter();
	delay(600);
	stop_counter();

#endif

//Circular Buffer Integration.
#ifdef CIRC_BUF

__disable_irq();

init_uart();

config_receive();
config_transmit();

//struct buffer buf;

//Init_Buffer(&buf, 4);

__enable_irq();

char ch, out;

while(1) {

		while( (UART0_S1 | 0x20) == 0xE0 ) {
			ch = UART0_D;
		}

//		Add_to_Buffer(&buf, &ch);

//		Remove_from_Buffer(&buf, &out);

		wait_for_buffer_empty();
		UART0_D = out;

		if(out == 'e') {
			//Free_Buffer(&buf);
			return 0;
		}
	}

#endif

return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
