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
    WEL_UNSET_SUCCESS
} eeprom_errors;


#define CHK_WEL_SET(val) ((val & 0x02) ? WEL_SET_SUCCESS : \
                                WEL_SET_FAILURE)
#define CHK_WEL_UNSET(val) ((!(val & 0x02)) ? WEL_UNSET_SUCCESS : \
                                WEL_UNSET_FAILURE)

/* *********************************
 * Instruction Set for the CAT25010 
 * *********************************
 */

#define WREN    0x06 //Enable Write Ops
#define WRDI    0x04 //Disable Write Ops
#define RDSR    0x05 //Read the Status Register
#define WRSR    0x01 //Write to the Status Register
#define READ    0x03 //Read Data from the memory
#define WRITE   0x02 //Write Data to the memory
#define NOP     0xFF //Dummy to push the data out from the SPI

uint8_t Send_EEPROM_Read_Write(uint8_t cmd);

eeprom_errors Read_Status(uint8_t *read_status_value);

eeprom_errors Enable_Write_Latch(void);

eeprom_errors Check_Write_Status(void);

eeprom_errors Enable_Write_Ops(void);

eeprom_errors Disable_Write_Latch(void);

eeprom_errors Write_Data_to_EEPROM(uint8_t data, uint8_t *address);

eeprom_errors Read_Data_from_EEPROM(uint8_t *starting_address);

#endif /* INCLUDES_EEPROM_H_ */
