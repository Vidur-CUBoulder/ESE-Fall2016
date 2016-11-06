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

#define SPI_TEST


#if 0
void UART0_IRQHandler() {
	char c;
	c = UART0->D;
}
#endif


int main(void)
{
#ifdef SPI_TEST

	spi_1_master_init();
	//spi_0_slave_init();

	//while(1);

	char *data1 = NULL;
	data1 = malloc(sizeof(char) * 3);
	*data1 = 0x0A;

	/* Clear the 4th pin on GPIO; CS = 0*/

#if 1
	GPIOD_PCOR = 0x00000010; // CLEAR the CS

	while(!(SPI1->S & 0x20)) { }
	SPI1->D = *data1;

	while(!(SPI1->S & 0x80)) { }
	*(data1 + sizeof(char)) = SPI1->D;
	//dummy = SPI1->D;

	GPIOD_PSOR |= 0x00000010; // SET the CS.

	free(data1);

#endif

#endif

#ifdef MSG_STRUCT

	CLI command_in;
	uint32_t command_length = 0;
	char data[40];

	/* Enter the CLI on the console */
	get_CLI(&data[0], &command_in.cmd_length);

	parse_CLI(data, &command_in);

	act_on_command(&command_in);

#endif


#ifdef dma_test

	uint8_t src[] = {0x39,0x53,0x57,0x32,0x74,0x23,0xa5,0xc4, 0x13, 0xfd, 0xcd};
	uint8_t dst[] = {8,1,9,0,4,1,23,5, 1,6, 7};
	//uint8_t src[100] = {12};
	//uint8_t dst[100] = {10};
	uint32_t len = 11;

#ifdef DEBUG
	/*Optional UART config. To get debugging info.*/
	init_uart(); //Initialize the UART...
	config_transmit(); //Config. the transmit registers.
	MY_LOG("UART Enabled Successfully!\n");
#endif

#ifdef DMA_MEMMOVE
	dma_debug dma_ret_handle;

	/*Initialize the counter*/
	dma_ret_handle = my_memmove_dma( src, dst, len);
	#ifdef DEBUG
		handle_errors(dma_ret_handle);
	#endif
#endif

#ifdef DMA_MEMZERO
	dma_debug dma_ret_handle;
	dma_ret_handle = my_memzero_dma(src, len);
	#ifdef DEBUG
		handle_errors(dma_ret_handle);
	#endif
#endif

#endif

#ifdef test

	__disable_irq();

	/* UART0 Clock gate */
	SIM->SCGC4 |= 0x0400;

	/* Process clock for PORT A*/
	SIM->SCGC5 |= 0x0200;

	/* Set UART0SRC */
	SIM->SOPT2 |= 0x04000000;

	/* Disable Tx/Rx */
	UART0->C1 = 0x00;

	/* Clear all prev. configs on C2 */
	UART0_C2 = 0x00;

	/* Config the baud settings */
	UART0_C4 = 0x0F;
	UART0_BDH = BAUD_BDH;
	UART0_BDL = BAUD_BDL;


	/* Enable RIE and RE */
	UART0->C2 = 0x24;
	//NVIC->ISER[0] |= 0x00001000;

	/* Set the Muxing and the IRQ on PORT A*/
	PORTA_PCR1 = 0x0200;

	NVIC_EnableIRQ(12);

	__enable_irq();

	while(!(UART0_S1 & 0x20)) {
			/*Wait for Buffer Full!*/
		}


#endif

	return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
