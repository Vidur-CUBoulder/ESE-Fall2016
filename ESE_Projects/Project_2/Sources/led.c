#include "led.h"
#include "uart.h"

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

void turn_on_leds(uint8_t select)
{
	switch(select)
	{
				case 1:
						turn_off_all_leds();
						/*Turn on the Red Led*/
						GPIOB_PCOR = 0x00040000;
						break;

				case 2:
						turn_off_all_leds();
						/*Turn on the Green Led*/
						GPIOB_PCOR = 0x00080000;
						break;

				case 3:
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

				case 7:
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
