/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"


#if 0
void trial_radio_config(void)
{
    /* 1. Select RX by setting the PRIM_PX to high */
    Abs_Write_to_nRF_Register(CONFIG, 0x01); //CRC:0 and PRIM_RX:1
    
    /* 2. Completely disable the AA feature */
    Abs_Write_to_nRF_Register(EN_AA, 0x00);

    /* 3. Setting the address width on RX_PW_P1(pipe 1) */
    Abs_Write_to_nRF_Register(RX_PW_P1, 0x20);

    /* 4. Set the freq. channel to rx over */
    Abs_Write_to_nRF_Register(RF_CH, 0x4C);

    /* 5. Select the data rate */
    Abs_Write_to_nRF_Register(RF_SETUP, 0x26);
}
#endif

void reset_all_registers_SPI1(void)
{
    Abs_Write_to_nRF_Register_SPI1(CONFIG, 0x80);
    Abs_Write_to_nRF_Register_SPI1(EN_AA, 0x3F);
    Abs_Write_to_nRF_Register_SPI1(EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register_SPI1(SETUP_AW, 0x03);
    Abs_Write_to_nRF_Register_SPI1(SETUP_RETR, 0x03);
    Abs_Write_to_nRF_Register_SPI1(RF_CH, 0x02);
    Abs_Write_to_nRF_Register_SPI1(RF_SETUP, 0x0E);
    Abs_Write_to_nRF_Register_SPI1(STATUS, 0x0E);

    uint8_t value[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P0, &value[0]);

    uint8_t value_1[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};
    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P1, &value_1[0]);

    uint8_t value_tx[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register_SPI1(TX_ADDR, &value_tx[0]);

    Abs_Write_to_nRF_Register_SPI1(RX_PW_P0, 0x00);
    Abs_Write_to_nRF_Register_SPI1(RX_PW_P1, 0x00);

    /* Read all in order to validate */
    //Dump_SPI1_Reg();
}

void Dump_SPI1_Reg(void)
{
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register_SPI1(STATUS, &reg_value);
    Read_from_nRF_Register_SPI1(OBSERVE_TX, &reg_value);
    Read_from_nRF_Register_SPI1(FIFO_STATUS, &reg_value);
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);
    Read_from_nRF_Register_SPI1(EN_AA, &reg_value);
    Read_from_nRF_Register_SPI1(EN_RXADDR, &reg_value);
    Read_from_nRF_Register_SPI1(SETUP_AW, &reg_value);
    Read_from_nRF_Register_SPI1(SETUP_RETR, &reg_value);
    Read_from_nRF_Register_SPI1(RF_CH, &reg_value);
    Read_from_nRF_Register_SPI1(RF_SETUP, &reg_value);
    Read_from_nRF_Register_SPI1(DYNPD, &reg_value);

    Read_5_Bytes_SPI1(RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes_SPI1(TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register_SPI1(RX_PW_P0, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P1, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P2, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P3, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P4, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P5, &reg_value);
}


void reset_all_registers_SPI0(void)
{
    Abs_Write_to_nRF_Register(CONFIG, 0x80);
    Abs_Write_to_nRF_Register(EN_AA, 0x3F);
    Abs_Write_to_nRF_Register(EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register(SETUP_AW, 0x03);
    Abs_Write_to_nRF_Register(SETUP_RETR, 0x03);
    Abs_Write_to_nRF_Register(RF_CH, 0x02);
    Abs_Write_to_nRF_Register(RF_SETUP, 0x0E);
    Abs_Write_to_nRF_Register(STATUS, 0x0E);

    uint8_t value[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P0, &value[0]);

    uint8_t value_1[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P1, &value_1[0]);

    uint8_t value_tx[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register(TX_ADDR, &value_tx[0]);

    Abs_Write_to_nRF_Register(RX_PW_P0, 0x00);
    Abs_Write_to_nRF_Register(RX_PW_P1, 0x00);

    /* Read all in order to validate */
    //Dump_SPI0_Reg();

}

void Dump_SPI0_Reg(void)
{
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register(STATUS, &reg_value);
    Read_from_nRF_Register(OBSERVE_TX, &reg_value);
    Read_from_nRF_Register(FIFO_STATUS, &reg_value);
    Read_from_nRF_Register(CONFIG, &reg_value);
    Read_from_nRF_Register(EN_AA, &reg_value);
    Read_from_nRF_Register(EN_RXADDR, &reg_value);
    Read_from_nRF_Register(SETUP_AW, &reg_value);
    Read_from_nRF_Register(SETUP_RETR, &reg_value);
    Read_from_nRF_Register(RF_CH, &reg_value);
    Read_from_nRF_Register(RF_SETUP, &reg_value);
    Read_from_nRF_Register(DYNPD, &reg_value);

    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes(RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register(RX_PW_P0, &reg_value);
    Read_from_nRF_Register(RX_PW_P1, &reg_value);
    Read_from_nRF_Register(RX_PW_P2, &reg_value);
    Read_from_nRF_Register(RX_PW_P3, &reg_value);
    Read_from_nRF_Register(RX_PW_P4, &reg_value);
    Read_from_nRF_Register(RX_PW_P5, &reg_value);
}

void Flush_TX_SPI1(void)
{
    Pull_CS_Low_SPI1();
   
    uint8_t cmd = FLUSH_TX;
    Send_Read_Write_Command_SPI1(&cmd);
    delay(10);
    
    Pull_CS_High_SPI1();
}

void Flush_TX_SPI0(void)
{
    Pull_CS_Low();
   
    uint8_t cmd = FLUSH_TX;
    Send_Read_Write_Command(&cmd);
    delay(10);
    
    Pull_CS_High();
}

void Flush_RX_SPI0(void)
{
    Pull_CS_Low();
    
    uint8_t cmd = FLUSH_RX;
    Send_Read_Write_Command(&cmd);
    delay(10);
    
    Pull_CS_High();
}

void Flush_RX_SPI1(void)
{
    Pull_CS_Low_SPI1();
    
    uint8_t cmd = FLUSH_RX;
    Send_Read_Write_Command_SPI1(&cmd);
    delay(10);
    
    Pull_CS_High_SPI1();
}

int8_t Flush_RX(void)
{
    Pull_CS_Low();
    
    uint8_t cmd = FLUSH_RX;
    Send_Read_Write_Command(&cmd);
    delay(10);
    
    Pull_CS_High();
}

int8_t Read_from_nRF(reg_map reg, uint8_t *reg_value)
{
    uint8_t reg_addr = 0;
    int8_t ret_debug_handle;

    reg_addr = R_REGISTER | reg;
    ret_debug_handle = Read_Single_Byte(&reg_addr, reg_value);
    MY_LOG_PARAMS("Read Operation Output: ", *reg_value);
    MY_LOG("\n");
    
    return ret_debug_handle;
}

uint8_t Send_Read_Write_Command(uint8_t *cmd)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = *cmd;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;
}

uint8_t Send_Read_Write_Command_SPI1(uint8_t *cmd)
{
    uint8_t ret_value = 0;

    while(WAIT_FOR_SPTEF_SPI1);
    SPI1->D = *cmd;
    while(WAIT_FOR_SPRF_SPI1);
    ret_value = SPI1->D;

    return ret_value;
}


/* please don't use this func.! It is redundant! */

uint8_t Send_Dummy_Byte(void)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = NOP;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;

}

uint8_t Send_Write_Value_SPI1(uint8_t write_value)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF_SPI1);
	SPI1->D = write_value;
	while(WAIT_FOR_SPRF_SPI1);
	ret_value = SPI1->D;

	return ret_value;
}

uint8_t Send_Write_Value(uint8_t write_value)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = write_value;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;
}

