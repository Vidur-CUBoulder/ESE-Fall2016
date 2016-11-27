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
    UNKNOWN_FAILURE,
    RETURN_NULL, 
    NOT_READY_TO_WRITE,
    READY_TO_WRITE,
    WRITE_OPS_ENABLED,
    WRITE_OPS_DISABLED,
	EEPROM_READ_SUCCESSFUL
} eeprom_errors;

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

uint8_t Send_EEPROM_Read_Write(uint8_t cmd);

eeprom_errors Read_Status(uint8_t *read_status_value);

eeprom_errors Check_Write_Status(void);

eeprom_errors Enable_Write_Ops(void);

eeprom_errors Disable_Write_Ops(void);


#endif /* INCLUDES_EEPROM_H_ */
