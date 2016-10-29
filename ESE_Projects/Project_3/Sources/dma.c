/*
 * dma.c
 *
 *  Created on: Oct 25, 2016
 *      Author: vidur
 */

#include "dma.h"

dma_debug my_memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length)
{
	/*1. Config. the clock gating register for DMAMUX clock gate register.*/
	SIM_SCGC6 |= ENABLE_CLOCK_GATE_DMAMUX;

	/*2. Enable DMA clock gate control */
	SIM_SCGC7 = ENABLE_CLOCK_GATE_DMA;

	/*3. First disable the DMAMUX_CHCFG0 register. */
	DMAMUX0_CHCFG0 = DISABLE_DMAMUX_CFG;

	/* 4. Store the Source address in the DMA Source Register */
	DMA_SAR0 = (uint32_t)src;

	/* 5. Store the Destination address in the DMA Destination Register */
	DMA_DAR0 = (uint32_t)dst;

	/*Optimizing the transfer by breaking the transfer into words(32bits)*/
	uint32_t word_transfers = length/4;
	uint32_t word_remainder = length%4;

	/* First do the transfer of words*/
	if(word_transfers != 0) {
		/*Config DMA for word transfers*/
		config_word_length(word_transfers);

		/*Start the word trasnfer*/
		dma_debug ret_handle;
		ret_handle = start_dma_transfer();
		if(ret_handle != DMA_SUCCESSFUL) {
			return ret_handle;
		}
	}

	if(word_remainder != 0) {
		/* we need to do these many 1B transfers.
		 * So, manage the config. accordingly.
		 */
		config_one_byte_length(word_remainder);

		/*start the transfer of 1B data*/
		dma_debug ret_handle;
		ret_handle = start_dma_transfer();
		if(ret_handle != DMA_SUCCESSFUL) {
			return ret_handle;
		}
	}

	return DMA_SUCCESSFUL;
}

dma_debug start_dma_transfer()
{
	/*Enable the DMA bit in the DMAMUX register */
	DMAMUX0_CHCFG0 = ENABLE_DMA_DMAMUX;

	/*Raise the START bit to start the transfer */
	DMA_DCR0 |= START_DMA_TRANSFER;

	/*Check if the transfer is successful*/
	return (check_dma_errors());
}

dma_debug check_dma_errors()
{
	/* Check the registers for any errors */
	if ( (DMA_DSR_BCR0 & RAISE_CE_BIT) == RAISE_CE_BIT ) {
		/* Check to see if CE bit is set */
		return CE_BIT_SET;
	} else if ( (DMA_DSR_BCR0 & RAISE_BES_BIT) == RAISE_BES_BIT ) {
		/* Check to see if the BES bit is set */
		return BES_BIT_SET;
	} else if( (DMA_DSR_BCR0 & RAISE_BED_BIT) == RAISE_BED_BIT ) {
		/* Check to see if the BED bit is set */
		return BED_BIT_SET;
	}

	return DMA_SUCCESSFUL;
}

dma_debug config_word_length(uint32_t length)
{
	/*Set the config. for a 32 bit increment.
	 * SINC = 1; DINC = 1
	 * SSIZE = 00; DSIZE = 00
	 */
	DMA_DCR0 = DCR_32_BIT_INCREMENTS;

	uint32_t temp_length = 0;
	temp_length = length * 4;

	DMA_DSR_BCR0 |= temp_length;
	return SUCCESS;

}

dma_debug config_word_length_memset(uint32_t length)
{
	/*Set the config. for a 32bit increment.
	 * SINC = 0; DINC = 1
	 * SSIZE = 00; DSIZE = 00
	 */
	DMA_DCR0 = DCR_32_BIT_INCREMENTS_MEMZERO;

	uint32_t temp_length = 0;
	temp_length = length * 4;

	DMA_DSR_BCR0 |= temp_length;
	return SUCCESS;

}

dma_debug config_one_byte_length(uint32_t length)
{
	/*3. First disable the DMAMUX_CHCFG0 register. */
	DMAMUX0_CHCFG0 = DISABLE_DMAMUX_CFG;

	/* Set the config. for a 8bit increment.
	 * SINC = 1; DINC = 1
	 * SSIZE = 01; DSIZE = 01
	 */
	DMA_DCR0 = DCR_8_BIT_INCREMENTS;

	/* 6. Store the Block size in the Byte Count Register
	 * The DMA_DSR_BCR register takes an input in the form of bits.
	 * But, the user specifies the input in terms of Bytes. So we need to
	 * multiply the input by either 4(32-bit) or 2(16-bit) to get a correct length.
	 */

#if 0
	if (temp_length != length) {
		return LENGTH_ERROR;
	}
#endif

	DMA_DSR_BCR0 |= length; //Need to confirm this!
	DMA_DSR_BCR0 |= length;

	return SUCCESS;
}

dma_debug config_one_byte_length_memset(uint32_t length)
{
	DMAMUX0_CHCFG0 = DISABLE_DMAMUX_CFG;

	/* Set the config. for a 8bit increment.
	 * SINC = 0; DINC = 1
	 * SSIZE = 01; DSIZE = 01
	 */
	DMA_DCR0 = DCR_8BIT_INCREMENTS_MEMZERO;

	DMA_DSR_BCR0 |= length; //Need to confirm this!
	DMA_DSR_BCR0 |= length;

	return SUCCESS;
}
dma_debug my_memzero_dma(uint8_t *src, uint32_t length)
{
	uint32_t set_zero = 0;

	/*1. Config. the clock gating register for DMAMUX clock gate register.*/
		SIM_SCGC6 |= ENABLE_CLOCK_GATE_DMAMUX;

	/*2. Enable DMA clock gate control */
		SIM_SCGC7 = ENABLE_CLOCK_GATE_DMA;

	/*3. First disable the DMAMUX_CHCFG0 register. */
		DMAMUX0_CHCFG0 = DISABLE_DMAMUX_CFG;

	/*4. Store the Source address in the DMA Source Register */
		DMA_SAR0 = (uint32_t)&set_zero;

	/*5. Store the Destination address in the DMA Destination Register */
		DMA_DAR0 = (uint32_t)src;

	/*Optimizing the transfer by breaking the transfer into words(32bits)*/
		uint32_t word_transfers = length/4;
		uint32_t word_remainder = length%4;

	/* First do the transfer of words*/
		if(word_transfers != 0) {
			/*Config DMA for word transfers*/
			config_word_length_memset(word_transfers);

			/*Start the word trasnfer*/
			dma_debug ret_handle;
			ret_handle = start_dma_transfer();
			if(ret_handle != DMA_SUCCESSFUL) {
				return ret_handle;
			}
		}

		if(word_remainder != 0) {
			/* we need to do these many 1B transfers.
			 * So, manage the config. accordingly.
			 */
			config_one_byte_length_memset(word_remainder);

			/*start the transfer of 1B data*/
			dma_debug ret_handle;
			ret_handle = start_dma_transfer();
			if(ret_handle != DMA_SUCCESSFUL) {
				return ret_handle;
			}
		}

		return DMA_SUCCESSFUL;
}
