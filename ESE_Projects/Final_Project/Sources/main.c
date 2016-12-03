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
//#define READ_PRINT_SINGLE_BYTE
//#define DEBUG
//#define temp_sensor
//#define SPI0_Rx_nRF_Comm
//#define EEPROM

int main(void)
{

#ifdef EEPROM
    uint8_t out = 0;

    spi_1_init();

    uint8_t read_status_value = 0;
    Read_Status(&read_status_value);

    //Enable_Write_Latch();
    //Disable_Write_Latch();

    uint8_t address = 0x00;
    //uint8_t data_ret = 0;

    //Write_Data_to_EEPROM(10, &address);
    //Read_Data_from_EEPROM(&address, &data_ret);

    uint8_t data[4] = {0};
    uint8_t write_data[4] = {0xAC, 0x48, 0xBA, 0xCD};

    Write_Page_Data_to_EEPROM(&write_data[0], &address, 3);

    Read_Page_Data_from_EEPROM(&data[0], &address, 4);

    delay(10);

#endif

#ifdef temp_sensor

    Init_Temp_Sensor();

    int16_t result = 0;
    
    Read_Temp_Sensor_Value(&result);

    MY_LOG_PARAMS("OUTPUT: ", result);

    /* Remaining, code for the temp. value calculation */

#endif

#ifdef SPI0_Rx_nRF_Comm

    /* Put all the Values back to what they should be! */

    uint8_t reg_value = 0;
    uint8_t data[4] = { 0x41, 0xC5, 0xF4, 0x56 };

    spi_0_init();
    spi_1_init();
   
    // we don't want these to be causing troubles
    CE_Low(SPI1);
    CE_Low(SPI0);

    reset_all_registers(SPI1);
    reset_all_registers(SPI0);
    
    nrf_Config_PTX_PRX();
    config_tx_addr();
    config_rx_addr();
    fill_tx_buffer(&data[0]);
    
    //power up both modules and make sure that the config is set acc.
    Write_to_nRF_Register(SPI1, CONFIG, 0x03); //PRX
    Read_from_nRF_Register(SPI1, CONFIG, &reg_value);
    Write_to_nRF_Register(SPI0, CONFIG, 0x02); //PTX
    Read_from_nRF_Register(SPI0, CONFIG, &reg_value);

    Dump_Reg(SPI0);
    Dump_Reg(SPI1);

    //csn for both modules shld be high, no SPI writes!!
    Pull_CS_High(SPI1);
    Pull_CS_High(SPI0);
     
    //raise the CE pins for both.. this shld do the trick!
    CE_High(SPI1);
    CE_High(SPI0);

    delay(200);
    delay(200);

    CE_Low(SPI1);
    CE_Low(SPI0);
    
    Dump_Reg(SPI0);
    Dump_Reg(SPI1);

    Pull_CS_Low(SPI1);
    
    uint8_t cmd = R_RX_PAYLOAD;
    Send_Read_Write_Command(SPI1, &cmd);
    
    delay(10);
   
    cmd = NOP;
    uint8_t data_1[4] = {0};
    uint8_t len = 4, i = 0;
    while(len) {
        data_1[i] = Send_Read_Write_Command(SPI1, &cmd);
        i++;
        len--;
    }

    delay(3);

    Pull_CS_High(SPI1);

#endif

#ifdef SPI_Read_Write_Working

	uint8_t rx_ret[7] = {0};
	uint8_t ret_debug_handle = 0;
	uint8_t out[5] = {0};
	uint8_t return_val[5] = {0};
	uint8_t cntr = 0;

	/* Init. SPI */
	spi_0_init();

	/*Config the value to be written to that register*/
	uint8_t write_value = 0x11;

	ret_debug_handle = Read_5_Bytes(SPI0, TX_ADDR, &return_val[0]);
	for(cntr=0; cntr<5; cntr++){
		out[cntr] = return_val[cntr];
		//MY_LOG_PARAMS("Write Operation Output: ", out[cntr]);
	}
	MY_LOG("\n");

	ret_debug_handle = Abs_Write_to_nRF_Register(SPI0, TX_ADDR, write_value);
	for(cntr=0; cntr<5; cntr++){
			out[cntr] = return_val[cntr];
	}
	MY_LOG_PARAMS("Write Operation Output: ", out[0]);
	MY_LOG("\n");

	/* Read agian from the register */

	ret_debug_handle = Read_5_Bytes(SPI0, TX_ADDR, &return_val[0]);
	for(cntr=0; cntr<5; cntr++){
		out[cntr] = return_val[cntr];
	}
	//MY_LOG_PARAMS("Read Operation Output: ", out[0]);
	//MY_LOG("\n");

#ifdef READ_PRINT_SINGLE_BYTE
	/*Change config to write*/
	uint8_t reg_addr = CONFIG;
        uint8_t return_value = 0;
	ret_debug_handle = Read_from_nRF_Register(SPI0, reg_addr, &return_value);
	//MY_LOG_PARAMS("Read Operation Output(post write): ", out);
	//MY_LOG("\n");
        delay(10);
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
	
	uint8_t src[8] = {0};
	uint8_t dst[8] = {0};

	uint8_t i = 0;
	for (i = 0; i<8; i++) {
		src[i] = 0x05;
		dst[i] = 0x03;
	}

	uint32_t len = 8;

#ifdef DEBUG
	/*Optional UART config. To get debugging info.*/
	init_uart();
	config_transmit();
	MY_LOG("UART Enabled Successfully!\n");
#endif

#ifdef DMA_MEMMOVE
	debug dma_ret_handle;

	/*Initialize the counter*/
	dma_ret_handle = my_memmove_dma( src, dst, len);
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
