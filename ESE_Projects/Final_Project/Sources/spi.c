/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#include "spi.h"

/* Config. as master */
void spi_1_init(void)
{
	/* Enable the clock gate for SPI1 */
	SIM_SCGC4 |= SET_SPI1_CLK_GATE;

	/* Enable the Clock Gate for PORTD */
	SIM_SCGC5 |= SET_CLK_GATE_PORT_D;

	/* Enable the ALT mux for the GPIO pins */
	PORTD_PCR4 = CONFIG_PORTD4_GPIO;
	PORTD_PCR5 = CONFIG_PORTD5_SPI_SCK;
	PORTD_PCR6 = CONFIG_PORTD6_SPI_MOSI;
	PORTD_PCR7 = CONFIG_PORTD7_SPI_MISO;

	/* Config the direction of the GPIO PORTD4 as output */
	GPIOD_PDDR |= CONFIG_PORTD4_DIR_OUT;

	/* Config the Baud Rate for SPI1 comm. */
	SPI_BR_REG(SPI1) = SPI1_BAUD_RATE;

	/*Config the C1 SPI1 register as master connection */
	SPI1->C1 = SPI1_C1_CONFIG;

}

/* Config. as master */
void spi_0_init(void)
{
	/* Enable the clock gate for SPI0 */
	SIM_SCGC4 |= SET_SPI0_CLK_GATE;

	/* Enable the clock gate for PORTC */
	SIM_SCGC5 |= SET_CLK_GATE_PORT_C;

	/* Enable the ALT mux for the GPIO pins */
	PORTC_PCR4 = CONFIG_PORTC4_GPIO;
	PORTC_PCR5 = CONFIG_PORTC5_SPI_SCK;
	PORTC_PCR6 = CONFIG_PORTC6_SPI_MOSI;
	PORTC_PCR7 = CONFIG_PORTC7_SPI_MISO;

	/*Config direction of GPIO PORTC4 as output*/
	GPIOC_PDDR |= CONFIG_PORTC4_DIR_OUT;

	/*Config the Baud Rate for SPI0 comm.*/	
	SPI_BR_REG(SPI0) = SPI0_BAUD_RATE;

	/* Config the C1 SPI0 register as the master connection */
	SPI0->C1 = SPI0_C1_CONFIG;

}

uint8_t Read_Single_Byte(uint8_t *cmd, uint8_t *ret_value)
{
	if (cmd == NULL) {
		return NULL_FAILURE;
	}

	*ret_value = Read_from_nRF_Register(cmd);

	if(ret_value!=NULL){
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}

}

uint8_t Read_5_Bytes(uint8_t *cmd, uint8_t *ret_value)
{
	if (cmd == NULL || ret_value == NULL) {
		return NULL_FAILURE;
	}

	uint8_t cntr = 0;

	for(cntr = 0; cntr < MAX_REG_LENGTH; cntr++) {
		*(ret_value+cntr) = Read_from_nRF_Register(cmd);
	}

	if(ret_value != NULL) {
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}

}

uint8_t Read_5_Bytes_SPI1(uint8_t *cmd, uint8_t *ret_value)
{
	if (cmd == NULL || ret_value == NULL) {
		return NULL_FAILURE;
	}

	uint8_t cntr = 0;

	for(cntr = 0; cntr < MAX_REG_LENGTH; cntr++) {
		*(ret_value+cntr) = Read_from_nRF_Register_SPI1(cmd);
	}

	if(ret_value != NULL) {
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}

}

uint8_t Read_from_nRF_Register_SPI1(uint8_t *reg_addr)
{
	if(reg_addr == NULL) {
		return NULL_FAILURE;
	}

	uint8_t return_nRF_value = 0;

	Pull_CS_Low_SPI1();
	
	uint8_t ret_value = 0;

	while(!(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK));
	SPI1->D = *reg_addr;
	while(!(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK));
	ret_value = SPI1->D;

	delay(10);

	//return_nRF_value = Send_Dummy_Byte();
	
	while(!(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK));
	SPI1->D = NOP;
	while(!(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK));
	return_nRF_value = SPI1->D;
	
	Pull_CS_High_SPI1();

	return return_nRF_value;

}

uint8_t Read_from_nRF_Register(uint8_t *reg_addr)
{
	if(reg_addr == NULL) {
		return NULL_FAILURE;
	}

	uint8_t return_nRF_value = 0;

	Pull_CS_Low();
	Send_Read_Write_Command(reg_addr);

	delay(10);

	return_nRF_value = Send_Dummy_Byte();
	Pull_CS_High();

	return return_nRF_value;

}

uint8_t Write_to_nRF_Register(uint8_t *reg_addr, uint8_t write_value)
{
	if(reg_addr == NULL) {
		return NULL_FAILURE;
	}

	uint8_t return_nRF_value = 0;

	Pull_CS_Low();
	Send_Read_Write_Command(reg_addr);

	delay(10);

	return_nRF_value = Send_Write_Value(write_value);
	Pull_CS_High();

	return return_nRF_value;

}
