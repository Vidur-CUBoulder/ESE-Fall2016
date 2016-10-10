/*
 * timer.c
 *
 *  Created on: Oct 7, 2016
 *      Author: vidur
 */

#include "timer.h"
#include "MKL25Z4.h"

/* Configure the counter register */

void counter_init()
{
	/* 1. enable the system clock gating control register
	 * to config TPM 0
	 */
	SIM_SCGC6 = 0x01000000;

	/* 2. Config the systems options register to select the TPM
	 * source clock as MCGFLLCLK
	 */
	SIM_SOPT2 |= 0x01000000;

	/* 3. Disable the timer while doing the clock configurations.
	 * We need to disbale all the bits in the status and control
	 * register
	 */
	TPM0_SC = 0x00000000;

	/* 4. Writing to the CNT register to clear its value */
	TPM0_CNT = 0x00000000;

	/* 5. Set the Max Modulo Value */
	TPM0_MOD = 0xFFFF;

	/* 6. Clear the Timer Overflow Flag(TOF) */
	TPM0_SC = 0x80;

}

void start_counter()
{
	/* This will start the TPM counter */
	TPM0_SC = 0x08;
}

void stop_counter()
{
	/* Stop the counter! */
	TPM0_SC = 0x00;
}
