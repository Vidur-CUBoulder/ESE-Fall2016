/*
 * spi_masks.h
 *
 *  Created on: Nov 8, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_SPI_MASKS_H_
#define INCLUDES_SPI_MASKS_H_

#define WAIT_FOR_SPTEF ( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_FOR_SPRF ( !(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))

/*Function: Pull_CS_Low()
 * Parameters: void
 * Description: Pull the CS line low and start the SPI transmission.
 */
#define Pull_CS_Low() GPIOC_PCOR = 0x00000010;

/*Function: Pull_CS_High()
 * Parameters: void
 * Description: Pull the CS line high and stop the SPI transmission.
 */
#define Pull_CS_High() GPIOC_PSOR = 0x00000010;


/*SPI Initialization Macros*/

#define SET_SPI_CLK_GATE 0x00400000
#define SET_CLK_GATE_PORT_C 0x00000800

#define CONFIG_PORTC4_GPIO 0x00000100
#define CONFIG_PORTC4_DIR_OUT 0x00000010

#define CONFIG_PORTC5_SPI_SCK 0x00000200
#define CONFIG_PORTC6_SPI_MOSI 0x00000200
#define CONFIG_PORTC7_SPI_MISO 0x00000200

#define SPI_BAUD_RATE 0x30

#define SPI_C1_CONFIG 0x50 /*SPE = 1 & MSTR = 1*/

/* Command Word Masks */

#define R_REGISTER 0x00 		/* 000A_AAAA; A->Address */
#define W_REGISTER 0x20 		/* 001A_AAAA */
#define R_RX_PAYLOAD 0x61 		/* 0110_0001 - Fixed */
#define W_TXAYLOAD 0XA0 		/* 1010_0000 - Fixed */
#define FLUSH_TX 0xE1 			/* 1110_0001 - Fixed */
#define FLUSH_RX 0xE2 			/* 1110_0010 - Fixed */
#define REUSE_TX_PL 0xE3		/* 1110_0011 - Fixed */
#define R_RX_PL_WID 0x60 		/* 0110_0000 - Fixed */

#define W_ACK_PAYLOAD 0xA8		/* 1010_1PPP; PPP -> 000 */

#define W_TX_PAYLOAD_NOACK 0xB0 /* 1011_0000 - Fixed */
#define NOP 0xFF 				/* 1111_1111 - Fixed */

/* Register Map Definitions */

#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define OBSERVE_TX 0x08
#define RPD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define PX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

/* Misc. Macros */

#define MAX_REG_LENGTH 5

#endif /* INCLUDES_SPI_MASKS_H_ */
