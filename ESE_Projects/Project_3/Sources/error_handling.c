/*
 * error_handling.c
 *
 *  Created on: Oct 26, 2016
 *      Author: vidur
 */

#include "error_handling.h"

void handle_errors(debug error_handle)
{
	switch(error_handle) {

		case SUCCESS: /*SUCCESS*/
				MY_LOG("Successful operation!\n");
				break;

		case DMA_SUCCESSFUL: /*DMA_SUCCESS*/
				MY_LOG("Successful DMA Operation!\n");
				break;

		case CE_BIT_SET: /*CE_BIT_SET*/
				MY_LOG("DMA operation failed! Please check the following:\n");
				MY_LOG(" 1. BCR, SAR, or DAR does not match the requested transfer size.\n");
				MY_LOG(" 2. Is a value greater than 0F_FFFFh written to BCR.\n");
				MY_LOG(" 3. Bits 31-20 of SAR or DAR are written with a value other than one of the allowed values.\n");
				MY_LOG(" 4. SSIZE or DSIZE is set to an unsupported value\n");
				MY_LOG(" 5. BCR equals 0 when the DMA receives a start condition\n");
				break;

		case BES_BIT_SET: /*BES_BIT_SET*/
				MY_LOG("DMA operation failed! Read on source failed.\n");
				break;

		case BED_BIT_SET: /*BED_BIT_SET*/
				MY_LOG("DMA operation failed! Write on destination failed.\n");
				break;

		case LENGTH_ERROR: /*LENGTH_ERROR*/
				MY_LOG("Input length too long! Please enter a shorter length for trasnfer.\n");
				break;

		default: /*UNKNOWN FAILURE*/
				MY_LOG("Unexpected failure occured!\n");
	}
}
