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

#include "systick_delay.h"


void systickDelayMs ( int delay ) {
	/* Configure Systick */

	/* Reload with number of clock per millisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;

	/* Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for ( int i = 0; i < delay; i++ ) {
		/* wait until the COUNTFLAG is set */
		while ( ( SysTick->CTRL & CTRL_COUNTFLAG ) == 0 ) {
		}
	}
	SysTick->CTRL = 0;
}