uint8_t Abs_Write_5B_to_nRF_Register_SPI1(reg_map reg, uint8_t *value)
{
    uint8_t *temp_value = value; 
    uint8_t reg_addr = 0;
    uint8_t len = 5;

    reg_addr = W_REGISTER | reg;

    Pull_CS_Low_SPI1();
    Send_Read_Write_Command_SPI1(&reg_addr);

    delay(10);

    while(len) {
        Send_Write_Value_SPI1(*(temp_value++));
        len--;
    }
    Pull_CS_High_SPI1();

    return 0;

}

uint8_t Abs_Write_5B_to_nRF_Register(reg_map reg, uint8_t *value)
{
    uint8_t *temp_value = value; 
    uint8_t reg_addr = 0;
    uint8_t len = 5;

    reg_addr = W_REGISTER | reg;

    Pull_CS_Low();
    Send_Read_Write_Command(&reg_addr);

    delay(10);

    while(len) {
        Send_Write_Value(*(temp_value++));
        len--;
    }
    Pull_CS_High();

    return 0;

}

/* << SPI 0 >> */
void nrf_Config_PTX()
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
    Abs_Write_to_nRF_Register(RF_CH, 2);
    Abs_Write_to_nRF_Register_SPI1(RF_CH, 2);

    /* RX_PW_P1 */
    Abs_Write_to_nRF_Register(RX_PW_P1, 4);
    Abs_Write_to_nRF_Register_SPI1(RX_PW_P1, 4);

    /* RF_SETUP */
    Abs_Write_to_nRF_Register(RF_SETUP, 0x06);
    Abs_Write_to_nRF_Register_SPI1(RF_SETUP, 0x06);

    /* CONFIG --> CRC en and 1B CRC len */
    Abs_Write_to_nRF_Register(CONFIG, 0x08);
    Abs_Write_to_nRF_Register_SPI1(CONFIG, 0x08);
   
    /* EN_AA --> pipes 0 and 1 */
    Abs_Write_to_nRF_Register(EN_AA, 0x03);
    Abs_Write_to_nRF_Register_SPI1(EN_AA, 0x03);

    /* EN_RXADDR */
    Abs_Write_to_nRF_Register(EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register_SPI1(EN_RXADDR, 0x03);

    /* SETUP_RETR */
    Abs_Write_to_nRF_Register(SETUP_RETR, 0x4F);
    Abs_Write_to_nRF_Register_SPI1(SETUP_RETR, 0x4F);

    /* Disable DYNPD */
    Abs_Write_to_nRF_Register(DYNPD, 0x00);
    Abs_Write_to_nRF_Register_SPI1(DYNPD, 0x00);
    
    //--------- end of TX config ---------------------

    /* Flush the TX and RX for the PTX */
    Flush_RX_SPI0();
    Flush_RX_SPI1();
    Flush_TX_SPI0();
    Flush_TX_SPI1();

    /* Next, clear the bits of the STATUS register */
    Write_to_nRF_Register(STATUS, 0x70);
    Write_to_nRF_Register_SPI1(STATUS, 0x70);


    /* << CRITICAL! >> */
    /* Make CE low; set the module as RX and power up the module; set CE high */
    //CE_SPI1_Low();
    //Write_to_nRF_Register(CONFIG, 0x03);
    //Write_to_nRF_Register_SPI1(CONFIG, 0x03);
    //CE_SPI1_High();
     
}

