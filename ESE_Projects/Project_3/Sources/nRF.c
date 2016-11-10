/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

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
