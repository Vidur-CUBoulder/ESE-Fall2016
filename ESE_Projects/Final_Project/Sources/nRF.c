/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

#define DEBUG

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

#ifdef DEBUG
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register_SPI1(CONFIG, &reg_value);
    Read_from_nRF_Register_SPI1(EN_AA, &reg_value);
    Read_from_nRF_Register_SPI1(EN_RXADDR, &reg_value);
    Read_from_nRF_Register_SPI1(SETUP_AW, &reg_value);
    Read_from_nRF_Register_SPI1(SETUP_RETR, &reg_value);
    Read_from_nRF_Register_SPI1(RF_CH, &reg_value);
    Read_from_nRF_Register_SPI1(RF_SETUP, &reg_value);
    Read_from_nRF_Register_SPI1(STATUS, &reg_value);

    Read_5_Bytes_SPI1(RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes_SPI1(RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes_SPI1(TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register_SPI1(RX_PW_P0, &reg_value);
    Read_from_nRF_Register_SPI1(RX_PW_P1, &reg_value);
#endif

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

#ifdef DEBUG
    uint8_t reg_value = 0;
    uint8_t ret_value[5] = {0};

    Read_from_nRF_Register(CONFIG, &reg_value);
    Read_from_nRF_Register(EN_AA, &reg_value);
    Read_from_nRF_Register(EN_RXADDR, &reg_value);
    Read_from_nRF_Register(SETUP_AW, &reg_value);
    Read_from_nRF_Register(SETUP_RETR, &reg_value);
    Read_from_nRF_Register(RF_CH, &reg_value);
    Read_from_nRF_Register(RF_SETUP, &reg_value);
    Read_from_nRF_Register(STATUS, &reg_value);

    Read_5_Bytes(RX_ADDR_P0, &ret_value[0]);
    Read_5_Bytes(RX_ADDR_P1, &ret_value[0]);
    Read_5_Bytes(TX_ADDR, &ret_value[0]);

    Read_from_nRF_Register(RX_PW_P0, &reg_value);
    Read_from_nRF_Register(RX_PW_P1, &reg_value);
#endif

}


int8_t Flush_TX(void)
{
    Pull_CS_Low();
   
    uint8_t cmd = FLUSH_TX;
    Send_Read_Write_Command(&cmd);
    delay(10);
    
    Pull_CS_High();
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

    Abs_Write_to_nRF_Register(RX_PW_P1, 0x20);
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
    Abs_Write_to_nRF_Register(RF_SETUP, 0x60); /*RF_DR_HIGH = b'0; RF_PWR = b'11*/
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


