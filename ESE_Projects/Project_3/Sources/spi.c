/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#include "spi.h"

void spi_0_init(void)
{
	/* Enable the clock gate for SPI0 */
	SIM_SCGC4 |= SET_SPI_CLK_GATE;

	/* Enable the clock gate for PORTC */
	SIM_SCGC5 |= SET_CLK_GATE_PORT_C;

	/* Enable the ALT mux for the GPIO pins */
	PORTC_PCR4 = CONFIG_PORTC4_GPIO;
	PORTC_PCR5 = CONFIG_PORTC5_SPI_SCK;
	PORTC_PCR6 = CONFIG_PORTC6_SPI_MOSI;
	PORTC_PCR7 = CONFIG_PORTC7_SPI_MISO;

	/*Config direction of GPIO PORTC4 as output*/
	GPIOC_PDDR |= CONFIG_PORTC4_DIR_OUT;

	/*Config the Baud Rate for SPI comm.*/
	SPI_BR_REG(SPI0) = SPI_BAUD_RATE;

	/* Config the C1 SPI register */
	SPI0->C1 = SPI_C1_CONFIG;

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

	if(ret_value!=NULL){
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}

}

uint8_t Read_from_nRF_Register(uint8_t *reg_addr)
{
	if(reg_addr == NULL) {
		return NULL_FAILURE;
	}

	uint8_t return_nRF_value = 0;

	Pull_CS_Low();
	Send_Read_Write_Command(reg_addr);

	delay(15);

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

	delay(15);

	return_nRF_value = Send_Write_Value(write_value);
	Pull_CS_High();

	return return_nRF_value;

}
