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
#pragma once

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOA_EN      ( 1U << 0 )  /* Enabling GPIOA */
#define UART2_EN      ( 1U << 17 ) /* Enabling UART2 */
#define CR1_TE        ( 1U << 3 )  /* Setting the USART2 Control Register Transmitter Enable  */
#define CR1_RE        ( 1U << 2 )  /* Setting the USART2 Control Register Receiver Enable */
#define UR1_UE        ( 1U << 13 ) /* Setting the USART2 Control Register USART Enable */
#define SR_TXE        ( 1U << 7 )  /* Setting the USART2 Status Register to watch TXE for emptying the data */
#define SR_RXNE       ( 1U << 5 )  /* Setting the USART Status Register to watch the RXNE for checking if data is not empty */
#define SYS_FREQ      16000000     /* System frequency */
#define APB1_CLK      SYS_FREQ     /* redefining macro  */

#define UART_BAUDRATE 115200 /* Setting the Baudrate */

/* Recalling the defined function */
void uart2_init ( void );
void uart2_putChar ( int ch );
void uart2_putStr ( char *p );
unsigned int uart2_getChar ( );
void uart2_getStr ( char *uart_buffer, unsigned char len );

