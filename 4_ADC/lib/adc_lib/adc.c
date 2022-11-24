/*
 *   Copyright (c) 2022 MechAsh
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

void adc_init ( void ) {
	/***Configure the ADC GPIO Pin***/
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set the mode of PA1 to Analog */
	GPIOA->MODER |= ( ( 1U << 1 ) | ( 1U << 0 ) );

	/***Configure the ADC Module***/
	/* Enable the clock access to ADC */
	RCC->APB2ENR |= ADC1_EN;

	/* Conversion sequence start */
	ADC1->SQR3 = ADC_CH1;

	/* Conversion sequence length */
	ADC1->SQR3 = ADC_SEQ_CH1;

	/* Enable ADC Module */
	ADC1->CR2 |= ADC_CR2_ON;
}

void adc_begin_conversion ( void ) {
  /* Enable ADC Continuous Conversion */
	ADC1->CR2 |= ADC_SR_CONT;
	/* Start ADC Conversion */
	ADC1->CR2 |= ADC_SW_START;
}

uint32_t adc_read ( void ) {
	/* Wait for conversion to be compleat */
	while ( !( ADC1->SR & ADC_SR_ECO ) ) {
	}

	/* Read converted result */
	return ( ADC1->DR );
}