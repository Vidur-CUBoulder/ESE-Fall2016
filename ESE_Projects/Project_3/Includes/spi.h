/*
 * spi.h
 *
 *  Created on: Oct 29, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include "MKL25Z4.h"

//void spi_0_init();

void spi_1_master_init();
void spi_0_slave_init();
void delay(uint8_t value);

#endif /* INCLUDES_SPI_H_ */
