/*
 * eeprom.c
 *
 *  Created on: Nov 24, 2016
 *      Author: vidur
 */

#include "eeprom.h"
#include "uart.h"

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

    uint8_t return_nRF_value = 0;
    uint8_t ret_value = 0;

    //Pull the CS low first!
    Pull_CS_Low_SPI1();

    //*read_status_value = Send_EEPROM_Read_Write(RDSR);

    while(!(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK));
    SPI1->D = RDSR;
    while(!(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK));
    *read_status_value = SPI1->D;
    
    //Pull the CS high!
    Pull_CS_High_SPI1();
    
    return EEPROM_READ_SUCCESSFUL;

}

eeprom_errors Check_Write_Status(void)
{
    uint8_t get_status = 0;
    Read_Status(&get_status);

    /* Check if the RDY bit & the WEL bit is 0 */
    if (get_status & 0x02) {
        return READY_TO_WRITE;
    }
    if( (get_status & 0x01) ) {
        /* One of the bits is set
         * Can't write now; return*/
        return NOT_READY_TO_WRITE;
    }

    return READY_TO_WRITE;
}

eeprom_errors Enable_Write_Ops(void)
{
    /*1. Send the WREN instruction to the EEPROM */
    Send_EEPROM_Read_Write(WREN);

    /* 2. Check the write status to make sure that all is ok */
    eeprom_errors check_write = Check_Write_Status();
    if(check_write == NOT_READY_TO_WRITE) {
        return NOT_READY_TO_WRITE;
    }

    /* 3. Make CSN Low to start writing */
   
    return WRITE_OPS_ENABLED;
}

eeprom_errors Disable_Write_Ops(void)
{
    /* 1. Send the WRDI instruction */
    Send_EEPROM_Read_Write(WRDI);

    eeprom_errors check_write = Check_Write_Status();
    if( check_write == NOT_READY_TO_WRITE) {
        return WRITE_OPS_DISABLED;
    }

    return UNKNOWN_FAILURE;
}






