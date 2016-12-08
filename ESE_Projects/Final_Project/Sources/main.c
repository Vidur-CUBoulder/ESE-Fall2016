/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"
#include "core_cmInstr.h"

//#define SPI_Read_Write_Working
//#define READ_PRINT_SINGLE_BYTE
//#define DEBUG
//#define temp_sensor
//#define SPI0_Rx_nRF_Comm
//#define EEPROM
//#define Final_Program
//#define Final_EEPROM
#define UART_PARSER

int main(void)
{
    CLI command_in;
    nRF_Cluster *new_cluster = NULL;
    new_cluster = Alloc_nRF_Cluster();
    nRF_Values PTX_Config_Data = {SPI0, 76, 4, 0x06, 0x08, 0x03, 0x03, 0x4F, 0x00, 0x70,{0xe7, 0xe7, 0xe7, 0xe7, 0xe7 },\
        {0xe7, 0xe7, 0xe7, 0xe7, 0xe7}, {0xd7, 0xd7, 0xd7, 0xd7, 0xd7} };  
    nRF_Values PRX_Config_Data = {SPI1, 76, 4, 0x06, 0x08, 0x03, 0x03, 0x4F, 0x00, 0x70,{0xd7, 0xd7, 0xd7, 0xd7, 0xd7 },\
        {0xd7, 0xd7, 0xd7, 0xd7, 0xd7}, {0xe7, 0xe7, 0xe7, 0xe7, 0xe7} };

    spi_0_init();
    spi_1_init();

    uint8_t i = 0;
    uint8_t data[20] = {0};

    get_message(&data[0]);
    parse_CLI_First(&data[0], &command_in);
    act_on_command(&command_in, new_cluster, &PTX_Config_Data, &PRX_Config_Data );

    while(1) { 
        get_message(&data[0]);

        parse_CLI(&data[0], &command_in);

        act_on_command(&command_in, new_cluster, &PTX_Config_Data, &PRX_Config_Data );
    }
    return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
