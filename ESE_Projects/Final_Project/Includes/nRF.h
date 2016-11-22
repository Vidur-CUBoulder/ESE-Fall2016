/*
 * nRF.h
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_NRF_H_
#define INCLUDES_NRF_H_

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

/*Function: Send_Write_Value(uint8_t write_value)
 * Parameters: value that has to be written to the nRF register.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: Send the write value to the respective nRF register.
 * XXX: Please note that this function must be preceded by Send_Read_Write_Command(*cmd)!
 * Failure to do this will result in an unexpected behavior.
 */
uint8_t Send_Write_Value(uint8_t write_value);

/*Function:(*ops_type)(int8_t, reg_map)
 * Parameters: 
 *      a. int8_t value: takes a value to be read/written to the register.
 *      b. reg_map reg: a particular register to work upon.
 * Return: could return a debug handle
 * Description: a function pointer to a particular function. Can be used to call
 *              functions to read from or write to a particular register in the nRF.
 */
int8_t (*ops_type)(int8_t, reg_map);

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
int8_t nRF_ops(int8_t (*ops_type)(int8_t, reg_map), int8_t reg_value, reg_map reg);

/*Function: Write_to_nRF(int8_t reg_value, reg_map reg);
 * Parameters: 
 *      a. reg_value: value that has to be written into the specified register
 *      b. reg_map reg: the register into which you want the value written
 * Return: a debug handle
 * Description: function to write a value into a given register
 */
int8_t Write_to_nRF(int8_t reg_value, /*int8_t*/reg_map reg);

/*Function:Read_from_nRF(int8_t reg_value, reg_map reg)
 * Parameters:
 *      a. reg_value: value that has been read from the given register
 *      b. reg_map reg: register whose value you want to read.
 * Return: a debug handle
 * Description: function to read the value stored in the register.
 */
int8_t Read_from_nRF(int8_t reg_value, reg_map reg);


#endif /* INCLUDES_NRF_H_ */
