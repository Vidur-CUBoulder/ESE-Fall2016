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

/*Function: spi_0_init()
 * Parameters: void
 * Return: void
 * Description: Initialize SPI0 as Master!
 */
void spi_0_init(void);

/*Function: spi_1_init()
 * Parameters: void
 * Return: void
 * Description: Initialize SPI1 as Master!
 */
void spi_1_init(void);

/*Function: Read_from_nRF_Register(reg_map reg)
 * Parameters: register that you want to read from.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: This is an aggregation function for reading data from
 * a register in the nRF device.
 */
uint8_t Read_from_nRF_Register(void *spi, reg_map reg, uint8_t *ret_value);

uint8_t Read_from_nRF_Register_SPI1(reg_map reg, uint8_t *reg_value);

/*Function: Write_to_nRF_Register(reg_map reg, uint8_t write_value)
 * Paramters: reg_addr:  This is the addr. of the register that you want to write to
 * 	      write_value: This is the value that you want to write to the register
 * 		   specified in reg_addr.
 * Return: Status returned by the nRF after the specified value has been written
 * 		   to the specifed register.
 * Description: This is the write aggregation function for the nRF module. It
 * should be used to write to a particular register in the nRF module.
 */
uint8_t Write_to_nRF_Register(void *spi, reg_map reg, uint8_t write_value);
uint8_t Write_to_nRF_Register_SPI1(reg_map reg, uint8_t write_value);

/* Function: Abs_Write_to_nRF_Register(void *spi, reg_map reg, uint8_t write_value);
 * Parameters: 
 *      a. reg: specify the register that you want to write to.
 *      b. write_value: value that you want to write into the register
 * Return: return the value that is returned from the NRF module
 * Description: This function is used to perform an absolute write to the reg.
 *              There is no OR-ing ops that will take place internally
 */
uint8_t Abs_Write_to_nRF_Register(void *spi, reg_map reg, uint8_t write_value);

uint8_t Abs_Write_to_nRF_Register_SPI1(reg_map reg, uint8_t write_value);

/*Function: errors Read_5_Bytes(reg_map reg, uint8_t *ret_value);
 * Parameters:
 * 		a. reg: pass the register that you want to read.
 * 		b. ret_value: the final return value from the function after it has done
 * 				all the processing.
 * Return: an enum that may be used for debugging purposes.
 * Description: this function can be used to read from registers on the nRF
 * 			that are 5 bytes long. It pushed 5 NOP bytes to the module.
 */
errors Read_5_Bytes(void *spi, reg_map reg, uint8_t *ret_value);

uint8_t Read_5_Bytes_SPI1(reg_map reg, uint8_t *ret_value);

#endif /* INCLUDES_SPI_H_ */