void config_tx_addr()
{
    // First the TX addr.
    
    /* RX_ADDR_P0 must be set to the sending address for the auto ack to work! */
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };

    Abs_Write_5B_to_nRF_Register(RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register(TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);

    uint8_t value_1[5] = {0xd7, 0xd7, 0xd7, 0xd7, 0xd7};
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes(RX_ADDR_P1, &ret_value[0]);
    
}

void config_rx_addr()
{
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xd7, 0xd7, 0xd7, 0xd7, 0xd7 };

    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P0, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register_SPI1(TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes_SPI1(TX_ADDR, &ret_value[0]);

    uint8_t value_1[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P1, &ret_value[0]);
}

void fill_tx_buffer()
{
    uint8_t data[4] = {0x00, 0xAA, 0x55, 0x01};
    
    //Write to the TX payload!
     
    Pull_CS_Low();
    
    uint8_t cmd = W_TX_PAYLOAD;
    Send_Read_Write_Command(&cmd);
    
    delay(10);

    //Now start pushing the data into the payload buffer!
    uint8_t i = 0;
    uint8_t len = 4;
    while(len) {
        Send_Write_Value(data[i]);
        i++;
        len--;
    }
    
    Pull_CS_High();

}



#if 0

/* Setup Common nRF Characteristics */
void setup_common_nRF_char(void)
{
    /* Channel: 2
     * Payload: 4
     */

	uint8_t reg_value = 0;

    /*1. Setup the RF channel */
    Abs_Write_to_nRF_Register(RF_CH, 2);
    Abs_Write_to_nRF_Register_SPI1(RF_CH, 2);
    Read_from_nRF_Register(RF_CH, &reg_value);

    /*2. Config the payload length on p1 */
    Abs_Write_to_nRF_Register(RX_PW_P1, 4);
    Abs_Write_to_nRF_Register_SPI1(RX_PW_P1, 4);
    Read_from_nRF_Register(RX_PW_P1, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P1, &reg_value);

    //Make sure that everything else is 0.
    Read_from_nRF_Register(RX_PW_P0, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P0, &reg_value);
    
    Read_from_nRF_Register(RX_PW_P2, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P2, &reg_value);
    
    Read_from_nRF_Register(RX_PW_P3, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P3, &reg_value);
    
    Read_from_nRF_Register(RX_PW_P4, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P4, &reg_value);
    
    Read_from_nRF_Register(RX_PW_P5, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P5, &reg_value);

    /* 3. 1Mbps and TX Gain: 0db */
    //Abs_Write_to_nRF_Register(RF_SETUP, 0x06);
    Abs_Write_to_nRF_Register(RF_SETUP, 0x26);
    //Abs_Write_to_nRF_Register_SPI1(RF_SETUP, 0x06);
    Read_from_nRF_Register(RF_SETUP, &reg_value);
    //Read_from_nRF_Register_SPI1(RF_SETUP, &reg_value);
   
    /* 4. Enable CRC, 1B */
    /*Abs_Write_to_nRF_Register(CONFIG, 0x08);
    Abs_Write_to_nRF_Register_SPI1(CONFIG, 0x08);
    Read_from_nRF_Register(CONFIG, &reg_value);
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);*/

    /* 5. EN_AA on pipes 0 & 1 */
    Abs_Write_to_nRF_Register(EN_AA, 0x00);
    Abs_Write_to_nRF_Register_SPI1(EN_AA, 0x00);
    Read_from_nRF_Register(EN_AA, &reg_value);
    Read_from_nRF_Register_SPI1(EN_AA, &reg_value);
    

    /* 6. Enable the RX_ADDR for pipes 0 & 1 */ 
    //Abs_Write_to_nRF_Register(EN_RXADDR, 0x03);
    Abs_Write_to_nRF_Register_SPI1(EN_RXADDR, 0x03);
    //Read_from_nRF_Register(EN_RXADDR, &reg_value);
    Read_from_nRF_Register_SPI1(EN_RXADDR, &reg_value);

    /* 7. 1000us and 15 retransmits */
    Abs_Write_to_nRF_Register(SETUP_RETR, 0x02);
    //Abs_Write_to_nRF_Register_SPI1(SETUP_RETR, 0x02);
    Read_from_nRF_Register(SETUP_RETR, &reg_value);
    //Read_from_nRF_Register_SPI1(SETUP_RETR, &reg_value);

    /* 8. Make sure that DYNPD is 0 */
    Abs_Write_to_nRF_Register(DYNPD, 0x00);
    Abs_Write_to_nRF_Register_SPI1(DYNPD, 0x00);
    Read_from_nRF_Register(DYNPD, &reg_value);
    Read_from_nRF_Register_SPI1(DYNPD, &reg_value);

    //------- Enable the RX module ------------

    /* 9. Flush the RX Register */
    Flush_RX_SPI1();

    /* 10. Write to the STATUS register */
    Write_to_nRF_Register(STATUS, 0x70);
    Write_to_nRF_Register_SPI1(STATUS, 0x70);
    Read_from_nRF_Register(STATUS, &reg_value);
    Read_from_nRF_Register_SPI1(STATUS, &reg_value);

    /* 11. Power up the RX transeiver */
    CE_SPI1_Low();

    Write_to_nRF_Register_SPI1(CONFIG, 0x03); 
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);

    CE_SPI1_High();

}

