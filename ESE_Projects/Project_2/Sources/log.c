/* This file holds the logging function definitions */

#include "log.h"

/* This function takes a pointer to data location and the length of the data
 * and prints the entire string onto the console.
 */
void MY_LOG(char *data, uint8_t length)
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
		delay(70);
		} while(i != length);
	}

	/* Stop the transmit mechanism */
	//disable_Tx_Rx();
}

