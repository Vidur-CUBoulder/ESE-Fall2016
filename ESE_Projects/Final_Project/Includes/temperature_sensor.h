/*
 * temperature_sensor.h
 *
 *  Created on: Nov 27, 2016
 *      Author: vidur
 */

#include "main.h"

#ifndef INCLUDES_TEMPERATURE_SENSOR_H_
#define INCLUDES_TEMPERATURE_SENSOR_H_

#define ENABLE_CLK_ADC0 0x08000000
#define ENABLE_SOFTWARE_TRIGGER (~0x40)
#define SET_CLOCK_RATIO 0x40
#define SET_LONG_SAMPLE_PERIODS 0x10
#define SELECT_12_BIT_CONVERSION_MODE 0x04
#define SELECT_BUS_CLK 0x00

#define WAIT_FOR_CONVERSION_COMPLETION (!(ADC0_SC1A & 0x80))

/*Function: Init_Temp_Sensor(void)
 * Parameters: void
 * Return: void
 * Description: Used to initialize the onboard temperature sensor
 *              on the FRDM board.
 */
void Init_Temp_Sensor(void);

/*Function: Read_Temp_Sensor_Value(uint16_t *value_read)
 * Parameters: Pass the variable in which you want the read
 *              value of the ADC to be stored.
 * Return: nothing for the moment. May implement a debugging enum for this.
 * Description: Used to read the internal temperature value of the FRDM board.
 *              It will return the value that is read.
 */
uint8_t Read_Temp_Sensor_Value(uint16_t *value_read);

#endif /* INCLUDES_TEMPERATURE_SENSOR_H_ */
