/*
 * spi.c
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#include "spi.h"

/* Config. as master */
/* Pin config details:
 *     J2_10 - PTD3 - CE
 *     J1_06  - PTD4 - CSN
 *     J2_04  - PTD5 - SCK
 *     J2_17  - PTD6 - MOSI
 *     J2_19  - PTD7 - MISO
 */
void spi_1_init(void)
{
	/* Enable the clock gate for SPI1 */
	SIM_SCGC4 |= SET_SPI1_CLK_GATE;

	/* Enable the Clock Gate for PORTD */
	SIM_SCGC5 |= SET_CLK_GATE_PORT_D;

	/* Enable the ALT mux for the GPIO pins */
        PORTD_PCR3 = CONFIG_PORTD3_GPIO;        //Config as CE
        PORTD_PCR4 = CONFIG_PORTD4_GPIO;        //Config as CS
        PORTD_PCR5 = CONFIG_PORTD5_SPI_SCK;     //Config as SCK
        PORTD_PCR6 = CONFIG_PORTD6_SPI_MOSI;    //Config as MOSI
        PORTD_PCR7 = CONFIG_PORTD7_SPI_MISO;    //Config as MISO

	/* Config the direction of the GPIO PORTD4 & PORTD3 as output */
	GPIOD_PDDR = (CONFIG_PORTD4_DIR_OUT | CONFIG_PORTD3_DIR_OUT);

	/* Config the Baud Rate for SPI1 comm. */
	SPI_BR_REG(SPI1) = SPI1_BAUD_RATE;

	/*Config the C1 SPI1 register as master connection */
	SPI1->C1 = SPI1_C1_CONFIG;

        /* Pull the CS High Now! */
        Pull_CS_High_SPI1();
}

/* Config. as master */
/* Pin config details:
 *     J1_05  - PTC3 - (GPIO)CE
 *     J1_07  - PTC4 - (GPIO)CSN
 *     J1_09  - PTC5 - SCK
 *     J1_11  - PTC6 - MOSI
 *     J1_01  - PTC7 - MISO
 */
void spi_0_init(void)
{
	/* Enable the clock gate for SPI0 */
	SIM_SCGC4 |= SET_SPI0_CLK_GATE;

	/* Enable the clock gate for PORTC */
	SIM_SCGC5 |= SET_CLK_GATE_PORT_C;

	/* Enable the ALT mux for the GPIO pins */
        PORTC_PCR3 = CONFIG_PORTC3_GPIO;        //config as CE
        PORTC_PCR4 = CONFIG_PORTC4_GPIO;        //config as CSN
	PORTC_PCR5 = CONFIG_PORTC5_SPI_SCK;     //config as SCK
	PORTC_PCR6 = CONFIG_PORTC6_SPI_MOSI;    //config as MOSI
	PORTC_PCR7 = CONFIG_PORTC7_SPI_MISO;    //config as MISO

	/*Config direction of GPIO PORTC4 & PORTC3 as output*/
	GPIOC_PDDR |= (CONFIG_PORTC4_DIR_OUT | CONFIG_PORTC3_DIR_OUT);

	/*Config the Baud Rate for SPI0 comm.*/	
	SPI_BR_REG(SPI0) |= SPI0_BAUD_RATE;

	/* Config the C1 SPI0 register as the master connection */
	SPI0->C1 = SPI0_C1_CONFIG;
}

/*Config pin 19 as the CE*/
/*TODO: Needs to GO!! */
void config_spi0_CE(void)
{
    /*Enable the clock gate for PORTD */
    SIM_SCGC5 |= SET_CLK_GATE_PORT_D;
    
    /*Config PORTD_PCR4 as GPIO*/
    PORTD_PCR4 = CONFIG_PORTD4_GPIO;

    /* Config the direction of the GPIO PORTD4 as output */
    GPIOD_PDDR |= CONFIG_PORTD4_DIR_OUT;

}

void pin6_CE_High(void)
{
    Pull_CS_High_SPI1();
}

void pin6_CE_Low(void)
{
    Pull_CS_Low_SPI1();
}

#if 0
uint8_t Read_Single_Byte(uint8_t *cmd, uint8_t *ret_value)
{
	if (cmd == NULL) {
		return NULL_FAILURE;
	}

	*ret_value = Read_from_nRF_Register(cmd);

	if(ret_value!=NULL){
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}
}
#endif

#if 0
uint8_t Read_Single_Byte_SPI1(uint8_t *cmd, uint8_t *ret_value)
{
	if (cmd == NULL) {
		return NULL_FAILURE;
	}

	//*ret_value = Read_from_nRF_Register(cmd);
	
        Pull_CS_Low_SPI1();
	//Send_Read_Write_Command(reg_addr);

	while(WAIT_FOR_SPTEF_SPI1);
	SPI1->D = *cmd;
	while(WAIT_FOR_SPRF_SPI1);
	ret_value = SPI1->D;

	delay(10);

	//return_nRF_value = Send_Dummy_Byte();

	while(WAIT_FOR_SPTEF_SPI1);
	SPI1->D = NOP;
	while(WAIT_FOR_SPRF_SPI1);
	ret_value = SPI1->D;
	Pull_CS_High_SPI1();

	if(ret_value!=NULL){
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}
}
#endif

