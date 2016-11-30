/*
 * spi_masks.h
 *
 *  Created on: Nov 8, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_SPI_MASKS_H_
#define INCLUDES_SPI_MASKS_H_

#include "MKL25Z4.h"

#define CE_SPI0_High() (GPIOC_PSOR |= 0x00000008) 
#define CE_SPI1_High() (GPIOD_PSOR |= 0x00000008) 


#define CE_SPI0_Low() (GPIOC_PCOR |= 0x00000008)
#define CE_SPI1_Low() (GPIOD_PCOR |= 0x00000008)

#define WAIT_FOR_SPTEF ( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_FOR_SPTEF_SPI1 ( !(SPI_S_REG(SPI1) & SPI_S_SPTEF_MASK))

#define WAIT_FOR_SPRF ( !(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))
#define WAIT_FOR_SPRF_SPI1 ( !(SPI_S_REG(SPI1) & SPI_S_SPRF_MASK))

/*Function: Pull_CS_Low() & Pull_CS_Low_SPI1()
 * Parameters: void
 * Description: Pull the CS line low and start the SPI transmission.
 */
#define Pull_CS_Low() (GPIOC_PCOR = 0x00000010)

#define Pull_CS_Low_SPI1() (GPIOD_PCOR = 0x00000010)

/*Function: Pull_CS_High() & Pull_CS_High_SPI1()
 * Parameters: void
 * Description: Pull the CS line high and stop the SPI transmission.
 */
#define Pull_CS_High() (GPIOC_PSOR = 0x00000010)

#define Pull_CS_High_SPI1() (GPIOD_PSOR = 0x00000010)

/* SPI1 Initialization Macrons */

#define SET_SPI1_CLK_GATE 0x00800000
#define SET_CLK_GATE_PORT_D 0x00001000

#define CONFIG_PORTD3_GPIO 0x00000100
#define CONFIG_PORTD4_GPIO 0x00000100
#define CONFIG_PORTD4_DIR_OUT 0x00000010 
#define CONFIG_PORTD3_DIR_OUT 0x00000008 

#define CONFIG_PORTD5_SPI_SCK 0x00000200
#define CONFIG_PORTD6_SPI_MOSI 0x00000200
#define CONFIG_PORTD7_SPI_MISO 0x00000200

#define SPI1_BAUD_RATE 0x30

#define SPI1_C1_CONFIG 0x50 /* SPE = 1 & MSTR = 1 */ 

/*SPI0 Initialization Macros*/

#define SET_SPI0_CLK_GATE 0x00400000
#define SET_CLK_GATE_PORT_C 0x00000800

#define CONFIG_PORTC3_GPIO 0x00000100
#define CONFIG_PORTC11_DIR_OUT 0x00000800

#define CONFIG_PORTC4_GPIO 0x00000100
#define CONFIG_PORTC3_DIR_OUT 0x00000008
#define CONFIG_PORTC4_DIR_OUT 0x00000010

#define CONFIG_PORTC5_SPI_SCK 0x00000200
#define CONFIG_PORTC6_SPI_MOSI 0x00000200
#define CONFIG_PORTC7_SPI_MISO 0x00000200

#define SPI0_BAUD_RATE 0x30

#define SPI0_C1_CONFIG 0x50 /*SPE = 1 & MSTR = 1*/

/* Command Word Masks */

#define R_REGISTER              0x00 	/* 000A_AAAA; A->Address */
#define W_REGISTER              0x20 	/* 001A_AAAA */
#define R_RX_PAYLOAD            0x61 	/* 0110_0001 - Fixed */
#define W_TX_PAYLOAD            0XA0 	/* 1010_0000 - Fixed */
#define FLUSH_TX                0xE1 	/* 1110_0001 - Fixed */
#define FLUSH_RX                0xE2 	/* 1110_0010 - Fixed */
#define REUSE_TX_PL             0xE3	/* 1110_0011 - Fixed */
#define R_RX_PL_WID             0x60 	/* 0110_0000 - Fixed */

#define W_ACK_PAYLOAD           0xA8	/* 1010_1PPP; PPP -> 000 */

#define W_TX_PAYLOAD_NOACK      0xB0    /* 1011_0000 - Fixed */
#define NOP                     0xFF    /* 1111_1111 - Fixed */

/* Register Map Definitions */

typedef enum register_defs_t {
    CONFIG         = 0x00,    
    EN_AA          = 0x01,
    EN_RXADDR      = 0x02,
    SETUP_AW       = 0x03,
    SETUP_RETR     = 0x04, 
    RF_CH          = 0x05,
    RF_SETUP       = 0x06,
    STATUS         = 0x07,
    OBSERVE_TX     = 0x08,
    RPD            = 0x09,
    RX_ADDR_P0     = 0x0A, 
    RX_ADDR_P1     = 0x0B,
    RX_ADDR_P2     = 0x0C, 
    RX_ADDR_P3     = 0x0D,
    RX_ADDR_P4     = 0x0E,
    RX_ADDR_P5     = 0x1F,
    TX_ADDR        = 0x10,
    RX_PW_P0       = 0x11,
    RX_PW_P1       = 0x12,
    RX_PW_P2       = 0x13,
    RX_PW_P3       = 0x14,
    RX_PW_P4       = 0x15,
    RX_PW_P5       = 0x16,
    FIFO_STATUS    = 0x17,
    DYNPD          = 0x1C,
    FEATURE        = 0x1D
} reg_map;

/* Misc. Macros */

#define MAX_REG_LENGTH 5

#endif /* INCLUDES_SPI_MASKS_H_ */
