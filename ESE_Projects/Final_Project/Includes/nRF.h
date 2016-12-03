/*
 * nRF.h
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_NRF_H_
#define INCLUDES_NRF_H_

#include "error_handling.h"
#include "spi_masks.h"

typedef enum errors_t {
	SUCCESSFUL,
	INCORRECT_ENTRY,
	NULL_FAILURE,
	INVALID,
	INVALID_RET_FROM_nRF,
	nRF_READ_SUCCESSFUL,
	nRF_READ_FAILURE,
        nRF_SETUP_SUCCESSFUL,
        PAYLOAD_READ_SUCCESSFUL
} errors;

#define RESET_nRF_Modules() reset_all_registers(SPI1);\
                            reset_all_registers(SPI0)


/* Function: Send_Read_Write_Command(void *spi, uint8_t *cmd)
 * Parameters: Command byte that has to be sent to the nRF module.
 * This could be either for reading or writing.
 * Return: Value returned by the nRF module
 * Description: Send the command byte to the nRF module and return
 * the value that MISO pushes back into the Rx Buffer.
 */
uint8_t Send_Read_Write_Command(void *spi, uint8_t *cmd);

uint8_t Send_Read_Write_Command_SPI1(uint8_t *cmd);

/*Function: Send_Write_Value(uint8_t write_value)
 * Parameters: value that has to be written to the nRF register.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: Send the write value to the respective nRF register.
 * XXX: Please note that this function must be preceded by Send_Read_Write_Command(*cmd)!
 * Failure to do this will result in an unexpected behavior.
 */
uint8_t Send_Write_Value(void *spi, uint8_t write_value);

uint8_t Send_Write_Value_SPI1(uint8_t write_value);

/*Function: Write_to_nRF(int8_t reg_value, reg_map reg);
 * Parameters: 
 *      a. reg_value: value that has to be written into the specified register
 *      b. reg_map reg: the register into which you want the value written
 * Return: a debug handle
 * Description: function to write a value into a given register
 */
int8_t Write_to_nRF(/*int8_t*/reg_map reg, int8_t *reg_value);

/* Function: Setup_nRF(void)
 * Parameters: void
 * Return: NULL
 * Description: used to do the prelimary setup prcedueres for the nRF
 *              TX and RX modules.
 */
errors Setup_nRF(void);

/* Function: Read_Rx_Payload(uint8_t length, uint8_t *data)
 * Parameters:
 *      a. length: the length of the data that you want to extract from the R_RX_PAYLOAD
 *      b. *data: the pointer where you want to store the read data.
 * Return: a handle that can be used for debugging.
 * Description: This function can be used to read the payload that has been
 *              transfered to the PTX module wirelessly.
 */
errors Read_Rx_Payload(uint8_t length, uint8_t *data); 

void setup_begin_config(); 

void setup_nRF_radio();

void Flush_RX(void *spi);

void Flush_TX(void *spi);

uint8_t Abs_Write_5B_to_nRF_Register(void *spi, reg_map reg, uint8_t *value);

uint8_t Abs_Write_5B_to_nRF_Register_SPI1(reg_map reg, uint8_t *value);

void loop();

void reset_all_registers_SPI1(void);

void reset_all_registers(void *spi);

void Setup_PTX_Device();

void Setup_PRX_Device();

void Dump_SPI1_Reg(void);
void Dump_Reg(void *spi);


void setup_common_nRF_char(void);

void set_device_addr(void);

void Setup_TX(void);

void config_tx_addr();
void config_rx_addr();

void fill_tx_buffer(uint8_t *data);

void nrf_Config_PTX_PRX();

#endif /* INCLUDES_NRF_H_ */
