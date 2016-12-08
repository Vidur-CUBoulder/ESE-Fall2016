/*
 * nRF.h
 *
 *  Created on: Nov 9, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_NRF_H_
#define INCLUDES_NRF_H_

#include "error_handling.h"
#include "spi_masks.h"

#define RESET_nRF_Modules() reset_all_registers(SPI1);\
                            reset_all_registers(SPI0)

#define DATA_IN_RX_PAYLOAD 0x42

/********** DEBUGGING RETURN TYPES ************/
typedef enum errors_t {
	SUCCESSFUL,
	INCORRECT_ENTRY,
	NULL_FAILURE,
	INVALID,
        PTX_CONFIG_SUCCESSFUL,
        PRX_CONFIG_SUCCESSFUL,
        BUFFER_FILLED,
        nRF_READ_SUCCESSFUL,
        nRF_READ_FAILURE,
        nRF_MODULES_ON,
        nRF_MODULES_OFF,
        FIVE_BYTES_SUCCESSFULLY_WRITTEN,
        nRF_MODULES_SUCCESSFULLY_INIT,
        CLUSTER_SPACE_CLEARED

} errors;

/******* nRF CONFIGURATION DATA STORAGE *****/
typedef struct nRF_Values_t {
    void *spi_number;
    uint8_t set_RF_CH;
    uint8_t set_RX_PW_P1; 
    uint8_t set_RF_SETUP; 
    uint8_t set_CONFIG; 
    uint8_t set_EN_AA; 
    uint8_t set_EN_RXADDR; 
    uint8_t set_SETUP_RETR; 
    uint8_t set_DYNPD; 
    uint8_t set_STATUS;
    uint8_t set_RX_ADDR_P0[5];
    uint8_t set_TX_ADDR[5];
    uint8_t set_RX_ADDR_P1[5];
} nRF_Values;


/*
 * assimilate the data and functions into a cluster type
 */
typedef struct nRF_Devices_t {

    errors (*Reset_Module)(void *);
    errors (*Dump_Register_Values)(void *);
    errors (*Config_Modules)(nRF_Values );
    errors (*fill_buffer)(void *, uint8_t *, uint8_t );
    errors (*Activate_Modules)(void *, void *);
    errors (*Read_Payload_Buffer)(void * ,struct nRF_Devices_t * , uint8_t *, uint8_t );
    errors (*Free_Cluster)(struct nRF_Devices_t *);

} nRF_Cluster;

/* Function: Send_Read_Write_Command(void *spi, uint8_t *cmd)
 * Parameters:
 *      a. *spi : the SPI module used.
 *      b. *cmd : the data that you want to pass to the SPI.
 * Return: Value returned by the nRF module
 * Description: Send the command byte to the nRF module and return
 * the value that MISO pushes back into the Rx Buffer.
 */
uint8_t Send_Read_Write_Command(void *spi, uint8_t *cmd);

/*Function: Send_Write_Value(void *spi, uint8_t write_value)
 * Parameters:
 *      a. *spi: the SPI module used.
 *      b. write_value: the value to be written to the module.
 * Return: Value that is returned via MISO to the Master Device.
 * Description: Send the write value to the respective nRF register.
 * Failure to do this will result in an unexpected behavior.
 */
uint8_t Send_Write_Value(void *spi, uint8_t write_value);

/*Function: Flush_RX(void *spi)
 * Parameters:
 *      *spi: the SPI module used.
 * Return: nothing.
 * Description: Flush the RX register in the nRF module.
 */
void Flush_RX(void *spi);

/*Function: Flush_TX(void *spi)
 * Parameters:
 *      *spi: the SPI module used.
 * Return: nothing.
 * Description: Flush the TX register in the nRF module.
 */
void Flush_TX(void *spi);

/* Function: Abs_Write_5B_to_nRF_Register(void *spi, reg_map reg, uint8_t *value);
 * Parameters:
 *      a. *spi : the SPI module that is being used.
 *      b. reg: the register that you want to write to.
 *      c. *value: the value that you want to write into the register.
 * Return: a debug handle that can be used for debugging.
 * Description: used to write 5Bytes to the nRF Register.
 */
errors Abs_Write_5B_to_nRF_Register(void *spi, reg_map reg, uint8_t *value);

