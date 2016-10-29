/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

void spi_init()
{
	/*1. Enable the clock gate for SPI0 */
	SIM_SCGC4 |= 0x00400000;

	/*Next, enable the clock gate for port C */
	SIM_SCGC5 |= 0x00000800;

	/* Config the ALT values on all the PORTC pins (4, 5, 6, 7) */
	// Master-> KL25z Slave->nRF
	//PORTC_PCR4 |= 0x00000200; //SPI0_PCS0 --> may not need to config as PCS ??
	PORTC_PCR5 |= 0x00000200; //SPI0_SCK
	PORTC_PCR6 |= 0x00000200; //SPI0_MOSI --> Master In Slave Out
	PORTC_PCR7 |= 0x00000200; //SPI0_MISO --> Master Out Slave In

	PORTC_PCR4 |= 0x00000100; //Config. as GPIO.

	/* Config. PCR4 as GPIO output */
	GPIOC_PDDR = 0x00000010;
	/* Set PDDR to IDLE high */
	GPIOC_PSOR = 0x00000010;







}