void set_device_addr(void)
{
    // For PTX -- SPI0
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };

    Abs_Write_5B_to_nRF_Register(RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register(TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);


    // For PRX -- SPI1
    CE_SPI1_Low();
    
    uint8_t value_1[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P1, &ret_value[0]);
    
    CE_SPI1_High();

}

void Setup_TX(void)
{
    uint8_t data_array[4] = {0x00, 0xAA, 0x55, 0x01}; 
    uint8_t reg_value = 0;

    CE_SPI1_Low();
    CE_SPI0_Low();

    //Setup TX module -- SPI0
    
    Abs_Write_to_nRF_Register(STATUS, 0x70);
    Read_from_nRF_Register(STATUS, &reg_value);

    /* Power up the PTX module */
    Write_to_nRF_Register(CONFIG, 0x02);
    Read_from_nRF_Register(CONFIG, &reg_value);

    Flush_TX();

    //Write to the TX payload!
     
    Pull_CS_Low();
    
    uint8_t cmd = W_TX_PAYLOAD;
    Send_Read_Write_Command(&cmd);
    
    delay(10);

    //Now start pushing the data into the payload buffer!
    uint8_t i = 0;
    uint8_t len = 4;
    while(len) {
        Send_Write_Value(data_array[i]);
        i++;
        len--;
    }
    
    Pull_CS_High();

    CE_SPI1_High();
    delay(20);
    CE_SPI0_High();
    delay(20);
    
    delay(200);

}

