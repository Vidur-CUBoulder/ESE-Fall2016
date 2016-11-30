/*
 * eeprom.c
 *
 *  Created on: Nov 24, 2016
 *      Author: vidur
 */

#include "eeprom.h"
#include "uart.h"

#define DEBUG

uint8_t Send_EEPROM_Read_Write(uint8_t cmd)
{
    uint8_t ret_value = 0;

    while(WAIT_FOR_SPTEF_SPI1);
    SPI1->D = cmd;
    while(WAIT_FOR_SPRF_SPI1);
    ret_value = SPI1->D;

    return ret_value;
}


eeprom_errors Read_Status(uint8_t *read_status_value)
{
    if(read_status_value == NULL) {
        return RETURN_NULL;
    }

    uint8_t return_nRF_value = 0;
    uint8_t ret_value = 0;

    //Pull the CS low first!
    Pull_CS_Low_SPI1();

    Send_EEPROM_Read_Write(RDSR);
    /*while(WAIT_FOR_SPTEF_SPI1);
    SPI1->D = 0x05;
    while(WAIT_FOR_SPRF_SPI1);
    ret_value = SPI1->D;*/


    *read_status_value = Send_EEPROM_Read_Write(0xFF);
    /*while(WAIT_FOR_SPTEF_SPI1);
    SPI1->D = 0xFF;
    while(WAIT_FOR_SPRF_SPI1);
    ret_value = SPI1->D;*/
    
    //Pull the CS high!
    Pull_CS_High_SPI1();
  
    //don't be cheeky!!
    *read_status_value <<= 1;

    return EEPROM_READ_SUCCESSFUL;

}

eeprom_errors Enable_Write_Latch()
{
    uint8_t ret_value = 0;

    Pull_CS_Low_SPI1();
    Send_EEPROM_Read_Write(WREN);
    Pull_CS_High_SPI1();
   
    //delay(20);

    Pull_CS_Low_SPI1();
    Send_EEPROM_Read_Write(WRSR);
    Pull_CS_High_SPI1();

    uint8_t read_value = 0;
    Read_Status(&read_value);
    
    return CHK_WEL_SET(read_value);
}

eeprom_errors Disable_Write_Latch()
{
    Pull_CS_Low_SPI1();
    Send_EEPROM_Read_Write(WRDI);
    Pull_CS_High_SPI1();

    uint8_t read_value = 0;
    Read_Status(&read_value);

    return CHK_WEL_UNSET(read_value);
}

eeprom_errors Write_Data_to_EEPROM(uint8_t data, uint8_t *address)
{
    if(address == NULL) {
        return RETURN_NULL;
    }

    /* Check if the WEL latch is set
     * if not, then set it before proceeding.
     */
    uint8_t status_read = 0;
    Read_Status(&status_read);
    if(CHK_WEL_SET(status_read) == WEL_SET_FAILURE) {
        Enable_Write_Latch();
    }
    
    //Send the WRITE instruction..

    Pull_CS_Low_SPI1();

    Send_EEPROM_Read_Write(WRITE);

    //Next, send the byte address

    Send_EEPROM_Read_Write(*address);

    //Lastly, send the byte that you want to write to it..

    Send_EEPROM_Read_Write(data);

    Pull_CS_High_SPI1();

    // Need to disable write ops before exiting...
    Disable_Write_Latch();
    
    return 0;

}

eeprom_errors Read_Data_from_EEPROM(uint8_t *starting_address)
{
    if(starting_address == NULL) {
        return RETURN_NULL;
    }

    //Check if the WEL latch is disabled!
    uint8_t status_read = 0;
    Read_Status(&status_read);
    if(CHK_WEL_SET(status_read) == WEL_SET_SUCCESS) {
        Disable_Write_Latch();
    }

    uint8_t read_value = 0;

    Pull_CS_Low_SPI1();

    Send_EEPROM_Read_Write(READ);

    Send_EEPROM_Read_Write(*starting_address);

    read_value = Send_EEPROM_Read_Write(NOP);

    //don't be cheeky!!
    read_value <<= 1;

    return 0;

}

