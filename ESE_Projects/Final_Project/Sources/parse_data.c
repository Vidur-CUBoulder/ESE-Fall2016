/*
 * parse_data.c
 *
 *  Created on: Oct 30, 2016
 *      Author: vidur
 */

#include "parse_data.h"

#define DEBUG
#define BLUE_LED

errors get_message(char *data)
{
	if (data == NULL) {
		return NULL_FAILURE;
	}

	init_uart();
	config_receive();
	uint16_t count = 0;

	while(1) {
		while(!(UART0->S1 & 0x20)) {
			/* Wait for Buffer Full */
		}

		*(data+count) = UART0->D;

		if( *(data+count) == UART_STOP_BYTE) { /* stop bit: # */
			/* Signifies end of the CLI command */
			return SUCCESSFUL;
		}
		count++;
	}
	return INVALID;
}

#if 0
checksum  fletchers_checksum(CLI cmd)
{
	uint16_t sum_1 = 0;
	uint16_t sum_2 = 0;
	uint8_t i = 0;

	for (i=0; i<2; i++) {
		sum_1 = (sum_1 + cmd.data[i]) % 0xFF;
		sum_2 = (sum_1 + sum_2) % 0xFF;
	}

	uint16_t check_MSB = 0xFF - (( sum_1 + sum_2) % 0xFF);
	uint16_t check_LSB = 0xFF - (( sum_1 + check_MSB ) % 0xFF);

	if (check_MSB == cmd.checksum[0] && check_LSB == cmd.checksum[1]) {
		return CHECK_SUCCESSFUL;
	} else {
		return CHECK_FAILURE;
	}

}
#endif

errors parse_CLI(char *str_data, CLI *command_in)
{
	if(str_data == NULL) {
		return NULL_FAILURE;
	}

	uint8_t i = 0;

	command_in->command = *(str_data);
	command_in->cmd_length = (*(str_data+1));
	while(i != (command_in->cmd_length)) {
		command_in->data[i] = *(str_data+2+i);
		i++;
	}

	return SUCCESSFUL;

}

errors parse_CLI_First(char *str_data, CLI *command_in)
{
	if(str_data == NULL) {
		return NULL_FAILURE;
	}

	uint8_t i = 0;

	command_in->command = *(str_data+1);
	command_in->cmd_length = (*(str_data+2));
	while(i != (command_in->cmd_length)) {
		command_in->data[i] = *(str_data+3+i);
		i++;
	}

	return SUCCESSFUL;

}

/* The data frame format is as follows:
 *      <cmd> <data length - cmd byte> ....<data>.... < terminating byte : 23(#) >
 *      The parser will first parse the command and accordingly make a decision on 
 *      how to store the data in the struct.
 *      Command List:-
 *              a. LED Blink/Color.
 *              b. Config and setup the nRF. 
 *              c. Put data into the TX payload of the nRF module
 *              d. Read the data from the RX payload of the nRF module.
 *              e. Read the on chip temperature sensor data
 *              f. Send data to store onto the EEPROM.
 */
errors act_on_command(CLI *command_in, nRF_Cluster *new_cluster, nRF_Values *PTX_Config_Data,\
                        nRF_Values *PRX_Config_Data)
{

    init_uart();
    config_transmit();
    uint8_t reg_value = 0;

    switch(command_in->command)
    {

        case ledcolor: /*Set the color of the led and turn on that LED */

            config_leds();

            switch(command_in->data[0])
            {
                case blue: MY_LOG("Turning on the Blue LED\n");
                           turn_on_leds(blue);
                           break;

                case red: MY_LOG("Turning on the Red LED\n");
                          turn_on_leds(red);
                          break;

                case green: MY_LOG("Turning on the Green LED\n");
                            turn_on_leds(green);
                            break;

                case white: MY_LOG("Turning on the White LED\n");
                            turn_on_leds(white);
                            break;

                case magenta: MY_LOG("Turning on the Magenta LED\n");
                              turn_on_leds(magenta);
                              break;

                case cyan: MY_LOG("Turning on the Cyan LED\n");
                           turn_on_leds(cyan);
                           break;

                case yellow: MY_LOG("Turning on the Yellow LED\n");
                             turn_on_leds(yellow);
                             break;

                default: MY_LOG("Keeping all LEDs off by default\n");
                         turn_on_leds(0xFF); /*Entering the default case*/
            }
            break;

        case nRF_Setup:

            MY_LOG("Configure the nRF for Wireless Trasnmission!\n");

            //spi_0_init();
            //spi_1_init();
            
            init_nRF_modules(new_cluster, PTX_Config_Data, PRX_Config_Data);
        
            MY_LOG("nRF Modules Successfully Configured for Wireless Trasnmisstion!\n");

            is_nrf_setup = 1;

            break;

        case nRF_Payload_Setup:
            
            if(!is_nrf_setup) {
                MY_LOG("You cannot pass data to the nRF without configuring it...\n");
                return INVALID;
            }

            MY_LOG("Congiuring the nRF Modules with the Payload provided!\n");

            //Fill the SPI buffer with the data.
            new_cluster->fill_buffer(PTX_Config_Data->spi_number,\
                                        command_in->data, 4);

            MY_LOG("Payload Configured Successfully!\n");

            break;

        case nRF_Start_Comm:
            
            if(!is_nrf_setup) {
                MY_LOG("You cannot pass data to the nRF without configuring it...\n");
                return INVALID;
            }
            
            MY_LOG("Starting the nRF Communication NOW!\n");

            /* Turn-On the Modules! */
            new_cluster->Activate_Modules(PRX_Config_Data->spi_number,\
                                          PTX_Config_Data->spi_number);

            /* Instead of the delay, monitor the status register and
             * if the RX_DR pin is set, come out of the loop and
             * read the value for the RX payload register.
             */
            while(reg_value != DATA_IN_RX_PAYLOAD) {
                /* Continue reading the Status register until data is received in the 
                 * RX payload register.
                 */
                Read_from_nRF_Register(PRX_Config_Data->spi_number, STATUS, &reg_value);
            }

            MY_LOG("Successful Communication!\n");

            break;

        case nRF_Read_RX_Payload:
            
            if(!is_nrf_setup) {
                MY_LOG("You cannot pass data to the nRF without configuring it...\n");
                return INVALID;
            }
            
            MY_LOG("Reading data from the RX Payload...\n");
            
            /* Read the data payload from the RX module */
            Read_Payload_Register_Value(PRX_Config_Data->spi_number, new_cluster,\
                                        PRX_Config_Data->store_Payload_Data, 3);

            
            MY_LOG("Data Read:-\n");
            MY_LOG_PARAMS("->", PRX_Config_Data->store_Payload_Data[0]);
            MY_LOG("\n");
            MY_LOG_PARAMS("->", PRX_Config_Data->store_Payload_Data[1]);
            MY_LOG("\n");
            MY_LOG_PARAMS("->", PRX_Config_Data->store_Payload_Data[2]);
            MY_LOG("\n");
            
            break; 

        case kill_program:
                MY_LOG("Exiting From the Program!\n");
                free(new_cluster);
                exit(1);

        case read_temp_sensor:
                MY_LOG("Reading data from the temperature sensor!\n");

                Init_Temp_Sensor();

                float result = 0;

                Read_Temp_Sensor_Value(&result);

                MY_LOG_FLOAT_PARAMS("OUTPUT: ", result, 3);

            break;

        default: /*Defining the default case*/
            MY_LOG("In the DEFAULT case! Exiting! \n");
            free(new_cluster);
            exit(1);
            return INVALID;
    }

    return SUCCESSFUL;

}

