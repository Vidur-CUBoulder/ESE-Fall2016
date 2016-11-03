/*
 * parse_data.c
 *
 *  Created on: Oct 30, 2016
 *      Author: vidur
 */

#include "parse_data.h"

errors get_CLI(char *str_data, uint32_t *len)
{
	if (str_data == NULL) {
		return NULL_FAILURE;
	}

	init_uart();
	config_receive();
	uint8_t count = 0;

	while (1) {
		while(!(UART0_S1 & 0x20)) {
			/*Wait for Buffer Full!*/
		}

		*(str_data + count) = UART0->D;
		if( *(str_data+count) == 0x0A || *(str_data+count) == 0x0D) {
			/* Signifies end of the CLI command */
			*len = (count - 1);
			return SUCCESSFUL;
		}
		count++;
	}
	return INVALID;
}

static char *set_CLI_commands(cmds command)
{
	static char *cmds_strings[] = {"commands", "baudrate", "ledcolor", "intensity", "kill_program"};
	return cmds_strings[command];
}

static char *set_CLI_ledcolors(ledcolors colors)
{
	static char *act_strings[] = {"blue", "red", "green", "white"};
	return act_strings[colors];
}

errors parse_CLI(char *cli_data, CLI *cmd_in)
{
	uint32_t pos = 0;
	uint8_t cntr = 0;
	char *word = NULL;
	word = (char *)malloc(sizeof(char) * 15);

	pos = get_word(cli_data, word, *cmd_in, pos);
	if(!strcmp(word, "show")) {
		cmd_in->act = show;
		cmd_in->command = commands;
		free(word);
		return SUCCESSFUL;
	} else if (!strcmp(word, "set")) {
		pos = get_word(cli_data, word, *cmd_in, pos);
		cmd_in->act = set;
		for(cntr = commands ; cntr<= kill_program; cntr++) {
			if( !strcmp(word, set_CLI_commands(cntr)) ) {
				cmd_in->command = cntr;
				pos = get_word(cli_data, word, *cmd_in, pos);
				set_union_values(cmd_in, word);
				free(word);
				return SUCCESSFUL;
			}
		}
		free(word);
	} else {
		return INCORRECT_ENTRY;
	}

	return SUCCESSFUL;
}

errors set_union_values(CLI *cmd_in, char *word)
{
	if( cmd_in->command == baudrate ) {
		cmd_in->u_cmd_value.baudrate = atoi(word);
	} else if ( cmd_in->command == ledcolor ) {
		memcpy((cmd_in->color), word, strlen(word));
	} else if ( cmd_in->command == intensity ) {
		cmd_in->u_cmd_value.led_intensity = atoi(word);
	} else {
		free(word);
		return INCORRECT_ENTRY;
	}

	return SUCCESSFUL;
}

uint32_t get_word(char *cli_data, char* ret_word, CLI cmd_in, uint32_t pos)
{
	uint8_t i = 0;
	while( (*(cli_data+pos+1) != 0x20) && (pos != cmd_in.cmd_length) ) {
		*(ret_word+i) = *(cli_data + pos +1);
		*(ret_word+i+1) = '\0';
		pos++;
		i++;
	}
	return (pos+1);
}

errors act_on_command(CLI *cmd_in)
{
	switch(cmd_in->act)
	{
		case show:
					switch(cmd_in->command)
					{
						case commands: /*Show the list of possible commands*/
										MY_LOG("set baudrate <baud rate>\n");
										MY_LOG("set led_color <blue|green|red|white>\n");
										MY_LOG("set led_intensity <intensity>\n");
										MY_LOG("set kill_program!\n");
										break;
					}
					break;
		case set:
					switch(cmd_in->command)
					{
						case baudrate: /*Set the Baudrate of the Board*/
										break;
						case ledcolor: /*Set the Led Color*/
										init_uart();
										config_receive();
										config_leds();

										ledcolors cntr;
										if ( !strcmp(cmd_in->color, "blue") ) {
											turn_on_leds(blue);
											break;
										} else if (!strcmp(cmd_in->color, "red")) {
											turn_on_leds(red);
											break;
										} else if (!strcmp(cmd_in->color, "green")) {
											turn_on_leds(green);
											break;
										} else if (!strcmp(cmd_in->color, "white")) {
											turn_on_leds(white);
											break;
										} else {
											return INCORRECT_ENTRY;
										}
										break;
						case intensity: /*Set the Led Intensity*/
										break;

					}
	}

	return SUCCESSFUL;
}

