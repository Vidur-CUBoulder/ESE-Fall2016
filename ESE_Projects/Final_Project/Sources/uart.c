/*
 * uart.c
 *
 *  Created on: Oct 23, 2016
 *      Author: vidur
 */

#include "uart.h"

void init_uart()
{
	/* 1. Initialize the System Clock Gating Control Register for UART0 */
	SIM_SCGC4 |= INIT_UART0_SYSTEM_CLOCK_GATING;

	/* 2. Configure the Systems Options Register to select the UART0 source clock */
	SIM_SOPT2 |= SELECT_UART0_SRC_CLOCK;

	/* 3. While changing the configurations, we need to make sure that the
	 * UART control register is set LOW. This makes sure that the UART
	 * transmitter and receiver are both disabled while we are configuring
	 * the various properties of the UART.
	 */
	UART0_C2 = DISABLE_TX_RX;

	/* Setting the oversampling ratio in the C4 reg. */
	UART0_C4 = 0x0F;

	/* 4. Now, setting the Baud values in the BDH and BDL registers.
	 * For a Baud of 115200, BDH = 0x00 and BDL = 0x17. This is based on
	 * the assumption, that the core frequency is being used @ 48MHz. Moreover,
	 * this also has to take into account the oversampling ratio which is set to 16.
	 */
	UART0_BDH = BAUD_BDH;
	UART0_BDL = BAUD_BDL;

	/* 5. We need to make the following changes to the UART0_C1 register:
	 * 		(Bit 7)Loop Mode Select: Normal Operation i.e Rx and Tx use separate pins.
	 * 		(Bit 5)Receiver Source Select: 0. Only makes a difference if LOOP is set.
	 */
	UART0_C1 = 0x00;

	/* 6. Next, we need to enable the clock for PORTA. */
	SIM_SCGC5 |= EN_PORTA_CLOCK;
}

void config_receive()
{
	/* Enable Receive.*/
	UART0_C2 |= 0x04;

	/* Setting the Pin Control Register for PORTA.
	 * For Pin Mux ALT2,
	 * 		UART0_RX = PTA1
	 * 		UART0_TX = PTA2
	 */
	PORTA_PCR1 = 0x00000200;
}

void disable_Tx_Rx()
{
	/* While changing the configurations, we need to make sure that the
	 * UART control register is set LOW. This makes sure that the UART
	 * transmitter and receiver are both disabled while we are configuring
	 * the various properties of the UART.
	 */
	UART0_C2 = 0x00;
}

void config_transmit()
{
	/* Enable Transmit.*/
	UART0_C2 |= 0x08;

	/* 7. Setting the Pin Control Register for PORTA.
	 * We need to keep in mind that the registers for TX and RX are different!
	 * For Pin Mux ALT2,
	 * 		UART0_RX = PTA1
	 * 		UART0_TX = PTA2
	 */
	PORTA_PCR2 = 0x00000200;
}

void wait_for_buffer_empty()
{
	while(!(UART0_S1 & 0x80)) {
		/* WAIT for buffer empty!*/
	}
	return;
}

void wait_for_buffer_full()
{
	while(!(UART0_S1 & 0x20)) {
		/*Wait for Buffer Full!*/
	}
	return;
}

void delay(uint8_t value)
{
	int i,j =0;
	for(i=0; i<value; i++) {
		for(j=0; j<5000; j++){
			/*delay*/
		}
	}
}

