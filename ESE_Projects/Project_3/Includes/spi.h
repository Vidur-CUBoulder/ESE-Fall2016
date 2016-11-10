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
#include "nRF.h"

/*Function: spi_init()
 * Parameters: void
 * Return: void
 * Description: Initialize the SPI Master!
 */
void spi_init(void);

/*Function: Read_from_nRF_Register(uint8_t *reg_addr)
 * Parameters: register address that you want to read from.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: This is an aggregation function for reading data from
 * a register in the nRF device.
 */
uint8_t Read_from_nRF_Register(uint8_t *reg_addr);

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

/*Function: uint8_t Read_Single_Byte(uint8_t *cmd, uint8_t *ret_value);
 * Parameters:
 * 		a. cmd: pass the struct where all the data is organized.
 * 		b. ret_value: the final return value from the function after it has done
 * 			all the processing.
 * Return: an enum that may be used for debugging purposes.
 * Description: this function can be used to read from registers on the nRF
 * 			that are only one byte in length.
 */
uint8_t Read_Single_Byte(uint8_t *cmd, uint8_t *ret_value);

/*Function: uint8_t Read_5_Bytes(uint8_t *cmd, uint8_t *ret_value);
 * Parameters:
 * 		a. cmd: pass the struct where all the data is organized.
 * 		b. ret_value: the final return value from the function after it has done
 * 				all the processing.
 * Return: an enum that may be used for debugging purposes.
 * Description: this function can be used to read from registers on the nRF
 * 			that are 5 bytes long. It pushed 5 NOP bytes to the module.
 */
uint8_t Read_5_Bytes(uint8_t *cmd, uint8_t *ret_value);


#endif /* INCLUDES_SPI_H_ */
