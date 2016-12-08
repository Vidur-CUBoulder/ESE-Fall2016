/*
 * parse_data.h
 *
 *  Created on: Oct 30, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_PARSE_DATA_H_
#define INCLUDES_PARSE_DATA_H_

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "log.h"
#include "data.h"
#include "led.h"
#include "error_handling.h"
#include "nRF.h"

#define UART_STOP_BYTE 0x23
#define MAX_DATA_LENGTH 20

static uint8_t is_nrf_setup = 0;

typedef enum cmds_t {
	ledcolor 	        = 0x10,
        nRF_Setup               = 0x20,
        nRF_Payload_Setup       = 0x21,
        nRF_Start_Comm          = 0x22,
        nRF_Read_RX_Payload     = 0x23,
        nRF_Dump_Reg_Values     = 0x24,
        read_temp_sensor        = 0x30,
        kill_program            = 0xFF
} cmds;

#ifdef CLI_PARSER
typedef enum action_t {
	set 	= 0,
	show 	= 1
} action;
#endif

typedef enum checksum_t {
	CHECK_SUCCESSFUL = 0x00,
	CHECK_FAILURE = 0x01
} checksum;

typedef enum ledcolors_t {
	all_off 	= 0x00,
	blue 		= 0x01,
	red 		= 0x02,
	green 		= 0x03,
	white 		= 0x04,
	magenta 	= 0x05,
	yellow 		= 0x06,
	cyan 		= 0x07
} ledcolors;

typedef struct classify_CLI {
    cmds command;
    uint8_t cmd_length;
    uint8_t data[MAX_DATA_LENGTH];
} CLI;

/* Function Prototypes */

/* Function: errors get_message(char *data);
 * Parameters: structure/array in which you want to store the data received.
 * Return: an enum that can be used for debugging.
 * Description: Used to store the received data via UART.
 */
errors get_message(char *data);

/* Function: errors parse_CLI(char *str_data, CLI *command_in)
 * Parameters:
 * 		a. str_data: data that you want to parse
 * 		b. structure in which you want to store the parsed data.
 * Return: an enum that can be used for debugging
 * Description: parse the data that has be received via UART and store
 * it in an appropriate array/data structure.
 */
errors parse_CLI(char *str_data, CLI *command_in);

/* Function: errors act_on_command(CLI *command_in);
 * Parameters:
 * 		a. command_in: the data structure in which the data
 * 			has been stored after parsing.
 * Return: an enum that can be used for debugging.
 * Description: perform an action based on what data has been stored
 * in the CLI data struct.
 */
errors act_on_command(CLI *command_in, nRF_Cluster *, nRF_Values *, nRF_Values *);

/*Function: errors flectchers_checksum(CLI cmd)
 * Parameters:
 * 		a. cmd: structure in which the checksum values are stored.
 * Return: an enum that can be used for debugging.
 * Description: perform the checksum calculations on the last 2B
 * of the data received via UART.
 */
checksum fletchers_checksum(CLI cmd);

/*Function: errors modify_intensity(ledcolors color)
 * Parameters: enum type that defines the color of the LED
 * Return: an enum that can be used for debugging
 * Description: modify the intensity of the specified led
 * by changing the pulse width.
 */
errors modify_intensity(ledcolors color);

errors parse_CLI_First(char *str_data, CLI *command_in);

#ifdef CLI_PARSER

errors set_union_values(CLI *cmd_in, char *word);

errors get_CLI(char *str_data, uint8_t *len);

static char *set_CLI_commands(cmds command);

static char *set_CLI_led_colors(ledcolors colors);

errors parse_CLI_words(char *cli_data, CLI *cmd_in);

uint32_t get_word(char *cli_data, char *ret_word, CLI cmd_in, uint32_t pos);

errors get_passed_value(CLI cmd_in, char *word);

errors act_on_CLI_command(CLI *cmd_in);

#endif

#endif /* INCLUDES_PARSE_DATA_H_ */
