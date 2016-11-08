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

#define SPI_Trials
#define SPI_Read_Working

int main(void)
{

#ifdef SPI_0_WORKING

	spi_0_init();

	//while(1);

	volatile char data1 = 0x20; //Write to the config register.
	volatile char data2 = 0x02; //Power up the device!
	volatile uint8_t rx_ret = 0;
	//data1 = malloc(sizeof(char) * 3);
	//*data1 = 0x0A;

	GPIOC_PCOR = 0x00000010;               // Activate SPI
	    while(WAIT_FOR_SPTEF);
	    //while(!(SPI1->S & 0x20)) { }
	      //SPI_D_REG(SPI0) = 0xFF;
	    SPI0->D = 0xFF;
	    //while(!(SPI1->S & 0x80)) { }
	       //rx_ret = SPI_D_REG(SPI0);
	    while(WAIT_FOR_SPRF);
	    rx_ret = SPI0->D;


	GPIOC_PSOR = 0x00000010;
	/* Clear the 4th pin on GPIO; CS = 0*/

#endif

#ifdef SPI_Read_Working

	uint8_t rx_ret[7] = {0};
	uint8_t cmd = RF_CH;

	/*Write Operations*/
	uint8_t reg_addr = /*0x25*/W_REGISTER | RF_CH;
	uint8_t write_value = 0x02;

	spi_init();

	rx_ret[0] = Read_from_nRF_Register(&cmd);

	rx_ret[1] = Write_to_nRF_Register(&reg_addr, write_value);

	rx_ret[2] = Read_from_nRF_Register(&cmd);

#endif


#ifdef CLI_PARSER

	CLI command_in;
	uint32_t command_length = 0;
	char data[40];

	/* Enter the CLI on the console */
	get_CLI(&data[0], &command_in.cmd_length);

	parse_CLI(data, &command_in);

	act_on_command(&command_in);

#endif

#ifdef MSG_STRUCT_2

	CLI command_in;
	uint8_t i = 0;
	char payload[40];
	//char *payload = NULL;
	//payload = malloc(sizeof(char) * 30);

	get_message(&payload[0]);

	parse_CLI(&payload[0], &command_in);

	//free(payload);

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

	return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
