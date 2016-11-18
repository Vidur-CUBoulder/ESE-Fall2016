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



#endif /* INCLUDES_NRF_H_ */
