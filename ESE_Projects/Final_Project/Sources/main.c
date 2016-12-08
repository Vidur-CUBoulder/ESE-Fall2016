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
#include "core_cmInstr.h"

//#define SPI_Read_Write_Working
//#define READ_PRINT_SINGLE_BYTE
//#define DEBUG
#define temp_sensor
//#define SPI0_Rx_nRF_Comm
//#define EEPROM
//#define Final_Program
//#define Final_EEPROM
//#define UART_PARSER

int main(void)
{

#ifdef Final_Program

    nRF_Cluster *new_cluster = NULL;
    uint8_t reg_value = 0;

    spi_0_init();
    spi_1_init();


    nRF_Values PTX_Config_Data = {SPI0, 76, 4, 0x06, 0x08, 0x03, 0x03, 0x4F, 0x00, 0x70,{0xe7, 0xe7, 0xe7, 0xe7, 0xe7 },\
                                {0xe7, 0xe7, 0xe7, 0xe7, 0xe7}, {0xd7, 0xd7, 0xd7, 0xd7, 0xd7} };  
    nRF_Values PRX_Config_Data = {SPI1, 76, 4, 0x06, 0x08, 0x03, 0x03, 0x4F, 0x00, 0x70,{0xd7, 0xd7, 0xd7, 0xd7, 0xd7 },\
                                {0xd7, 0xd7, 0xd7, 0xd7, 0xd7}, {0xe7, 0xe7, 0xe7, 0xe7, 0xe7} };
    
    uint8_t data[4] = {0x24, 0x54, 0xFE, 0x4D};
    uint8_t data_1[4] = {0};
    errors debug_handle = 0 ;

    new_cluster = Alloc_nRF_Cluster();
    
    debug_handle = init_nRF_modules(new_cluster, &PTX_Config_Data, &PRX_Config_Data);

    //Fill the SPI buffer with the data.
    debug_handle = new_cluster->fill_buffer(PTX_Config_Data.spi_number,\
                                                &data[0], 4);  

    /* Turn-On the Modules! */
    new_cluster->Activate_Modules(PRX_Config_Data.spi_number,\
                                  PTX_Config_Data.spi_number);

    /* Instead of the delay, monitor the status register and
     * if the RX_DR pin is set, come out of the loop and
     * read the value for the RX payload register.
     */
    
    while(reg_value != DATA_IN_RX_PAYLOAD) {
        /* Continue reading the Status register until data is received in the 
         * RX payload register.
         */
        Read_from_nRF_Register(PRX_Config_Data.spi_number, STATUS, &reg_value);
    }
   
    /* Read the data payload from the RX module */
    Read_Payload_Register_Value(PRX_Config_Data.spi_number, new_cluster, &data_1[0], 4);
   
    /* Free the Cluster once the work is done! */
    new_cluster->Free_Cluster(new_cluster);

#endif


#ifdef EEPROM
    uint8_t out = 0;

    //spi_1_init();
    /* Enable the clock gate for SPI1 */
    SIM_SCGC4 |= SET_SPI1_CLK_GATE;

    /* Enable the Clock Gate for PORTD */
    SIM_SCGC5 |= SET_CLK_GATE_PORT_D;

    /* Enable the ALT mux for the GPIO pins */
    PORT_PCR_REG(PORTD, 3) = CONFIG_PORTD3_GPIO;      //Config as CE
    PORT_PCR_REG(PORTD, 4) = CONFIG_PORTD4_GPIO;      //Config as CS
    PORT_PCR_REG(PORTD, 5) = CONFIG_PORTD5_SPI_SCK;   //Config as SCK
    PORT_PCR_REG(PORTD, 6) = CONFIG_PORTD6_SPI_MOSI;  //Config as MOSI
    PORT_PCR_REG(PORTD, 7) = CONFIG_PORTD7_SPI_MISO;  //Config as MISO

    /* Config the direction of the GPIO PORTD4 & PORTD3 as output */
    GPIO_PDDR_REG(GPIOD) = (CONFIG_PORTD4_DIR_OUT | CONFIG_PORTD3_DIR_OUT);

    /* Config the Baud Rate for SPI1 comm. */
    SPI_BR_REG(SPI1) = /*0x36*/0x30;

    /*Config the C1 SPI1 register as master connection */
    SPI_C1_REG(SPI1) = /*SPI_C1_CONFIG*/0x5C;

    /* Pull the CS High Now! */
    Pull_CS_High(SPI1);


    uint8_t read_status_value = 0;
    //Read_Status(&read_status_value);
    
    uint8_t return_nRF_value = 0;
    uint8_t ret_value = 0;

    //Pull the CS low first!
    Pull_CS_Low(SPI1);
    
    //Send_EEPROM_Read_Write(RDSR);
    while ( !(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK)) { }
    SPI1->D = 0x05;
    delay(40);
    SPI1->D = 0xFF;
    //while ( !(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK)) { }
    ret_value = SPI1->D;


    delay(20);

    SPI1->D = 0xFF;
    while(WAIT_FOR_SPTEF_SPI1);
    ret_value = SPI1->D;

/*
    delay(20);

    SPI1->D = 0xFF;
    while(WAIT_FOR_SPRF_SPI1);
    ret_value = SPI1->D;
*/
    
    Pull_CS_High(SPI1);
  
    //don't be cheeky!!
    //*read_status_value <<= 3;

#if 0
    //Enable_Write_Latch();
    Disable_Write_Latch();

    uint8_t address = 0x05;
    uint8_t data_ret = 0;

    Write_Data_to_EEPROM(12, &address);
    Read_Data_from_EEPROM(&address, &data_ret);

    uint8_t data[4] = {0};
    uint8_t write_data[4] = {0xAC, 0x48, 0xBA, 0xCD};

    Write_Page_Data_to_EEPROM(&write_data[0], &address, 3);

    Read_Page_Data_from_EEPROM(&data[0], &address, 4);
#endif
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

#if 0

	CLI command_in;
	uint32_t command_length = 0;
	char data[40];

	/* Enter the CLI on the console */
	get_CLI(&data[0]/*, &command_in.cmd_length*/);

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
