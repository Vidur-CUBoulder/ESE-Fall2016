/*
 * error_handling.h
 *
 *  Created on: Oct 26, 2016
 *      Author: vidur
 */

#ifndef INCLUDES_ERROR_HANDLING_H_
#define INCLUDES_ERROR_HANDLING_H_

#include "log.h"

typedef enum debug_e {
	SUCCESS, //Generic Success enum.
	DMA_SUCCESSFUL,
	CE_BIT_SET,
	BES_BIT_SET,
	BED_BIT_SET,
	LENGTH_ERROR, //More than what is possible was entered!
} debug;

void handle_errors(debug error_handle);

#endif /* INCLUDES_ERROR_HANDLING_H_ */
