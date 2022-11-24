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

#define GPIOA_EN ( 1U << 0 )
#define GPIOC_EN ( 1U << 2 )
#define PA0_IN   ~( 1U << 0 ) & ~( 1U << 1 )
#define PC13_OUT ( 1U << 26 ) & ~( 1U << 27 )
#define PA0_PU   ( 1U << 0 ) & ~( 1U << 1 )
#define PA0      ( 1U << 0 )
#define PC13     ( 1U << 13 )
#define BTN      PA0
#define LED      PC13

int main ( ) {
	RCC->AHB1ENR |= GPIOA_EN | GPIOC_EN;

	GPIOA->MODER &= PA0_IN;
	GPIOC->MODER |= PC13_OUT;

	GPIOA->PUPDR |= PA0_PU;

	while ( 1 ) {

		if ( ( GPIOA->IDR & BTN ) != 0x1U ) {
			GPIOC->ODR &= ~LED;
		} else {
			GPIOC->ODR |= LED;
		}
	}
	return 0;
}