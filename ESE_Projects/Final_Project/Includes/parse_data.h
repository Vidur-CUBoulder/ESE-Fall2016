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

typedef enum cmds_t {
	commands 	= 0,
	baudrate 	= 1,
	ledcolor 	= 2,
	intensity 	= 3,
	kill_program 	= 4
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

#ifdef CLI_PARSER
	action act;
#endif
	cmds command;
	uint8_t cmd_length;
#ifdef CLI_PARSER
	char color[8];

	union {
		uint32_t baudrate;
		uint8_t led_intensity;
		uint8_t kill_program;
	} u_cmd_value;
#endif
	uint8_t data[10];
	uint8_t checksum[2];
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
errors act_on_command(CLI *command_in);

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


#ifdef CLI_PARSER

errors set_union_values(CLI *cmd_in, char *word);

errors get_CLI(char *str_data, uint32_t *len);

static char *set_CLI_commands(cmds command);

static char *set_CLI_led_colors(ledcolors colors);

errors parse_CLI_words(char *cli_data, CLI *cmd_in);

uint32_t get_word(char *cli_data, char *ret_word, CLI cmd_in, uint32_t pos);

errors get_passed_value(CLI cmd_in, char *word);

errors act_on_CLI_command(CLI *cmd_in);

#endif

#endif /* INCLUDES_PARSE_DATA_H_ */
