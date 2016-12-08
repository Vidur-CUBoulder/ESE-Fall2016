/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

errors reset_all_registers(void *spi)
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

errors Dump_Reg(void *spi)
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

uint8_t Send_Write_Value(void *spi, uint8_t write_value)
{
    uint8_t ret_value = 0;
    if(spi == SPI0) {
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI0) = write_value;
        while(WAIT_FOR_SPRF(spi));
        ret_value = SPI_D_REG(SPI0);
    } else {
        while(WAIT_FOR_SPTEF(spi));
        SPI_D_REG(SPI1) = write_value;
        while(WAIT_FOR_SPRF(spi));
        ret_value = SPI_D_REG(SPI1);
    }
	return ret_value;
}

errors Abs_Write_5B_to_nRF_Register(void *spi, reg_map reg, uint8_t *value)
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

    return FIVE_BYTES_SUCCESSFULLY_WRITTEN;

}

nRF_Cluster *Alloc_nRF_Cluster()
{
    nRF_Cluster *cluster = malloc(sizeof(nRF_Cluster));
    
    cluster->Reset_Module = &reset_all_registers;
    cluster->Dump_Register_Values = &Dump_Reg;
    cluster->Config_Modules = &nrf_Config_PTX;
    cluster->fill_buffer = &fill_nRF_buffer;
    cluster->Activate_Modules = &Turn_On_Modules;
    cluster->Read_Payload_Buffer = &Read_Payload_Register_Value;
    cluster->Free_Cluster = &Free_nRF_Cluster;

    return cluster;
}

errors Free_nRF_Cluster(nRF_Cluster *cluster)
{
    if (cluster == NULL) {
        return NULL_FAILURE;
    }

    free(cluster);
    
    return CLUSTER_SPACE_CLEARED;
}

errors Read_Payload_Register_Value(void *spi, nRF_Cluster *new_cluster, uint8_t *data,\
                                        uint8_t len)
{
    if( data == NULL ) {
        return NULL_FAILURE;
    }

    /* Turn-Off the Modules! */
    new_cluster->Activate_Modules = &Turn_Off_Modules;
    new_cluster->Activate_Modules(SPI1, SPI0);
    
    /* Debug -- Dump all Register values! */
    new_cluster->Dump_Register_Values(SPI0);
    new_cluster->Dump_Register_Values(SPI1);
   
    /* Read the data from the RX Buffer */
    //uint8_t data_read[4] = {0};
    Read_RX_Payload(spi, data, len);
    
    return 0;
}

errors init_nRF_modules(nRF_Cluster *new_cluster, nRF_Values *PTX_Config_Data,\
                            nRF_Values *PRX_Config_Data)
{
    errors debug_handle = 0;

    /* Reset both modules before beginning */
    new_cluster->Reset_Module(PTX_Config_Data->spi_number);
    new_cluster->Reset_Module(PRX_Config_Data->spi_number);

    /*Config the modules with the new configs */
    
    /* PTX Config */
    new_cluster->Config_Modules = &nrf_Config_PTX;
    new_cluster->Config_Modules(*PTX_Config_Data);

    /* PRX Config */
    new_cluster->Config_Modules = &nrf_Config_PRX;
    new_cluster->Config_Modules(*PRX_Config_Data);

    return nRF_MODULES_SUCCESSFULLY_INIT;
}

errors nrf_Config_PRX(nRF_Values config_data)
{

    /*  Config Information:->
     *  RF_CH : Channel : 76
     *  RX_PW_P1 : Payload_Length: 4
     *  RF_SETUP : 1Mbps, TX gain: 0db - 0x06
     *  CONFIG :  CRC enabled, 1B CRC length - 0x08
     *  EN_AA : pipes 0 and 1 - 0x03
     *  EN_RXADDR : again pipes 0 and 1 - 0x03
     *  SETUP_RETR : 1000us and 15 re-trans trials - 0x4F
     *  disable DYNPD completely - 0x00
     *  Status register - 0x70
     */

    /* RF_CH */
    Abs_Write_to_nRF_Register(config_data.spi_number, RF_CH,\
                                config_data.set_RF_CH);

    /* RX_PW_P1 */
    Abs_Write_to_nRF_Register(config_data.spi_number, RX_PW_P1,\
                                config_data.set_RX_PW_P1);
    
    /* RF_SETUP */
    Abs_Write_to_nRF_Register(config_data.spi_number, RF_SETUP,\
                                config_data.set_RF_SETUP);

    /* CONFIG --> CRC en and 1B CRC len */
    Abs_Write_to_nRF_Register(config_data.spi_number, CONFIG,\
                                config_data.set_CONFIG);

    /* EN_AA --> pipes 0 and 1 */
    Abs_Write_to_nRF_Register(config_data.spi_number, EN_AA,\
                                config_data.set_EN_AA);

    /* EN_RXADDR */
    Abs_Write_to_nRF_Register(config_data.spi_number, EN_RXADDR,\
                                config_data.set_EN_RXADDR);

    /* SETUP_RETR */
    Abs_Write_to_nRF_Register(config_data.spi_number, SETUP_RETR,\
                                config_data.set_SETUP_RETR);
    
    /* Disable DYNPD */
    Abs_Write_to_nRF_Register(config_data.spi_number, DYNPD,\
                                config_data.set_DYNPD);

    /* Flush the TX and RX for the PRX */
    Flush_RX(config_data.spi_number);
    Flush_TX(config_data.spi_number);

    /* Next, clear the bits of the STATUS register */
    Write_to_nRF_Register(config_data.spi_number, STATUS,\
                                config_data.set_STATUS);

    /* Do the address configuration now! */
    config_rx_addr(config_data);

    return PRX_CONFIG_SUCCESSFUL;

}

