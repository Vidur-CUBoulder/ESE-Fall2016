/*
 * uart.h
 *
 *  Created on: Oct 23, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "MKL25Z4.h"


#define INIT_UART0_SYSTEM_CLOCK_GATING 0x00000400
#define SELECT_UART0_SRC_CLOCK 0x04000000
#define DISABLE_TX_RX 0x00
#define CONFIG_OVERSAMPLING_RATIO 0x0F
#define BAUD_BDH 0x00
#define BAUD_BDL 0x17
#define EN_PORTA_CLOCK 0x00000200

#define SET_RX_FLAG 0x04
#define SELECT_ALT2_PORTA 0x00000200


/* Function : init_uart()
 * Inputs:
 *		void
 * Output:
 *      void
 * Description:
 * 		initializes the UART. This is a common init. function for both Tx and Rx.
 */
void init_uart();

/* Function : config_receive()
 * Inputs:
 *		void
 * Output:
 *      void
 * Description:
 * 		init. the reception via the UART.
 */
void config_receive();

/* Function : config_receive()
 * Inputs:
 *		void
 * Output:
 *      void
 * Description:
 * 		disable both Tx and Rx on the port and go to defaults.
 */
void disable_Tx_Rx();

/* Function : config_receive()
 * Inputs:
 *		void
 * Output:
 *      void
 * Description:
 * 		init the transmit via the UART.
 */
void config_transmit();

void wait_for_buffer_empty();

void wait_for_buffer_full();

void delay(uint8_t value);

#endif /* INCLUDES_UART_H_ */
