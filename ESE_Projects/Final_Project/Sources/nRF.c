/*
 * nRF.c
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#include "spi_masks.h"
#include "spi.h"

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

int8_t Read_from_nRF(reg_map reg, int8_t *reg_value)
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

uint8_t Send_Write_Value(uint8_t write_value)
{
	uint8_t ret_value = 0;

	while(WAIT_FOR_SPTEF);
	SPI0->D = write_value;
	while(WAIT_FOR_SPRF);
	ret_value = SPI0->D;

	return ret_value;
}

int8_t Abs_Write_5B_to_nRF_Register(reg_map reg, uint8_t *value)
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
    }

    return 1;
}


void loop()
{
    if(data_available()) {
        MY_LOG("BOGUS_LOG!\n");
    }

    return;
}


