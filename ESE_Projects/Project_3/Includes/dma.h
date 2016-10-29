/*
 * dma.h
 *
 *  Created on: Oct 25, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

//#include "main.h"
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include "MKL25Z4.h"

typedef enum debug_e {
	SUCCESS, //Generic Success enum.
	DMA_SUCCESSFUL,
	CE_BIT_SET,
	BES_BIT_SET,
	BED_BIT_SET,
	LENGTH_ERROR //More than what is possible was entered!
}dma_debug;

#define ENABLE_CLOCK_GATE_DMAMUX 0x00000002
#define ENABLE_CLOCK_GATE_DMA 0x00000100
#define DISABLE_DMAMUX_CFG 0x00
#define ENABLE_DMA_DMAMUX 0x80
#define START_DMA_TRANSFER 0x00010000

#define RAISE_CE_BIT 0x40000000
#define RAISE_BES_BIT 0x20000000
#define RAISE_BED_BIT 0x10000000

#define DCR_8_BIT_INCREMENTS 0x005a0000
#define DCR_32_BIT_INCREMENTS 0x00480000
#define DCR_32_BIT_INCREMENTS_MEMZERO 0x00080000
#define DCR_8BIT_INCREMENTS_MEMZERO 0x001a0000

dma_debug my_memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length);

dma_debug my_memzero_dma(uint8_t *src, uint32_t length);

dma_debug config_one_byte_length(uint32_t length);

dma_debug check_dma_errors();

dma_debug config_word_length();

dma_debug start_dma_transfer();

#endif /* INCLUDES_DMA_H_ */
