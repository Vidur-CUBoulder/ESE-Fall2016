/*
 * eeprom.c
 *
 *  Created on: Nov 24, 2016
 *      Author: vidur
 */

#include "eeprom.h"
#include "uart.h"

#define DEBUG

uint8_t Send_EEPROM_Read_Write(eeprom_instructions cmd)
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
    uint8_t cmd = RDSR;

    //Pull the CS low first!
    Pull_CS_Low(SPI1);
    
    Send_EEPROM_Read_Write(RDSR);
    *read_status_value = Send_EEPROM_Read_Write(0xFF);

    //Pull the CS high!
    Pull_CS_High(SPI1);
  
    return EEPROM_READ_SUCCESSFUL;

}
eeprom_errors Enable_Write_Latch()
{
    uint8_t ret_value = 0;

    Pull_CS_Low(SPI1);
    Send_EEPROM_Read_Write(WREN);
    Pull_CS_High(SPI1);
   
    //delay(20);

    Pull_CS_Low(SPI1);
    Send_EEPROM_Read_Write(WRSR);
    Pull_CS_High(SPI1);

    uint8_t read_value = 0;
    Read_Status(&read_value);
    
    return CHK_WEL_SET(read_value);
}

eeprom_errors Disable_Write_Latch()
{
    Pull_CS_Low(SPI1);
    Send_EEPROM_Read_Write(WRDI);
    Pull_CS_High(SPI1);

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

    Pull_CS_Low(SPI1);

    Send_EEPROM_Read_Write(WRITE);

    //Next, send the byte address

    Send_EEPROM_Read_Write(*address);

    //Lastly, send the byte that you want to write to it..

    Send_EEPROM_Read_Write(data);

    Pull_CS_High(SPI1);

    // Need to disable write ops before exiting...
    Disable_Write_Latch();
    
    return 0;

}

eeprom_errors Write_Page_Data_to_EEPROM(uint8_t *data, uint8_t *address,\
                                        uint8_t length)
{
    if(address == NULL || data == NULL) {
        return RETURN_NULL;
    }

    if(length > 16) {
        return INVALID_DATA_WRITE_LENGTH;
    }

    //Check if the WEL latch is disabled!
    uint8_t status_read = 0;
    Read_Status(&status_read);
    if(CHK_WEL_SET(status_read) == WEL_SET_FAILURE) {
        Enable_Write_Latch();
    }

    Pull_CS_Low(SPI1);
   
    Send_EEPROM_Read_Write(WRITE);

    Send_EEPROM_Read_Write(*address);

    while(length) {
        Send_EEPROM_Read_Write(*(data++));
        length--;
    }

    Pull_CS_High(SPI1);

    // Need to disable write ops before exiting...
    Disable_Write_Latch();

    return PAGE_WRITE_SUCCESSFUL;

}

eeprom_errors Read_Page_Data_from_EEPROM(uint8_t *data, uint8_t *starting_address,\
                                            uint8_t length)
{

    if(data == NULL || starting_address == NULL) {
        return RETURN_NULL;
    }
    
    Pull_CS_Low(SPI1);

    Send_EEPROM_Read_Write(READ);

    Send_EEPROM_Read_Write(*starting_address);

    while(length) {
        *data = Send_EEPROM_Read_Write(NOP);
        
        *data <<= 1;
        data++;
        length--;
    }

    Pull_CS_High(SPI1);

    return PAGE_READ_SUCCESSFUL;
}


eeprom_errors Read_Data_from_EEPROM(uint8_t *starting_address,\
                                    uint8_t *data_ret)
{
    if(starting_address == NULL || data_ret == NULL) {
        return RETURN_NULL;
    }

    //Check if the WEL latch is disabled!
    uint8_t status_read = 0;
    Read_Status(&status_read);
    if(CHK_WEL_SET(status_read) == WEL_SET_SUCCESS) {
        Disable_Write_Latch();
    }

    uint8_t read_value = 0;

    Pull_CS_Low(SPI1);

    Send_EEPROM_Read_Write(READ);

    Send_EEPROM_Read_Write(*starting_address);

    read_value = Send_EEPROM_Read_Write(NOP);
    
    Pull_CS_High(SPI1);

    *data_ret = read_value;

    return 0;

}
