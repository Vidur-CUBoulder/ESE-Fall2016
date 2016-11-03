#include "led.h"
#include "uart.h"
#include "parse_data.h"

/* This function configures the Red, Green and Blue LEDs on the
 * freedom board.
 */
void config_leds()
{
	/* 1. Enable the clock on PORTB & PORTD. */
	SIM_SCGC5 = 0x00001580;

	/* 2. Config. PTB for output to the LED */
	PORTB_PCR18 = 0x00000100;

	/* 3. Config. PTB pin 18 port data direction as output. */
	GPIOB_PDDR = 0x00040000;

	/* 4. Turn off the LED at pin 18. */
	GPIOB_PSOR = 0x00040000;

	/* 5. Config. pin 19 as GPIO */
	PORTB_PCR19 = 0x00000100;

	/* 6. Make pin 19 as the output pin */
	GPIOB_PDDR |= 0x00080000;

	/* 7. Turn off the led at pin 19 */
	GPIOB_PSOR = 0x00080000;

	/* 8. Config. pin 1, port D as GPIO */
	PORTD_PCR1 = 0x00000100;

	/* 9. Make pin 1 as output pin. */
	GPIOD_PDDR |= 0x00000002;

	/* 10. Turn off the led at pin1 */
	GPIOD_PSOR = 0x00000002;
}

void turn_off_all_leds()
{
	/* Turning off the led at pin 18 */
	GPIOB_PSOR = 0x00040000;

	/* Turn off the led at pin 19 */
	GPIOB_PSOR = 0x00080000;

	/* Turn off the led at pin1 */
	GPIOD_PSOR = 0x00000002;
}

void turn_on_leds(ledcolors color)
{
	switch(color)
	{
				case red:
						turn_off_all_leds();
						/*Turn on the Red Led*/
						GPIOB_PCOR = 0x00040000;
						break;

				case green:
						turn_off_all_leds();
						/*Turn on the Green Led*/
						GPIOB_PCOR = 0x00080000;
						break;

				case blue:
						turn_off_all_leds();
						/* Turn on the Blue Led*/
						GPIOD_PCOR = 0x00000002;
						break;

				case 4:
						turn_off_all_leds();
						/*Turn on the Red and Green Led*/
						GPIOB_PCOR = 0x00040000;
						GPIOB_PCOR = 0x00080000;
						break;

				case 5:
						turn_off_all_leds();
						/*Turn on the Red and Blue Led*/
						GPIOB_PCOR = 0x00040000;
						GPIOD_PCOR = 0x00000002;
						break;

				case 6:
						turn_off_all_leds();
						/*Turn on the Green and Blue Led*/
						GPIOB_PCOR = 0x00080000;
						GPIOD_PCOR = 0x00000002;
						break;

				case white:
						turn_off_all_leds();
						/*Turn on the Red, Green and Blue*/
						GPIOB_PCOR = 0x00040000;
						GPIOB_PCOR = 0x00080000;
						GPIOD_PCOR = 0x00000002;
						break;

				default: /* turn everything off! */
						turn_off_all_leds();
	}
}


void init_PWM_Blue(uint16_t pulse)
{
	int pulsewidth = 0;

		/* 1. Enable PORT D from the clock gating control register */
		SIM->SCGC5 |= 0x00001000;

		/* 2. Select the alternative for the Blue LED*/
		PORTD->PCR[1] = 0x0400;

		/* 3. Enable TPM0 from the clock gating control register */
		SIM->SCGC6 = 0x01000000;

		/* 4. Select the clock source for TPM0 */
		SIM->SOPT2 |= 0x01000000;

		/* 5. Clear the status and control register before beginning */
		TPM0->SC = 0;

		/* 6. Modify the channel status and control register
		 * 	a. ELSB and ELSA : 11 : set on match-up and clear on match-down
		 * 	b. MSB and MSA : 10 : Channel Mode Select
		 */
		TPM0->CONTROLS[1].CnSC = 0x2C;

		/* 7. Set the maximum modulus value */
		TPM0->MOD = 0xFFFF;

		/* 8. Configure the timer to increment on every counter clock */
		TPM0->SC = 0x08;

		/* 9. CnV value directly controls the pulse width of the timer
		 * modifying this will lead to an increase in the brightness of the LEDs*/
		TPM0->CONTROLS[1].CnV = pulse;

		return;
}


void init_PWM_Red(uint16_t pulse)
{
	int pulsewidth = 0;

	/* 1. Enable PORT B from the system control register */
	SIM->SCGC5 |= 0x00000400;

	/* 2. Select the alternative for the RED LED */
	PORTB->PCR[18] |= 0x00000300;

	/* 3. Enable TPM2 from the system clock gating registers */
	SIM->SCGC6 = 0x04000000;

	/* 4. Select the clock source for TPM2 */
	SIM->SOPT2 |= 0x01000000;

	/* 5. Clear the status and control register before beginning */
	TPM2->SC = 0;

	/* 6. Modify the channel status and control register
	 * 	a. ELSB and ELSA : 11 : set on match-up and clear on match-down
	 * 	b. MSB and MSA : 10 : Channel Mode Select
	 */
	TPM2->CONTROLS[0].CnSC = 0x2C;

	/* 7. Set the maximum modulus value */
	TPM2->MOD = 0xFFFF;

	/* 8. Configure the timer to increment on every counter clock */
	TPM2->SC = 0x08;

	/* 9. CnV value directly controls the pulse width of the timer
	 * modifying this will lead to an increase in the brightness of the LEDs*/
	TPM2->CONTROLS[0].CnV = pulse;

	return;
}


void init_PWM_Green(uint16_t pulse)
{
	int pulsewidth = 0;

	/* 1. Enable PORTB from the system control register */
	SIM->SCGC5 |= 0x00000400;

	/* 2. Select the alternative for the Green LED */
	PORTB->PCR[19] |= 0x00000300;

	/* 3. Enable TPM2 from the system clock gating registers */
	SIM->SCGC6 = 0x04000000;

	/* 4. Select the clock source for TPM2 */
	SIM->SOPT2 |= 0x01000000;

	/* 5. Clear the status and control register before beginning */
	TPM2->SC = 0;

	/* 6. Modify the channel status and control register
	 * 	a. ELSB and ELSA : 11 : set on match-up and clear on match-down
	 * 	b. MSB and MSA : 10 : Channel Mode Select
	 */
	TPM2->CONTROLS[1].CnSC = 0x2C;

	/* 7. Set the maximum modulus value */
	TPM2->MOD = 0xFFFF;

	/* 8. Configure the timer to increment on every counter clock */
	TPM2->SC = 0x08;

	/* 9. CnV value directly controls the pulse width of the timer
	 * modifying this will lead to an increase in the brightness of the LEDs*/
	TPM2->CONTROLS[1].CnV = pulse;

	return;
}

