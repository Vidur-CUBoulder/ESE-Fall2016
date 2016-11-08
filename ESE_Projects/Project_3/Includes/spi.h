/*
 * spi.h
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include "MKL25Z4.h"
#include "parse_data.h"
#include "spi_masks.h"

/*Function: spi_init()
 * Parameters: void
 * Return: void
 * Description: Initialize the SPI Master!
 */
void spi_init(void);

/* Function: Send_Read_Write_Command(uint8_t *cmd)
 * Parameters: Command byte that has to be sent to the nRF module.
 * This could be either for reading or writing.
 * Return: Value returned by the nRF module
 * Description: Send the command byte to the nRF module and return
 * the value that MISO pushes back into the Rx Buffer.
 */
uint8_t Send_Read_Write_Command(uint8_t *cmd);

/*Function: Send_Dummy_Byte(void)
 * Parameters: void
 * Return: Value returned by the nRF module
 * Description: Send the NOP byte to the nRF module to:
 * 	a. Get/read the value of the previous command
 * 	b. Get/read the value of the Status register.
 */
uint8_t Send_Dummy_Byte(void);

/*Function: Read_from_nRF_Register(uint8_t *reg_addr)
 * Parameters: register address that you want to read from.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: This is an aggregation function for reading data from
 * a register in the nRF device.
 */
uint8_t Read_from_nRF_Register(uint8_t *reg_addr);

/*Function: Send_Write_Value(uint8_t write_value)
 * Parameters: value that has to be written to the nRF register.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: Send the write value to the respective nRF register.
 * XXX: Please note that this function must be preceded by Send_Read_Write_Command(*cmd)!
 * Failure to do this will result in an unexpected behavior.
 */
uint8_t Send_Write_Value(uint8_t write_value);

/*Function: Write_to_nRF_Register(uint8_t *reg_addr, uint8_t write_value)
 * Paramters: reg_addr:  This is the addr. of the register that you want to write to
 * 			  write_value: This is the value that you want to write to the register
 * 			  			   specified in reg_addr.
 * Return: Status returned by the nRF after the specified value has been written
 * 		   to the specifed register.
 * Description: This is the write aggregation function for the nRF module. It
 * should be used to write to a particular register in the nRF module.
 */
uint8_t Write_to_nRF_Register(uint8_t *reg_addr, uint8_t write_value);

#endif /* INCLUDES_SPI_H_ */
