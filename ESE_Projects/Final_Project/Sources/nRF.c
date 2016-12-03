/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

/*void reset_all_registers(void *spi_type)
{
    uint8_t a = 0;
    if(spi_type == SPI0) {
        a = 4;
    } else if(spi_type == SPI1) {
        a = 7;
    }

}*/


/*
void reset_all_registers_SPI1(void)
{
    Abs_Write_to_nRF_Register(SPI1, CONFIG, 0x80);
    Abs_Write_to_nRF_Register(SPI1, EN_AA, 0x3F);
    Abs_Write_to_nRF_Register(SPI1, EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register(SPI1, SETUP_AW, 0x03);
    Abs_Write_to_nRF_Register(SPI1, SETUP_RETR, 0x03);
    Abs_Write_to_nRF_Register(SPI1, RF_CH, 0x02);
    Abs_Write_to_nRF_Register(SPI1, RF_SETUP, 0x0E);
    Abs_Write_to_nRF_Register(SPI1, STATUS, 0x7E);

    uint8_t value[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(SPI1, RX_ADDR_P0, &value[0]);

    uint8_t value_1[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};
    Abs_Write_5B_to_nRF_Register(SPI1, RX_ADDR_P1, &value_1[0]);

    uint8_t value_tx[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(SPI1, TX_ADDR, &value_tx[0]);

    Abs_Write_to_nRF_Register(SPI1, RX_PW_P0, 0x00);
    Abs_Write_to_nRF_Register(SPI1, RX_PW_P1, 0x00);

    //Read all in order to validate
    //Dump_SPI1_Reg();
}
*/

/*
void Dump_SPI1_Reg(void)
{
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register(SPI1, STATUS, &reg_value);
    Read_from_nRF_Register(SPI1, OBSERVE_TX, &reg_value);
    Read_from_nRF_Register(SPI1, FIFO_STATUS, &reg_value);
    Read_from_nRF_Register(SPI1, CONFIG, &reg_value);
    Read_from_nRF_Register(SPI1, EN_AA, &reg_value);
    Read_from_nRF_Register(SPI1, EN_RXADDR, &reg_value);
    Read_from_nRF_Register(SPI1, SETUP_AW, &reg_value);
    Read_from_nRF_Register(SPI1, SETUP_RETR, &reg_value);
    Read_from_nRF_Register(SPI1, RF_CH, &reg_value);
    Read_from_nRF_Register(SPI1, RF_SETUP, &reg_value);
    Read_from_nRF_Register(SPI1, DYNPD, &reg_value);

    Read_5_Bytes(SPI1, RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes(SPI1, RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes(SPI1, TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register(SPI1, RX_PW_P0, &reg_value);
    Read_from_nRF_Register(SPI1, RX_PW_P1, &reg_value);
    Read_from_nRF_Register(SPI1, RX_PW_P2, &reg_value);
    Read_from_nRF_Register(SPI1, RX_PW_P3, &reg_value);
    Read_from_nRF_Register(SPI1, RX_PW_P4, &reg_value);
    Read_from_nRF_Register(SPI1, RX_PW_P5, &reg_value);
}
*/

