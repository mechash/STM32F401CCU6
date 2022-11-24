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

#include "uart.h"

/* Recalling the defined function */
static void uart_set_baudrate ( USART_TypeDef *USARTtx, uint32_t PeripheralCLK, uint32_t BaudRate );
static uint16_t compute_uart_bd ( uint32_t PeripheralCLK, uint32_t BaudRate );

/* Function to initializing the UART2  */
void uart2_init ( void ) {

	/*************** Configure UART GPIO Pin ***************/

	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA2 to alternate function mode for UART Tx */
	GPIOA->MODER |= ( 1U << 5 ) & ~( 1U << 4 );

	/* Set PA3 to alternate function mode for UART Rx */
	GPIOA->MODER |= ( 1U << 7 ) & ~( 1U << 6 );

	/* Set PA2 alternate function type to UART_TX (AF07) */
	/* 	GPIOA->AFR[0] |= ( 1U << 8 );
	      GPIOA->AFR[0] |= ( 1U << 9 );
	      GPIOA->AFR[0] |= ( 1U << 10 );
	      GPIOA->AFR[0] &= ~( 1U << 11 );
	   */
	GPIOA->AFR[0] |= ( ( ( 1U << 8 ) | ( 1U << 9 ) | ( 1U << 10 ) ) & ~( 1U << 11 ) );

	/* Set PA3 alternate function type to UART_RX (AF07) */
	GPIOA->AFR[0] |= ( ( ( 1U << 12 ) | ( 1U << 13 ) | ( 1U << 14 ) ) & ~( 1U << 15 ) );

	/**************** Configure UART Module ****************/

	/* Enable clock access to UART2 */
	RCC->APB1ENR |= UART2_EN;

	/* Configure baudrate */
	uart_set_baudrate ( USART2, APB1_CLK, UART_BAUDRATE );

	/* Configure the transfer direction */
	USART2->CR1 = CR1_TE | CR1_RE;

	/* Enable UART module */
	USART2->CR1 |= UR1_UE;
}

/* Function to transmit or to write single character or 8 bit of data */
void uart2_putChar ( int ch ) {
	/* Make sure the transmit data register is empty */
	while ( !( USART2->SR & SR_TXE ) ) {
	}
	/* Write to transmit data register */
	USART2->DR = ( ch & 0xFF );
}

/* Function to transmit a string (usually 40 character) */
void uart2_putStr ( char *p ) {
	while ( *p != '\0' ) {    /* unless the data store int the pointer is not null the code inside it will execute  */
		uart2_putChar ( *p ); /* sending the data of pointer per index to the function */
		p++;                  /* incrementing the pointer index by 1 */
	}
}

/* Function to receive /read a single character from the data register */
unsigned int uart2_getChar ( ) {
	/* Make sure the receive data register is not empty */
	while ( !( USART2->SR & SR_RXNE ) ) {
	}

	int int_char = USART2->DR;

	/* Return the data  */
	return int_char;
}

void uart2_getStr ( char *uart_buffer, unsigned char len ) {
	unsigned char data;
	for ( int i = 0; i <= len; i++ ) {

		data = uart2_getChar ( );
		*uart_buffer = data;
		uart_buffer++;
	}
}

/* Function for setting the UART Baudrate */
static void uart_set_baudrate ( USART_TypeDef *USARTtx, uint32_t PeripheralCLK, uint32_t BaudRate ) {
	USARTtx->BRR = compute_uart_bd ( PeripheralCLK, BaudRate );
}

static uint16_t compute_uart_bd ( uint32_t PeripheralCLK, uint32_t BaudRate ) {
	return ( ( PeripheralCLK + ( BaudRate / 2U ) ) / BaudRate );
}
