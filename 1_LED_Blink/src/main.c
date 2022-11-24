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

#include "ms_delay.h"
#include "stm32f4xx.h"

#define GPIOC_EN   ( 1U << 2 )                  /* Setting the 2nd bit of AHB1 RCC Register to enable the clock to GPIOC*/
#define INPUT_MODE ( 1U << 26 ) & ~( 1U << 27 ) /* Setting the 27th and 26th bit of the GPIOC MODER Register to 0 and 1 so the GPIO MODE is set as INPUT MODE */
#define PC13       ( 1U << 13 )                 /* Setting the 13th bit of the GPIOC ODR to turn on and off LED */


int main ( void ) {

	/* Enable clock for GPIOC */
	RCC->AHB1ENR |= GPIOC_EN;

	/* Set pin Mode */
	GPIOC->MODER |= INPUT_MODE;

	/* Infinite loop */
	while ( 1 ) {

		/* Set LED ON */
		GPIOC->ODR &= ~PC13;

		/* Delay for 2 sec */
		ms_delay ( 2000 );

		/* Set LED OFF */
		GPIOC->ODR |= PC13;

		/* Delay 2 sec */
		ms_delay ( 2000 );
	}
	return 0;
}