void reset_all_registers(void *spi)
{
    Abs_Write_to_nRF_Register(spi, CONFIG, 0x80);
    Abs_Write_to_nRF_Register(spi, EN_AA, 0x3F);
    Abs_Write_to_nRF_Register(spi, EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register(spi, SETUP_AW, 0x03);
    Abs_Write_to_nRF_Register(spi, SETUP_RETR, 0x03);
    Abs_Write_to_nRF_Register(spi, RF_CH, 0x02);
    Abs_Write_to_nRF_Register(spi, RF_SETUP, 0x0E);
    Abs_Write_to_nRF_Register(spi, STATUS, 0x7E);

    uint8_t value[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(spi, RX_ADDR_P0, &value[0]);

    uint8_t value_1[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};
    Abs_Write_5B_to_nRF_Register(spi, RX_ADDR_P1, &value_1[0]);

    uint8_t value_tx[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(spi, TX_ADDR, &value_tx[0]);

    Abs_Write_to_nRF_Register(spi, RX_PW_P0, 0x00);
    Abs_Write_to_nRF_Register(spi, RX_PW_P1, 0x00);

    /* Read all in order to validate */
    //Dump_SPI0_Reg();

}

void Dump_Reg(void *spi)
{
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register(spi, STATUS, &reg_value);
    Read_from_nRF_Register(spi, OBSERVE_TX, &reg_value);
    Read_from_nRF_Register(spi, FIFO_STATUS, &reg_value);
    Read_from_nRF_Register(spi, CONFIG, &reg_value);
    Read_from_nRF_Register(spi, EN_AA, &reg_value);
    Read_from_nRF_Register(spi, EN_RXADDR, &reg_value);
    Read_from_nRF_Register(spi, SETUP_AW, &reg_value);
    Read_from_nRF_Register(spi, SETUP_RETR, &reg_value);
    Read_from_nRF_Register(spi, RF_CH, &reg_value);
    Read_from_nRF_Register(spi, RF_SETUP, &reg_value);
    Read_from_nRF_Register(spi, DYNPD, &reg_value);

    Read_5_Bytes(spi, RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes(spi, RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes(spi, TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register(spi, RX_PW_P0, &reg_value);
    Read_from_nRF_Register(spi, RX_PW_P1, &reg_value);
    Read_from_nRF_Register(spi, RX_PW_P2, &reg_value);
    Read_from_nRF_Register(spi, RX_PW_P3, &reg_value);
    Read_from_nRF_Register(spi, RX_PW_P4, &reg_value);
    Read_from_nRF_Register(spi, RX_PW_P5, &reg_value);
}

/*
void Flush_TX_SPI1(void)
{
    Pull_CS_Low(SPI1);
   
    uint8_t cmd = FLUSH_TX;
    Send_Read_Write_Command_SPI1(&cmd);
    delay(10);
    
    Pull_CS_High(SPI1);
}
*/

void Flush_TX(void *spi)
{
    Pull_CS_Low(spi);
   
    uint8_t cmd = FLUSH_TX;
    Send_Read_Write_Command(spi, &cmd);
    delay(10);
    
    Pull_CS_High(spi);
}

void Flush_RX(void *spi)
{
    Pull_CS_Low(spi);
    
    uint8_t cmd = FLUSH_RX;
    Send_Read_Write_Command(spi, &cmd);
    delay(10);
    
    Pull_CS_High(spi);
}

/*
void Flush_RX_SPI1(void)
{
    Pull_CS_Low(SPI1);
    
    uint8_t cmd = FLUSH_RX;
    Send_Read_Write_Command_SPI1(&cmd);
    delay(10);
    
    Pull_CS_High(SPI1);
}
*/

uint8_t Send_Read_Write_Command(void *spi, uint8_t *cmd)
{
    uint8_t ret_value = 0;

    if (spi == SPI0) {
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI0) = *cmd;
        while(WAIT_FOR_SPRF(spi));
        ret_value = SPI_D_REG(SPI0);
    } else {
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI1) = *cmd;
        while(WAIT_FOR_SPRF(spi));
        ret_value = SPI_D_REG(SPI1);
    }

    return ret_value;
}
/*
uint8_t Send_Read_Write_Command_SPI1(uint8_t *cmd)
{
    uint8_t ret_value = 0;

    while(WAIT_FOR_SPTEF(SPI1));
    SPI1->D = *cmd;
    while(WAIT_FOR_SPRF(SPI1));
    ret_value = SPI1->D;

    return ret_value;
}
*/
uint8_t Send_Write_Value(void *spi, uint8_t write_value)
{
    uint8_t ret_value = 0;
    if(spi == SPI0) {
        //while(WAIT_FOR_SPTEF(spi));
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI0) = write_value;
        while(WAIT_FOR_SPRF_SPI0);
        ret_value = SPI_D_REG(SPI0);
    } else {
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI1) = write_value;
        while(WAIT_FOR_SPRF(spi));
        ret_value = SPI_D_REG(SPI1);
    }
	return ret_value;
}

/*
uint8_t Abs_Write_5B_to_nRF_Register_SPI1(reg_map reg, uint8_t *value)
{
    uint8_t *temp_value = value; 
    uint8_t reg_addr = 0;
    uint8_t len = 5;

    reg_addr = W_REGISTER | reg;

    Pull_CS_Low(SPI1);
    Send_Read_Write_Command_SPI1(&reg_addr);

    delay(10);

    while(len) {
        Send_Read_Write_Command_SPI1(temp_value++);
        len--;
    }
    Pull_CS_High(SPI1);

    return 0;

}
*/

uint8_t Abs_Write_5B_to_nRF_Register(void *spi, reg_map reg, uint8_t *value)
{
    uint8_t *temp_value = value; 
    uint8_t reg_addr = 0;
    uint8_t len = 5;

    reg_addr = W_REGISTER | reg;

    Pull_CS_Low(spi);
    Send_Read_Write_Command(spi, &reg_addr);

    delay(10);

    while(len) {
        Send_Write_Value(spi, *(temp_value++));
        len--;
    }
    Pull_CS_High(spi);

    return 0;

}

void nrf_Config_PTX_PRX()
{

    /*  Config Information:->
     *  RF_CH : Channel : 2 
     *  RX_PW_P1 : Payload_Length: 4
     *  RF_SETUP : 1Mbps, TX gain: 0db
     *  CONFIG :  CRC enabled, 1B CRC length
     *  EN_AA : pipes 0 and 1
     *  EN_RXADDR : again pipes 0 and 1
     *  SETUP_RETR : 1000us and 15 re-trans trials
     *  disable DYNPD completely
     */

    /* RF_CH */
    Abs_Write_to_nRF_Register(SPI0, RF_CH, 76);
    Abs_Write_to_nRF_Register(SPI1, RF_CH, 76);

    /* RX_PW_P1 */
    Abs_Write_to_nRF_Register(SPI0, RX_PW_P1, 4);
    Abs_Write_to_nRF_Register(SPI1, RX_PW_P1, 4);

    /* RF_SETUP */
    Abs_Write_to_nRF_Register(SPI0, RF_SETUP, 0x06);
    Abs_Write_to_nRF_Register(SPI1, RF_SETUP, 0x06);

    /* CONFIG --> CRC en and 1B CRC len */
    Abs_Write_to_nRF_Register(SPI0, CONFIG, 0x08);
    Abs_Write_to_nRF_Register(SPI1, CONFIG, 0x08);
   
    /* EN_AA --> pipes 0 and 1 */
    Abs_Write_to_nRF_Register(SPI0, EN_AA, 0x03);
    Abs_Write_to_nRF_Register(SPI1, EN_AA, 0x03);

    /* EN_RXADDR */
    Abs_Write_to_nRF_Register(SPI0, EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register(SPI1, EN_RXADDR, 0x03);

    /* SETUP_RETR */
    Abs_Write_to_nRF_Register(SPI0, SETUP_RETR, 0x4F);
    Abs_Write_to_nRF_Register(SPI1, SETUP_RETR, 0x4F);

    /* Disable DYNPD */
    Abs_Write_to_nRF_Register(SPI0, DYNPD, 0x00);
    Abs_Write_to_nRF_Register(SPI1, DYNPD, 0x00);
    
    /* Flush the TX and RX for the PTX */
    Flush_RX(SPI0);
    Flush_RX(SPI1);
    Flush_TX(SPI0);
    Flush_TX(SPI1);

    /* Next, clear the bits of the STATUS register */
    Write_to_nRF_Register(SPI0, STATUS, 0x70);
    Write_to_nRF_Register(SPI1, STATUS, 0x70);

}

void config_tx_addr()
{
    // First the TX addr.
    
    /* RX_ADDR_P0 must be set to the sending address for the auto ack to work! */
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };

    Abs_Write_5B_to_nRF_Register(SPI0, RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(SPI0, RX_ADDR_P0, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register(SPI0, TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(SPI0, TX_ADDR, &ret_value[0]);

    uint8_t value_1[5] = {0xd7, 0xd7, 0xd7, 0xd7, 0xd7};
    Abs_Write_5B_to_nRF_Register(SPI0, RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes(SPI0, RX_ADDR_P1, &ret_value[0]);
    
}

void config_rx_addr()
{
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xd7, 0xd7, 0xd7, 0xd7, 0xd7 };

    Abs_Write_5B_to_nRF_Register(SPI1, RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(SPI1, RX_ADDR_P0, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register(SPI1, TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(SPI1, TX_ADDR, &ret_value[0]);

    uint8_t value_1[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(SPI1, RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes(SPI1, RX_ADDR_P1, &ret_value[0]);
}

void fill_tx_buffer(uint8_t *data)
{
    //Write to the TX payload!
     
    Pull_CS_Low(SPI0);
    
    uint8_t cmd = W_TX_PAYLOAD;
    Send_Read_Write_Command(SPI0, &cmd);
    
    delay(10);

    //Now start pushing the data into the payload buffer!
    uint8_t i = 0;
    uint8_t len = 4;
    while(len) {
        Send_Write_Value(SPI0, *(data++));
        i++;
        len--;
    }
    
    Pull_CS_High(SPI0);

}

errors Setup_nRF(void)
{
    uint8_t reg_value = 0;
   
    //Disable the Chip Enable pins on both modules. 
    CE_Low(SPI1);
    CE_Low(SPI0);

    /* Make the CS pins on both modules high to prevent
     * inadvertent SPI read/writes.
     */
    Pull_CS_High(SPI1);
    Pull_CS_High(SPI0);

    RESET_nRF_Modules();

    nrf_Config_PTX_PRX();
    config_tx_addr();
    config_rx_addr();
    //fill_tx_buffer(&data[0]);
    
    /* Reset the interrupt bits in the CONFIG reg. 
     * in both TX and RX modules
     */
    Write_to_nRF_Register(SPI1, CONFIG, 0x03); //PRX
    Read_from_nRF_Register(SPI1, CONFIG, &reg_value);
    
    Write_to_nRF_Register(SPI0, CONFIG, 0x02); //PTX
    Read_from_nRF_Register(SPI0, CONFIG, &reg_value);

    return nRF_SETUP_SUCCESSFUL; 
}

errors Read_Rx_Payload(uint8_t length, uint8_t *data)
{
    Pull_CS_Low(SPI1);
    
    uint8_t cmd = R_RX_PAYLOAD;
    Send_Read_Write_Command(SPI1, &cmd);
    
    delay(10);
   
    cmd = NOP;
    
    while(length) {
        *(data++) = Send_Read_Write_Command(SPI1, &cmd);
        length--;
    }

    Pull_CS_High(SPI1);
    
    return PAYLOAD_READ_SUCCESSFUL; 
}