#endif

#if 0

/* Setup the PTX device 
 *       << SPI0>>
 */
void Setup_PTX_Device()
{
    uint8_t read_value = 0;
    uint8_t len = 5;

    Flush_TX(); //remove all data from the TX FIFO
    Abs_Write_to_nRF_Register(STATUS, 0x00);
    
    /* 0. Set the data rate at 1Mbps */
    //Abs_Write_to_nRF_Register(RF_SETUP, 0x0E);
    Abs_Write_to_nRF_Register(RF_SETUP, 0x0F);
    Read_from_nRF_Register(RF_SETUP, &read_value);
    
    /* 1. Set the CONFIG bit PRIM_RX low */
    Abs_Write_to_nRF_Register(CONFIG, 0x00);
    Read_from_nRF_Register(CONFIG, &read_value);
    
    //config data pipe 0 to rx ACK!
    Abs_Write_to_nRF_Register(EN_AA, 0x00); 
    Read_from_nRF_Register(CONFIG, &read_value);
    
    /* 2. Write to the TX_PLD using the W_TX_PAYLOAD command. 
     * Note that the CSN must be held low while writing data into the TX Buf.
     */
    Pull_CS_Low();
    
    uint8_t cmd = W_TX_PAYLOAD;
    Send_Read_Write_Command(&cmd);
    
    delay(10);

    //Now start pushing the data into the payload buffer!
    while(len) {
        Send_Write_Value(0xA0);
        len--;
    }
    
    Pull_CS_High();

    // Read the FIFO_STATUS reg. for testing
    Read_from_nRF_Register(FIFO_STATUS, &read_value);

    /* 3. Write the addresses 
     * TX_ADDR:         0xB3B4B5B6f1
     * RX_ADDR_P0:      0xB3B4B5B6f1
     */
   
    uint8_t ret_value[5] = {0};
    uint8_t rx_addr_val[] = { 0xb3, 0xb4, 0xb5, 0xb6, 0xf1 };
    //uint8_t rx_addr_val[] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };
    Abs_Write_5B_to_nRF_Register(TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);
    
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);
    
    //Just for fun.. count the number of lost packets
    Read_from_nRF_Register(OBSERVE_TX, &read_value);

    //Power up the module!
    Write_to_nRF_Register(CONFIG, 0x02);
    Read_from_nRF_Register(CONFIG, &read_value);

    //Lastly, raise the CE pin!
    CE_SPI0_High(); 

    delay(10);
}

/* Setup the PRX Device
 *  <<**** SPI1 ****>>
 */

void Setup_PRX_Device(void)
{
    uint8_t reg_value = 0;
    Abs_Write_to_nRF_Register(STATUS, 0x00);
    
    //0. Flush the RX Buffer!
    Flush_RX_SPI1();
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);

    //1. Set the PRIM_RX bit in the CONFIG reg.
    Abs_Write_to_nRF_Register_SPI1(CONFIG, 0x01);
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);
    
    //All data pipes that receive data should be enabled.
    //Enabling data pipes 0 and 1
    Abs_Write_to_nRF_Register_SPI1(EN_RXADDR, 0x03);
    Read_from_nRF_Register_SPI1(EN_RXADDR, &reg_value);

    //Also enable the AA on pipe0
    Abs_Write_to_nRF_Register_SPI1(EN_AA, 0x00);
    Read_from_nRF_Register_SPI1(EN_AA, &reg_value);
   
    //Write to the RX_ADDR_P5..
    uint8_t ret_value[5] = {0};
    uint8_t value_1[5] = {0xb3, 0xb4, 0xb5, 0xb6, 0xf1};
    //uint8_t value_1[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2};
    Abs_Write_5B_to_nRF_Register_SPI1(RX_ADDR_P1, &value_1[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P1, &ret_value[0]);
   
    //Power up the module!
    Write_to_nRF_Register_SPI1(CONFIG, 0x02);
    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);

    //Now, raise the CE pin for SPI1
    CE_SPI1_High();

    delay(10);
}







