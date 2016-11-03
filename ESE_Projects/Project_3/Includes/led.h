#include <stdint.h>

void config_leds();

void turn_on_leds(uint8_t counter);

void turn_off_all_leds();

void init_PWM_Blue(uint16_t pulse);

void init_PWM_Red(uint16_t pulse);

void init_PWM_Green(uint16_t pulse);