errors nrf_Config_PTX(nRF_Values config_data)
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
    Abs_Write_to_nRF_Register(config_data.spi_number, RF_CH,\
                                config_data.set_RF_CH);
    /* RX_PW_P1 */
    Abs_Write_to_nRF_Register(config_data.spi_number, RX_PW_P1,\
                                config_data.set_RX_PW_P1);

    /* RF_SETUP */
    Abs_Write_to_nRF_Register(config_data.spi_number, RF_SETUP,\
                                config_data.set_RF_SETUP);

    /* CONFIG --> CRC en and 1B CRC len */
    Abs_Write_to_nRF_Register(config_data.spi_number, CONFIG,\
                                config_data.set_CONFIG);
   
    /* EN_AA --> pipes 0 and 1 */
    Abs_Write_to_nRF_Register(config_data.spi_number, EN_AA,\
                                config_data.set_EN_AA);

    /* EN_RXADDR */
    Abs_Write_to_nRF_Register(config_data.spi_number, EN_RXADDR,\
                                config_data.set_EN_RXADDR);

    /* SETUP_RETR */
    Abs_Write_to_nRF_Register(config_data.spi_number, SETUP_RETR,\
                                config_data.set_SETUP_RETR);

    /* Disable DYNPD */
    Abs_Write_to_nRF_Register(config_data.spi_number, DYNPD,\
                                config_data.set_DYNPD);
    
    /* Flush the TX and RX for the PTX */
    Flush_RX(config_data.spi_number);
    Flush_TX(config_data.spi_number);

    /* Next, clear the bits of the STATUS register */
    Write_to_nRF_Register(config_data.spi_number, STATUS,\
                                config_data.set_STATUS);

    /* Do the address configuration now! */
    config_tx_addr(config_data);

    return PTX_CONFIG_SUCCESSFUL;
}

void config_tx_addr(nRF_Values config_data)
{
    /* RX_ADDR_P0 must be set to the sending address for the auto ack to work! */
    uint8_t ret_value[5] = {0};

    Abs_Write_5B_to_nRF_Register(config_data.spi_number, RX_ADDR_P0,\
                                    &config_data.set_RX_ADDR_P0[0]);
    
    Abs_Write_5B_to_nRF_Register(config_data.spi_number, TX_ADDR,\
                                    &config_data.set_TX_ADDR[0]);

    Abs_Write_5B_to_nRF_Register(config_data.spi_number, RX_ADDR_P1,\
                                    &config_data.set_RX_ADDR_P1[0]);
}

void config_rx_addr(nRF_Values config_data)
{
    uint8_t ret_value[5] = {0};

    Abs_Write_5B_to_nRF_Register(config_data.spi_number, RX_ADDR_P0,\
                                    &config_data.set_RX_ADDR_P0[0]);
    
    Abs_Write_5B_to_nRF_Register(config_data.spi_number, TX_ADDR,\
                                    &config_data.set_TX_ADDR[0]);

    //uint8_t value_1[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(config_data.spi_number, RX_ADDR_P1,\
                                    &config_data.set_RX_ADDR_P1[0]);
}

errors fill_nRF_buffer(void *spi, uint8_t *data, uint8_t length)
{
    //Write to the TX payload!
    Pull_CS_Low(spi);
    
    uint8_t cmd = W_TX_PAYLOAD;
    Send_Read_Write_Command(spi, &cmd);
    
    delay(10);

    //Now start pushing the data into the payload buffer
    while(length) {
        Send_Write_Value(spi, *(data++));
        length--;
    }
    
    Pull_CS_High(spi);

    return BUFFER_FILLED;
}

errors Turn_On_Modules(void *SPI_RX/*SPI1*/, void *SPI_TX/*SPI0*/)
{
    /* Write to the CONFIG register to reset the interrupts
     * and to config the TX/RX modules accordingly
     */
    uint8_t reg_value = 0;
    
    Write_to_nRF_Register(SPI_RX, CONFIG, 0x03); //PRX
    Read_from_nRF_Register(SPI_RX, CONFIG, &reg_value);
    
    Write_to_nRF_Register(SPI_TX, CONFIG, 0x02); //PTX
    Read_from_nRF_Register(SPI_TX, CONFIG, &reg_value);

    /* Prevent any other SPI operations */
    Pull_CS_High(SPI_RX);
    Pull_CS_High(SPI_TX);

    /* Launch!! */
    CE_High(SPI_RX);
    CE_High(SPI_TX);

    return nRF_MODULES_ON;
}

errors Turn_Off_Modules(void *SPI_RX/*SPI1*/, void *SPI_TX/*SPI0*/)
{

    if(SPI_RX == NULL || SPI_TX == NULL) {
        return NULL_FAILURE;
    }

    /* Just disable the Chip Select */ 
    CE_Low(SPI_RX);
    CE_Low(SPI_TX);

    return nRF_MODULES_OFF;

}

errors Read_RX_Payload(void *spi, uint8_t *read_data, uint8_t len)
{
    Pull_CS_Low(spi);
    
    uint8_t cmd = R_RX_PAYLOAD;
    Send_Read_Write_Command(spi, &cmd);
    
    delay(10);
   
    cmd = NOP;
    while(len) {
        *(read_data++) = Send_Read_Write_Command(spi, &cmd);
        len--;
    }

    Pull_CS_High(spi);

}