void setup_nRF_radio(void)
{
    /* This is bogus. Please remove post testing */
    int8_t reg_value = 0;
    
    MY_LOG("PongBack!\n");
    
    /* Set the CE pin as output */
    /*already handled in func. config_spi0_ce() */

    /* Set the CSN pin as output */
    /* already handle in spi_setup() */

    setup_begin_config();
    
    /* Set the number of retries */
    Write_to_nRF_Register(SETUP_RETR, 0xFF);
    Read_from_nRF(SETUP_RETR, &reg_value);

    /* Set the channel */
    Write_to_nRF_Register(RF_CH, 0x4C);
    Read_from_nRF(RF_CH, &reg_value);

    /* RF_SETUP; set PA_LOW */
    //Write_to_nRF_Register(0xFF, RF_SETUP);

    /* Open pipe 0 for writing */
    
    uint8_t ret_value[5] = {0};
    //uint8_t rx_addr_val[] = { 0xf0, 0xf0, 0xf0, 0xf0, 0xe1 };
    uint8_t rx_addr_val[] = { 0xf0, 0xf0, 0xf0, 0xf0, 0xd2 };
    
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P0, &rx_addr_val[0]);
    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);

    Abs_Write_5B_to_nRF_Register(TX_ADDR, &rx_addr_val[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);

    /* Condition the Rx pipe for a full 32B payload */
    Abs_Write_to_nRF_Register(RX_PW_P0, 0x20);
    Read_from_nRF(RX_PW_P0, &reg_value);

    /* Open pipe 1 for Reading */

    //uint8_t rx_addr_val[] = { 0xf0, 0xf0, 0xf0, 0xf0, 0xe1 };
    uint8_t rx_addr_val_1[] = { 0xf0, 0xf0, 0xf0, 0xf0, 0xe1 };
    
    Abs_Write_5B_to_nRF_Register(RX_ADDR_P1, &rx_addr_val_1[0]);
    Read_5_Bytes(RX_ADDR_P1, &ret_value[0]);

    //Abs_Write_to_nRF_Register(RX_PW_P1, 0x20);
    Abs_Write_to_nRF_Register(RX_PW_P1, 4);
    Read_from_nRF(RX_PW_P1, &reg_value);

    Write_to_nRF_Register(EN_RXADDR, 0x03);
    Read_from_nRF(EN_RXADDR, &reg_value);

    /* Now start the listening process!! */

    Write_to_nRF_Register(CONFIG, 0x03);  
    Read_from_nRF(CONFIG, &reg_value);

    /* Reset bits in the STATUS register */
    Write_to_nRF_Register(STATUS, 0x70); 
    Read_from_nRF(STATUS, &reg_value);

    /* Flush the Buffers! */
    Flush_RX();
    Flush_TX();

    /* Raise the CE! */
    pin6_CE_High();

    delay(120);

}

void setup_begin_config() 
{
    /* This var. is bogus. Please remove post testing */
    int8_t reg_value = 0;

    /* Set CE low */
    pin6_CE_Low();

    /* Set CSN high */
    Pull_CS_High();

    /* add a delay to give the radio some time to settle */
    delay(10); //arbitarily chosen value

    /* Write 0x4F to SETUP_RETR */
    Abs_Write_to_nRF_Register(SETUP_RETR, 0x4F);
    Read_from_nRF(SETUP_RETR, &reg_value);

    /* Config the value for RF_SETUP */
    /* This sets the data rate to 1Mbps */
    Abs_Write_to_nRF_Register(RF_SETUP, 0x06); /*RF_DR_HIGH = b'0; RF_PWR = b'11*/
    Read_from_nRF(RF_SETUP, &reg_value);

    /* Set the CRC */
    Write_to_nRF_Register(CONFIG, 0x0C);
    Read_from_nRF(CONFIG, &reg_value);

    /* Reset bits in the STATUS register */
    Write_to_nRF_Register(STATUS, 0x70); 
    Read_from_nRF(STATUS, &reg_value);

    /* Select the channel and write to RF_CH */
    Abs_Write_to_nRF_Register(RF_CH, 0x4C); 
    Read_from_nRF(RF_CH, &reg_value);

    /* Call the FLUSH commands */
    Flush_RX();
    Flush_TX();

    return;
}

int8_t data_available(void)
{
    int8_t status = 0;
    /* Get the contents of the Status register! */ 
    Read_from_nRF(STATUS, &status);
    
    uint8_t rx_in = status & 0x40; //wait for RX_DR to be set!!..

    if(rx_in) {
        MY_LOG("We're IN!!\n");
        return 1;
    }

    return 0;
}


void loop()
{
    if(data_available()) {
        MY_LOG("BOGUS_LOG!\n");
    }

    return;
}

#endif

