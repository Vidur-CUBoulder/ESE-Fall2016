/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#include "spi.h"

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
	PORTD_PCR5 = 0x00000200;
	PORTD_PCR6 = 0x00000200;
	PORTD_PCR7 = 0x00000200;

	SPI1->C2 = 0x00;

	SPI1->C1 = 0x14;

	//SPI1_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));
	SPI1_BR = 0x00000000;

	SPI1->C1 |= SPI_C1_SPE_MASK; //Enable the SPE!

}

void spi_0_slave_init() //slave
{
	/* Enable the clock gate for SPI0 */
	SIM_SCGC4 |= 0x00400000;

	/* Enable the clock gate for PORTC */
	SIM_SCGC5 |= 0x00000800;

	/* Enable the ALT mux for the GPIO pins */
	PORTC_PCR4 = 0x00000200;
	PORTC_PCR5 = 0x00000200;
	PORTC_PCR6 = 0x00000200;
	PORTC_PCR7 = 0x00000200;

	SPI0->C1 |= 0x02;

	SPI0->C2 = SPI_C2_MODFEN_MASK;

	SPI0->C1 |= SPI_C1_SPE_MASK;

}
