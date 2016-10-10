
#include "MKL25Z4.h"

void init_uart();

void config_transmit();

void config_receive();

void disable_Tx_Rx();

void wait_for_buffer_empty();

void wait_for_buffer_full();

void write_to_buffer();

void delay(uint8_t value);

//void UART0_IRQHandler();
