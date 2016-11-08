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

typedef enum errors_t {
	SUCCESSFUL,
	INCORRECT_ENTRY,
	NULL_FAILURE,
	INVALID,
	INVALID_RET_FROM_nRF
} errors;

typedef enum cmds_t {
	commands = 0,
	baudrate = 1,
	ledcolor = 2,
	intensity = 3,
	kill_program = 4
} cmds;

typedef enum action_t {
	set = 0,
	show = 1
} action;

typedef enum ledcolors_t {
	blue = 0,
	red = 1,
	green = 2,
	white = 3
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
	uint8_t data[40];
	uint8_t checksum[2];
} CLI;

/* Function Prototypes */

errors get_message(char *data);

errors parse_CLI(char *str_data, CLI *command_in);


errors set_union_values(CLI *cmd_in, char *word);

errors get_CLI(char *str_data, uint32_t *len);

static char *set_CLI_commands(cmds command);

static char *set_CLI_led_colors(ledcolors colors);

errors parse_CLI_words(char *cli_data, CLI *cmd_in);

uint32_t get_word(char *cli_data, char *ret_word, CLI cmd_in, uint32_t pos);

errors get_passed_value(CLI cmd_in, char *word);

errors act_on_command(CLI *cmd_in);

#endif /* INCLUDES_PARSE_DATA_H_ */
