/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#include "spi.h"

void spi_init(void)
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

#if 0
void Pull_CS_Low(void)
{
	GPIOC_PCOR = 0x00000010;
}

void Pull_CS_High(void)
{
	GPIOC_PSOR = 0x00000010;
}
#endif

uint8_t Send_Read_Write_Command(uint8_t *cmd)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = *cmd;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;
}

uint8_t Send_Dummy_Byte(void)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = NOP;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;

}

uint8_t Send_Write_Value(uint8_t write_value)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = write_value;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;

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

/* !!!!!!!!!!!!!!!!!!!!!!!   TODO: Need to remove old code after thorough testing   !!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#if 0


uint8_t read_RX_ADDR_P0()
{
	uint8_t ret_status = 0;

	GPIOC_PCOR = 0x00000010; // CLEAR the CS

	while(WAIT_FOR_SPTEF);
	SPI0->D = 0xFF;

	while(WAIT_FOR_SPRF);
	ret_status = SPI0->D;

	GPIOC_PSOR = 0x00000010;

	return ret_status;
}

uint8_t push_dummy()
{
	uint8_t ret_status = 0;

	GPIOD_PCOR = 0x00000010; // CLEAR the CS

	while(WAIT_FOR_SPTEF);
	SPI0->D = 0xFF;
	while(WAIT_FOR_SPRF);
	ret_status = SPI0->D;

	GPIOD_PSOR = 0x00000010;

	return ret_status;
}


void spi_1_master_init() //master
{
	/* Enable the clock gate for SPI1 */
	SIM_SCGC4 |= 0x00800000;

	/* Enable the clock gate for port D */
	SIM_SCGC5 |= 0x00001000;

	//PORTD_PCR4 = 0x00000200;
	PORTD_PCR4 |= 0x100; // Set as GPIO
	GPIOD_PDDR |= 0x00000010; //Set the GPIO pin as output
	GPIOD_PSOR |= 0x00000010; // Sets the GPIO pin to high

	PORTD_PCR5 |= 0x00000200;
	PORTD_PCR6 |= 0x00000200;
	PORTD_PCR7 |= 0x00000200;

	SPI1->C2 = 0x00;

	SPI1->C1 = SPI_C1_MSTR_MASK | SPI_C1_CPHA_MASK;

	//SPI1_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));
	SPI1_BR = 0x01;

	SPI1->C1 |= SPI_C1_SPE_MASK; //Enable the SPE!

}

void spi_trial_code()
{
	  // Turn on port C
	   SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	   // Turn on SPI0 clock
	   SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	   // Set up ports for SPI0
	   PORTC->PCR[4] |= PORT_PCR_MUX(1); // ss as gpio pin
	   PORTC->PCR[5] |= PORT_PCR_MUX(2);
	   PORTC->PCR[6] |= PORT_PCR_MUX(2);
	   PORTC->PCR[7] |= PORT_PCR_MUX(2);

	   // Set port C, pin 8 data direction to output
	   PTC_BASE_PTR->PDDR |= 1<<8;

	   SPI_C1_REG(SPI0) = SPI_C1_SPE_MASK;
	   SPI_C2_REG(SPI0) = 0x00;

	   SPI_C1_REG(SPI0) = SPI_C1_MSTR_MASK |
	                   SPI_C1_SPE_MASK |
	                   SPI_C1_CPHA_MASK;

	   // prescaler=1, divisor=4 , 24MHz/4 = 6MHz
	   SPI_BR_REG(SPI0) = 0x01;
}

void spi_0_init()
{
	/* Enable the clock gate for SPI0 */
	SIM_SCGC4 |= 0x00400000;

	/* Enable the clock gate for PORTC */
	SIM_SCGC5 |= 0x00000800;

	/* Enable the ALT mux for the GPIO pins */
	PORTC_PCR4 = 0x00000100;
	PORTC_PCR5 = 0x00000200;
	PORTC_PCR6 = 0x00000200;
	PORTC_PCR7 = 0x00000200;

	GPIOC_PDDR |= 0x00000010;

	SPI_BR_REG(SPI0) = 0x30;

	SPI0->C1 = 0x50;

}

#endif
