/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

int8_t nRF_ops(int8_t (*ops_type)(int8_t, reg_map), int8_t reg_value, reg_map reg)
{
    return ((*ops_type)(reg_value, reg));
}

int8_t Write_to_nRF(int8_t reg_value, reg_map reg)
{
    uint8_t reg_addr = 0;

    reg_addr = W_REGISTER | reg;
    return (Write_to_nRF_Register(&reg_addr, reg_value));
}

int8_t Read_from_nRF(int8_t reg_value, reg_map reg)
{
    uint8_t reg_addr = 0;
    int8_t ret_debug_handle;

    reg_addr = R_REGISTER | reg;
    ret_debug_handle = Read_Single_Byte(&reg_addr, &reg_value);
    MY_LOG_PARAMS("Read Operation Output: ", reg_value);
    MY_LOG("\n");
    
    return ret_debug_handle;
}

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


