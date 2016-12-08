/*
 * temperature_sensor.c
 *
 *  Created on: Nov 27, 2016
 *      Author: vidur
 */

#include "temperature_sensor.h"
#include "MKL25Z4.h"

void Init_Temp_Sensor(void)
{
    /* 1. Provide the clock to the ADC. */
    SIM_SCGC6 |= ENABLE_CLK_ADC0;

    /* 2. Config the software trigger for the ADC 
     * trigger will be init. following a write to SCA1*/
    ADC0_SC2 &= ENABLE_SOFTWARE_TRIGGER;

    /* 3. Do the following setting on the ADC:
     *  a. Set the clock divide ratio to clk/4
     *  b. Select the long sample time for the ADC
     *  c. Conversion mode: 12-bit single ended conversion
     *  d. Clock select: the bus clock.
     */
    ADC0_CFG1 =  SET_CLOCK_RATIO | SET_LONG_SAMPLE_PERIODS\
                 | SELECT_10_BIT_CONVERSION_MODE | SELECT_BUS_CLK;

}

uint8_t Read_Temp_Sensor_Value(float *value_read)
{
    ADC0_SC1A = TEMP_SENSOR_CHANNEL; // Select the channel for the temp. sensor.
    while(WAIT_FOR_CONVERSION_COMPLETION);
    *value_read = ADC0_RA;

    float Vtemp = 0.00;
    float Final_Temp = 0;
    Vtemp = *(value_read) * 0.0029296875;

    if(Vtemp >= 0.7012) {
    	*value_read = 25 - ((Vtemp - 0.7012)/0.001646);
    } else {
    	*value_read = 25 -((Vtemp - 0.7012)/0.001749);
    }
}


