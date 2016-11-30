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
	nRF_READ_FAILURE
} errors;

typedef struct nRF_ops_t {
    reg_map nrf_register;
    int8_t reg_value;
    int8_t read_value;
    int8_t write_value;

    /*Function Pointers*/
    errors (*send_command)(uint8_t); 
    errors (*read_write_ops)(reg_map, uint8_t);

} nRF_ops;

/* Function: Send_Read_Write_Command(uint8_t *cmd)
 * Parameters: Command byte that has to be sent to the nRF module.
 * This could be either for reading or writing.
 * Return: Value returned by the nRF module
 * Description: Send the command byte to the nRF module and return
 * the value that MISO pushes back into the Rx Buffer.
 */
uint8_t Send_Read_Write_Command(uint8_t *cmd);

uint8_t Send_Read_Write_Command_SPI1(uint8_t *cmd);

/*Function: Send_Dummy_Byte(void)
 * Parameters: void
 * Return: Value returned by the nRF module
 * Description: Send the NOP byte to the nRF module to:
 * 	a. Get/read the value of the previous command
 * 	b. Get/read the value of the Status register.
 */
uint8_t Send_Dummy_Byte(void);

/*Function: Send_Write_Value(uint8_t write_value)
 * Parameters: value that has to be written to the nRF register.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: Send the write value to the respective nRF register.
 * XXX: Please note that this function must be preceded by Send_Read_Write_Command(*cmd)!
 * Failure to do this will result in an unexpected behavior.
 */
uint8_t Send_Write_Value(uint8_t write_value);

uint8_t Send_Write_Value_SPI1(uint8_t write_value);

/*Function:(*ops_type)(int8_t, reg_map)
 * Parameters: 
 *      a. int8_t value: takes a value to be read/written to the register.
 *      b. reg_map reg: a particular register to work upon.
 * Return: could return a debug handle
 * Description: a function pointer to a particular function. Can be used to call
 *              functions to read from or write to a particular register in the nRF.
 */
int8_t (*ops_type)(reg_map, int8_t *);

/*Function: nRF_ops(int8_t (*ops_type)(int8_t, reg_map), int8_t reg_value, reg_map reg)
 * Paramters:
 *      a. int8_t (*ops_type)(int8_t, reg_map): defines the function pointer type.
 *      b. int8_t reg_value: value to be written into the register
 *      c. reg_map reg: the register that has to be worked upon from the list of
 *                      ennumerated register maps.
 * Return: a debug message/output
 * Description: This is an aggregation function for the various types of read/write
 *              operations that can be performed on the nRF module.
 */
//int8_t nRF_ops(int8_t (*ops_type)(reg_map, int8_t *), reg_map reg, int8_t *reg_value);

/*Function: Write_to_nRF(int8_t reg_value, reg_map reg);
 * Parameters: 
 *      a. reg_value: value that has to be written into the specified register
 *      b. reg_map reg: the register into which you want the value written
 * Return: a debug handle
 * Description: function to write a value into a given register
 */
int8_t Write_to_nRF(/*int8_t*/reg_map reg, int8_t *reg_value);

/*Function:Read_from_nRF(reg_map reg, int8_t *reg_value)
 * Parameters:
 *      a. reg_value: value that has been read from the given register
 *      b. reg_map reg: register whose value you want to read.
 * Return: a debug handle
 * Description: function to read the value stored in the register.
 */
int8_t Read_from_nRF(reg_map reg, uint8_t *reg_value);

void setup_begin_config(); 

void setup_nRF_radio();

int8_t Flush_RX(void);
void Flush_RX_SPI1(void);

int8_t Flush_TX(void);

uint8_t Abs_Write_5B_to_nRF_Register(reg_map reg, uint8_t *value);

uint8_t Abs_Write_5B_to_nRF_Register_SPI1(reg_map reg, uint8_t *value);

void loop();

void reset_all_registers_SPI1(void);

void reset_all_registers_SPI0(void);

void Setup_PTX_Device();

void Setup_PRX_Device();

void Dump_SPI1_Reg(void);
void Dump_SPI0_Reg(void);


void setup_common_nRF_char(void);

void set_device_addr(void);

void Setup_TX(void);


#endif /* INCLUDES_NRF_H_ */
