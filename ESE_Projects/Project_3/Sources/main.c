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


//#define SPI_Read_Write_Working
//#define DEBUG


int main(void)
{

	spi_init(); //Init. the SPI.

	/*Config PORTD pin19 as GPIO for CE on nRF*/
	SIM_SCGC5 |= 0x00001000;

	PORTD_PCR7 |= 0x00000100;

	GPIOD_PDDR |= 0x00000080;

	GPIOD_PCOR |= 0x00000080;

	/*First fill RX_ADDR_P0 with 0xE7E7E7E7E7 same as TX.
	 * This is set to that register by default. So not doing anything.*/

	/*Enable AA for Pipe0*/
	Write_to_nRF_Register(EN_AA, 0x01);

	/*Enable Pipe0*/
	Write_to_nRF_Register(EN_RXADDR, 0x01);

	/*Select RF Channel as 76*/
	Write_to_nRF_Register(RF_CH, 0x4C);

	/*Select the same RX payload width as the TX payload width*/
	Write_to_nRF_Register(RX_PW_P0, 0x01);

	/*config RF_SETUP*/
	Write_to_nRF_Register(RF_SETUP, 0x60);

	/*set the CONFIG register*/
	Write_to_nRF_Register(0x07, 0x0F);

	GPIOD_PSOR |= 0x00000080; // Pull the CE pin high.

	while(1) {
		if (Read_from_nRF_Register(R_RX_PAYLOAD) == 0x01) { //FIXME: check, may not be correct
			return 0;
		}
	}


#ifdef SPI_Read_Write_Working

	uint8_t rx_ret[7] = {0};
	uint8_t ret_debug_handle = 0;
	uint8_t out[5] = {0};
	uint8_t return_val[5] = {0};
	uint8_t cntr = 0;

	/* Init. SPI */
	spi_init();

	/*Config. the register address*/
	uint8_t reg_addr = R_REGISTER | TX_ADDR;

	/*Config the value to be written to that register*/
	uint8_t write_value = 0x11;

	ret_debug_handle = Read_5_Bytes(&reg_addr, &return_val[0]);
	for(cntr=0; cntr<5; cntr++){
		out[cntr] = return_val[cntr];
	}
	MY_LOG_PARAMS("Read Operation Output: ", out[0]);
	MY_LOG("\n");

	/*Change config to write*/
	reg_addr = W_REGISTER | TX_ADDR;

	ret_debug_handle = Write_to_nRF_Register(&reg_addr, write_value);
	for(cntr=0; cntr<5; cntr++){
			out[cntr] = return_val[cntr];
	}
	MY_LOG_PARAMS("Write Operation Output: ", out[0]);
	MY_LOG("\n");

	/* Read agian from the register */
	reg_addr = R_REGISTER | TX_ADDR;

	ret_debug_handle = Read_5_Bytes(&reg_addr, &return_val[0]);
	for(cntr=0; cntr<5; cntr++){
		out[cntr] = return_val[cntr];
	}
	MY_LOG_PARAMS("Read Operation Output: ", out[0]);
	MY_LOG("\n");

#if READ_PRINT_SINGLE_BYTE
	/*Change config to write*/
	reg_addr = R_REGISTER | CONFIG;

	ret_debug_handle = Read_Single_Byte(&reg_addr, &return_val);
	out = return_val;
	MY_LOG_PARAMS("Read Operation Output(post write): ", out);
	MY_LOG("\n");
#endif

#endif

#ifdef UART_PARSER

	CLI command_in;
	uint8_t i = 0;
	checksum ret_checksum_result;
	uint8_t *payload = NULL;
	payload = malloc(sizeof(char) * 30);

	get_message(payload);

	parse_CLI(payload, &command_in);

	ret_checksum_result = fletchers_checksum(command_in);

	if(!ret_checksum_result) {
		MY_LOG("Checksum Passes!\n");
		act_on_command(&command_in);
	} else {
		MY_LOG("Checksum Failure!\n");
	}

	free(payload);

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

#ifdef ENABLE_DMA
;
	uint8_t src[11] = {0};
	uint8_t dst[11] = {0};

	uint8_t i = 0;
	for (i = 0; i<11; i++) {
		src[i] = 0x05;
		dst[i] = 0x03;
	}

	uint32_t len = 11;

#ifdef DEBUG
	/*Optional UART config. To get debugging info.*/
	init_uart();
	config_transmit();
	MY_LOG("UART Enabled Successfully!\n");
#endif

#ifdef DMA_MEMMOVE
	debug dma_ret_handle;

	/*Initialize the counter*/
	//start_counter();
	dma_ret_handle = my_memmove_dma( src, dst, len);
	//stop_counter();
	#ifdef DEBUG
		handle_errors(dma_ret_handle);
	#endif
#endif

#ifdef DMA_MEMZERO

#if 0
	double sys_clock = 0.047; // in microsecs
	double count, net_time;

	counter_init();
#endif

	debug dma_ret_handle;

	//start_counter();
	dma_ret_handle = my_memzero_dma(src, len);
	//stop_counter();
#if 0
	count = TPM0_CNT;
	net_time = count * sys_clock;
#endif

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
