/*
 * eeprom.h
 *
 *  Created on: Nov 24, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_EEPROM_H_
#define INCLUDES_EEPROM_H_

#include "stdint.h"
#include "spi_masks.h"

/* CAT25010 SPI Operated EEPROM */

typedef enum eeprom_errors_e {
    //Generic debug flags
    UNKNOWN_FAILURE,
    RETURN_NULL, 
    
    NOT_READY_TO_WRITE,
    READY_TO_WRITE,
    
    //Read_Status
    EEPROM_READ_SUCCESSFUL,
    
    //Enable_Write_Latch
    WEL_SET_FAILURE,
    WEL_SET_SUCCESS,
    
    //Disable_Write_Latch
    WEL_UNSET_FAILURE,
    WEL_UNSET_SUCCESS,

    //Write_Page_Data_to_EEPROM
    INVALID_DATA_WRITE_LENGTH,
    PAGE_WRITE_SUCCESSFUL,

    //Read_Page_Data_from_EEPROM
    PAGE_READ_SUCCESSFUL
} eeprom_errors;


#define CHK_WEL_SET(val) ((val & 0x02) ? WEL_SET_SUCCESS : \
                                WEL_SET_FAILURE)
#define CHK_WEL_UNSET(val) ((!(val & 0x02)) ? WEL_UNSET_SUCCESS : \
                                WEL_UNSET_FAILURE)

/* *********************************
 * Instruction Set for the CAT25010 
 * *********************************
 */

typedef enum eeprom_instrctions_t {
    WREN        =  0x06, 
    WRDI        =  0x04,  
    RDSR        =  0x05,
    WRSR        =  0x01,
    READ        =  0x03,
    WRITE       =  0x02
} eeprom_instructions;

/*Function: Send_EEPROM_Read_Write(uint8_t cmd)
 * Parameters: take the input command that has to be passed to the 
 *             EEPROM. This can either be the opcode or any data that
 *             has to be written or read from the eeprom.
 * Return: returns the value that is shifted out from the 
 *         EEPROM IC.
 * Description: Function to read/write values to the eeprom.
 */
uint8_t Send_EEPROM_Read_Write(uint8_t cmd);

/*Function: Read_Status(uint8_t *read_status_value)
 * Parameters: var. in which you want to store the read value.
 * Return: a debug handle that can help in debugging.
 * Description: used to read the value from the status register.
 */
eeprom_errors Read_Status(uint8_t *read_status_value);

/* Function: Enable_Write(void)
 * Parameters: void
 * Return: a return handle for debugging purposes.
 * Description: Set the Write Enable Latch in the Status register.
 */
eeprom_errors Enable_Write_Latch(void);

/* Function: Disable_Write_Latch(void)
 * Parameter: void
 * Return: a handle that you can use for debugging.
 * Description: Used to Disable the Write Enable Latch in the Status 
 *              register. It is recommended that this function be called
 *              after every write opertation is completed.
 */
eeprom_errors Disable_Write_Latch(void);

/* Function: Write_Data_to_EEPROM(uint8_t data, uint8_t *address)
 * Parameters: 
 *      a. data: value that you want to write into the EEPROM memory.
 *      b. address: address in the EEPROM that you want to write to.
 * Return: a handle that you can use for debugging.
 * Description: Used to write data into the EEPROM memory.
 */
eeprom_errors Write_Data_to_EEPROM(uint8_t data, uint8_t *address);

/* Function: Read_Data_from_EEPROM(uint8_t *starting_address, uint8_t *data_ret)
 * Parameters: 
 *      a. starting_address: the address from which you want to read the data.
 *      b. data_ret: value that is read from the EEPROM memory.
 * Return: a handle that you can use for debugging.
 * Description: Used to read a byte of data from the EEPROM memory.
 */
eeprom_errors Read_Data_from_EEPROM(uint8_t *starting_address,\
                                    uint8_t *data_ret);

/* Function: Write_Page_Data_to_EEPROM(uint8_t *data, uint8_t *address,\
 *                                              uint8_t length)
 * Parameters:
 *      a. *data: data that you want to write into the EEPROM memory.
 *      b. *address: the address starting from which you want to write 
 *                   to the memory.
 *      c. length: the length of the data that you want to write into the memory.                    
 *                 Please note that no more that 16 bytes can be written into the                    
 *                 memory at any given point in time.
 * Return: a debug handle that can be used for debugging.
 * Description: Used to write at most 16B of data into the memory.
 */
eeprom_errors Write_Page_Data_to_EEPROM(uint8_t *data, uint8_t *address,\
                                        uint8_t length);

/* Function: Read_Page_Data_to_EEPROM(uint8_t *data, uint8_t *address,\
 *                                        uint8_t length)
 * Parameters:
 *      a. *data: the address starting from which you want to read from the memory. 
 *      b. *address: the address starting from which you want to read from the memory.
 *      c. length: the length of the data that you want to write into the memory.                    
 *                 Please note that no more that 16 bytes can be written into the                    
 *                 memory at any given point in time.
 * Return: a debug handle that can be used from debugging.
 * Description: Used to read at most 16B of data from the memory.
 */
eeprom_errors Read_Page_Data_from_EEPROM(uint8_t *data, uint8_t *starting_address,
                                            uint8_t length);


#endif /* INCLUDES_EEPROM_H_ */