errors Read_5_Bytes(reg_map reg, uint8_t *ret_value)
{
	if (ret_value == NULL) {
		return NULL_FAILURE;
	}

	uint8_t cntr = 0;

        uint8_t cmd = R_REGISTER | reg;
        
        Pull_CS_Low();
        Send_Read_Write_Command(&cmd);
        
        delay(10);

	for(cntr = 0; cntr < MAX_REG_LENGTH; cntr++) {
            *(ret_value+cntr) = Send_Dummy_Byte();
        }

        Pull_CS_High();

	if(ret_value != NULL) {
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}
}

errors Read_5_Bytes_SPI1(reg_map reg, uint8_t *ret_value)
{
	uint8_t cntr = 0;
        uint8_t cmd = R_REGISTER | reg;

        Pull_CS_Low_SPI1();
        Send_Read_Write_Command_SPI1(&cmd);

        delay(10);

        cmd = NOP;
	for(cntr = 0; cntr < MAX_REG_LENGTH; cntr++) {
		//*(ret_value+cntr) = Read_from_nRF_Register_SPI1(reg, ret_value);
		*(ret_value+cntr) = Send_Read_Write_Command_SPI1(&cmd);
	}

        Pull_CS_High_SPI1();

	if(ret_value != NULL) {
		return nRF_READ_SUCCESSFUL;
	} else {
		return nRF_READ_FAILURE;
	}

}

uint8_t Read_from_nRF_Register_SPI1(reg_map reg, uint8_t *reg_value)
{

    uint8_t return_nRF_value = 0;
    uint8_t reg_addr = R_REGISTER | reg;

	Pull_CS_Low_SPI1();

	uint8_t ret_value = 0;

	while(!(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK));
	SPI1->D = reg_addr;
	while(!(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK));
	ret_value = SPI1->D;

	delay(10);

	//return_nRF_value = Send_Dummy_Byte();
	
	while(!(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK));
	SPI1->D = NOP;
	while(!(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK));
	*reg_value = SPI1->D;
	
	Pull_CS_High_SPI1();

	return *reg_value;

}

uint8_t Read_from_nRF_Register(reg_map reg, uint8_t *ret_value)
{
	uint8_t return_nRF_value = 0;
	uint8_t reg_addr = R_REGISTER | reg;
	
        Pull_CS_Low();
        Send_Read_Write_Command(&reg_addr);

	delay(10);

	*ret_value = Send_Dummy_Byte();
        Pull_CS_High();

	return *ret_value;

}

uint8_t Abs_Write_to_nRF_Register_SPI1(reg_map reg, uint8_t write_value)
{
    uint8_t return_nRF_value = 0;
    uint8_t final_write_value = 0;
    uint8_t reg_addr = 0;

    reg_addr = W_REGISTER | reg;

    Pull_CS_Low_SPI1();
    Send_Read_Write_Command_SPI1(&reg_addr);

    delay(10);

    return_nRF_value = Send_Write_Value_SPI1(write_value);
    Pull_CS_High_SPI1();

    return return_nRF_value;
}


uint8_t Abs_Write_to_nRF_Register(reg_map reg, uint8_t write_value)
{
	uint8_t return_nRF_value = 0;
        uint8_t final_write_value = 0;
        uint8_t reg_addr = 0;
    
        reg_addr = W_REGISTER | reg;
        
	Pull_CS_Low();
	Send_Read_Write_Command(&reg_addr);

	delay(10);

	return_nRF_value = Send_Write_Value(write_value);
	Pull_CS_High();

	return return_nRF_value;

}
uint8_t Write_to_nRF_Register(reg_map reg, uint8_t write_value)
{
        /* First read the present value in the register
         * and then OR it with the new value. This is the proper
         * way of writing to registers.
         */
        
	uint8_t return_nRF_value = 0;
        uint8_t read_reg_value = 0;
        uint8_t final_write_value = 0;
        uint8_t reg_addr = 0;
    
        read_reg_value = Read_from_nRF_Register(reg, &read_reg_value);
        
        reg_addr = W_REGISTER | reg;
        final_write_value = write_value | read_reg_value; 
        
	Pull_CS_Low();
	Send_Read_Write_Command(&reg_addr);

	delay(10);

	return_nRF_value = Send_Write_Value(final_write_value);
	Pull_CS_High();

	return return_nRF_value;

}

uint8_t Write_to_nRF_Register_SPI1(reg_map reg, uint8_t write_value)
{
        /* First read the present value in the register
         * and then OR it with the new value. This is the proper
         * way of writing to registers.
         */
        
	uint8_t return_nRF_value = 0;
        uint8_t read_reg_value = 0;
        uint8_t final_write_value = 0;
        uint8_t reg_addr = 0;
    
        read_reg_value = Read_from_nRF_Register_SPI1(reg, &read_reg_value);
        
        reg_addr = W_REGISTER | reg;
        final_write_value = write_value | read_reg_value; 
        
	Pull_CS_Low_SPI1();
	Send_Read_Write_Command_SPI1(&reg_addr);

	delay(10);

	return_nRF_value = Send_Write_Value_SPI1(final_write_value);
	Pull_CS_High_SPI1();

	return return_nRF_value;
}



