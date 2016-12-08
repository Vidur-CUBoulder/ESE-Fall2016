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

errors parse_CLI(char *str_data, CLI *command_in)
{
	if(str_data == NULL) {
		return NULL_FAILURE;
	}

	uint8_t i = 0;

	command_in->command = *(str_data+1);
	command_in->cmd_length = (*(str_data+2) + 1);
	while(i != (command_in->cmd_length-2-3)) {
		command_in->data[i] = *(str_data+3+i);
		i++;
	}
	command_in->checksum[0] = *(str_data+command_in->cmd_length-2);
	command_in->checksum[1] = *(str_data+command_in->cmd_length-1);

	return SUCCESSFUL;

}

errors act_on_command(CLI *command_in)
{

#ifdef DEBUG
    /*For debugging purposes
     * No need to do extra work if not needed!
     */
    init_uart();
    config_transmit();
#endif

    switch(command_in->command)
    {

        case commands: /*Output a list of the available command on the UART*/
            break;

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

        case intensity: /* Set the intensity of the LED! */
            MY_LOG("Setting the LED Intensity\n");
            MY_LOG("Press 'W' to increase and 'S' to decrease\n");
            MY_LOG("Press 'Q' to quit.\n");
            modify_intensity(command_in->data[1]);
            break;

        default: /*Defining the default case*/
            MY_LOG("In the DEFAULT case! Exiting! \n");
            return INVALID;
    }

    return SUCCESSFUL;

}

errors modify_intensity(ledcolors color)
{

	/* Initialize the UART */
	init_uart();

	/* Config the UART to receive */
	config_receive();

	char input;
	uint16_t pulsewidth = 0;

	while(1) {

		while(!(UART0->S1 & 0x20)) {
		}
		input = UART0->D;

		if(input == 'q') {
			break;
		}

		if(input == 'w') {
			pulsewidth+=300;
		} else if(input == 's') {
			pulsewidth -= 300;
		} else {
			/* turn off the LED */
			pulsewidth = 0;
		}

		if(color == blue) {
			init_PWM_Blue(pulsewidth);
		} else if (color == red) {
			init_PWM_Red(pulsewidth);
		} else if (color == green) {
			init_PWM_Green(pulsewidth);
		} else {
			/*Invalid Color input; exit*/
			return INVALID;
		}

	}

	return SUCCESSFUL;

}

#ifdef CLI_PARSER

errors get_CLI(char *str_data/*, uint32_t *len*/)
{
    if (str_data == NULL) {
        return NULL_FAILURE;
    }

    init_uart();
    config_receive();
    uint8_t count = 0;
    //uint8_t temp_len = *len;

    while (1) {
        while(!(UART0_S1 & 0x20)) {
            /*Wait for Buffer Full!*/
        }

        *(str_data + count) = UART0->D;
        if( *(str_data+count) == 0x0A || *(str_data+count) == 0x0D) {
            /* Signifies end of the CLI command */
            //temp_len = (count - 1);
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

#if 0
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
#endif

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

errors act_on_CLI_command(CLI *cmd_in)
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

#endif

