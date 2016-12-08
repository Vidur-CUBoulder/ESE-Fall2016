/*
 * error_handling.c
 *
 *  Created on: Oct 26, 2016
 *      Author: vidur
 */

#include "error_handling.h"
#include "nRF.h"

void handle_nRF_errors(errors error_handle)
{
    switch(error_handle) {

        case SUCCESSFUL: /* Generic Success Output */
                         MY_LOG("Successful Operation!\n");

        case INCORRECT_ENTRY: /* Wrong Entry returned from the function */
                         MY_LOG("Incorrect parameter entry passed to the function!\n");

        case NULL_FAILURE: /* returned from a NULL check */
                         MY_LOG("Value passed to the function was NULL!\n");

        case INVALID: /* Generic Invalid flag */
                         MY_LOG("Invalid data retured from the function!\n");

        case PTX_CONFIG_SUCCESSFUL: /* the PTX module was successfully configured! */
                         MY_LOG("The Trasnmit nRF module was successfully configured!\n");

        case PRX_CONFIG_SUCCESSFUL: /* the PRX module was successfully configured! */
                         MY_LOG("The Receive nRF module was successfully configured!\n");

        case BUFFER_FILLED: /* The data buffer in the TX buffer was filled with the data */
                         MY_LOG("TX module filled with the data to be transmitted!\n");

        case nRF_READ_SUCCESSFUL: /* value successfully read from the nRF module! */
                         MY_LOG("The value was successfully read from the nRF module!\n");

       // case nRF_READ_FAULIRE: /* value read failed! */
                         //MY_LOG("Unable to read the value form the nRF register!\n");

        case nRF_MODULES_ON: /* Both the nRF modules were turned on */
                         MY_LOG("Both the nRF modules were turned on and are ready for trasception\n");

        case nRF_MODULES_OFF: /* Both the nRF modules are now off */
                         MY_LOG("Both the nRF modules are now off. STANDBY-II mode!\n");

        case nRF_MODULES_SUCCESSFULLY_INIT: /* Both the modules have been successfully initialized! */
                         MY_LOG("Both modules have been successfully initialized!\n");

        default:
                         MY_LOG("Invalid data retured from the function!\n");

        }
}


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
