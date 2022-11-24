/*
 *   Copyright (c) 2022 Mechash
 *   All rights reserved.

 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:

 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.

 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 */
#include "adc.h"
#include "ms_delay.h"
#include "uart.h"

uint32_t sensor_value;
char buffer[40];

int main ( void ) {

	/* initialize uart for sending adc data to serial */
	uart2_init ( );
	/* initialize adc configuration */
	adc_init ( );
  /* start conversion */
	adc_begin_conversion ( );

	while ( 1 ) {

    /* Read and store ADC data */
		sensor_value = adc_read ( );
    /* Print or Send data through serial */
		sprintf ( buffer, "value of sensor = %d \n\r", (int)sensor_value );
		uart2_putStr ( buffer );
		ms_delay ( 500 );
	}

	return 0;
}