/*Function: reset_all_registers(void *spi)
 * Parameters: 
 *      *spi: define the SPI module that is being used.
 * Return: Resets all the registers in the nRF module to its default
 *              values.
 * Description: Used to reset all the registers in the nRF module.
 */
errors reset_all_registers(void *spi);

/*Function: config_tx_addr(nRF_Values config_data)
 * Parameters:
 *      config_data: the config values for the particular nRF module.
 * Return: void.
 * Description: used to configure the TX address for the nRF module.
 */
void config_tx_addr(nRF_Values config_data);

/*Function: config_rx_addr(nRF_Values config_data)
 * Parameters:
 *      config_data: the config values for the particular nRF module.
 * Return: void.
 * Description: used to configure the RX address for the nRF module.
 */
void config_rx_addr(nRF_Values config_data);

/*Function: fill_nRF_buffer(void *spi, uint8_t *data, uint8_t length)
 * Parameters:
 *      a. *spi: the SPI module that you are accessing.
 *      b. *data: the data that you want to fill the nRF buffer with.
 *      c. length: the length of the data that you want to write into 
 *                      the nRF TX buffer.
 * Return: a debug handle that you may use for debugging purposes.
 * Description: Used to write into the TX buffer of a nRF module.
 */
errors fill_nRF_buffer(void *spi, uint8_t *data, uint8_t length);

/*Function: nrf_Config_PTX(nRF_Values config_data)
 * Parameters:
 *      config_data: the data that you want to config the 
 *                      PTX module with.
 * Return: a debug handle that you can use for debugging purposes.
 * Description: used to do the initial config. for the PTX module.
 */
errors nrf_Config_PTX(nRF_Values config_data);

/*Function: nrf_Config_PRX(nRF_Values config_data)
 * Parameters:
 *      config_data: the data that you want to config the 
 *                      PRX module with.
 * Return: a debug handle that you can use for debugging purposes.
 * Description: used to do the initial config. for the PRX module.
 */
errors nrf_Config_PRX(nRF_Values config_data);

/*Function: *Alloc_nRF_Cluster(void)
 * Parameters: void
 * Return: a pointer to the nRF_Cluster struct.
 * Description: init. the function to the various function pointers
 *              of declared in the struct.
 */
nRF_Cluster *Alloc_nRF_Cluster(void);

/*Function: Turn_On_Modules(void *SPI_RX, void *SPI_TX)
 * Parameters:
 *      *SPI_RX: the SPI number that is being used to access the PRX.
 *      *SPI_TX: the SPI number that is being used to access the PTX.
 * Return: a debug handle that can be used for debugging.
 * Description: Run the procedures to turn on the PTX and PRX modules.
 */
errors Turn_On_Modules(void *SPI_RX/*SPI1*/, void *SPI_TX/*SPI0*/);

/*Function: Turn_Off_Modules(void *SPI_RX, void *SPI_TX)
 * Parameters:
 *      *SPI_RX: the SPI number that is being used to access the PRX.
 *      *SPI_TX: the SPI number that is being used to access the PTX.
 * Return: a debug handle that can be used for debugging.
 * Description: Run the procedures to turn off the PTX and PRX modules.
 */
errors Turn_Off_Modules(void *SPI_RX/*SPI1*/, void *SPI_TX/*SPI0*/);

/*Function: Read_RX_Payload(void *spi, uint8_t *read_data, uint8_t len);
 * Parameters:
 *      a. *spi: the SPI number that the nRF module is connected to.
 *      b. *read_data: the location where you want to store the read data.
 *      c. len: the length of the data that you want to read from the payload.
 * Return: a debug handle that can be used for debugging purposes.
 * Description: Read the payload data from the nRF modules.
 */
errors Read_RX_Payload(void *spi, uint8_t *read_data, uint8_t len);

/*Function: Dump_Reg(void *spi)
 * Parameters:
 *      *spi: the spi number that you want to use.
 * Return: a debug handle that can be used for debugging.
 * Description: used to Dump all the nRF registers connected to the particular
 *                     SPI module/number.
 */
errors Dump_Reg(void *spi);

errors init_nRF_modules(nRF_Cluster *new_cluster, nRF_Values *,\
                            nRF_Values *);

errors Read_Payload_Register_Value(void *, nRF_Cluster *new_cluster, uint8_t *data, uint8_t len);

errors Free_nRF_Cluster(nRF_Cluster *cluster);

#endif /* INCLUDES_NRF_H_ */
