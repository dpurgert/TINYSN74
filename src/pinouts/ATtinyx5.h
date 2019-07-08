/***********************************************************************
*
*                 Program: Arduino SN74CH595 Library
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.1
*                    date: Mon, 08 Jan 2018 14:46:33 EDT
*                 purpose: Library for the SN74HC595 shift register, as
*                        : it's readily available from suppliers
*
*                 license: GPL v2 (only)
*              repository: http://github.com/dpurgert
*
*  This program is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
*  02110-1301, USA.
***********************************************************************/

#ifndef SN74_ATTINY_X5_H
#define SN74_ATTINY_X5_H

/***********************************************************************
*               SPI and Clock pins for the ATMEGA 328.
*   Don't change these.  All user-modifiable pins are in max_config.h 
***********************************************************************/

/* SPI Pins */

/* SPI MOSI (ATTiny pin 5) -> SER (SN74 pin 14) */
#define SN_MOSI_PIN  PB0
#define SN_MOSI_PORT PORTB
#define SN_MOSI_DDR  DDRB

/* SPI SS (ATTiny pin 6) : SN74HC595 pin 12 */
// Borrowing MISO - default unused
#define SN_SS_PIN  PB1
#define SN_SS_PORT PORTB
#define SN_SS_DDR  DDRB

/* SPI CLK (ATTiny pin 7) -> SRCLK ( SN74 pin 11) */
#define SN_CLK_PIN  PB2
#define SN_CLK_PORT PORTB
#define SN_CLK_DDR  DDRB



/* Rest of GPIO pins */

/* CLR (ATTiny pin 2) -> SRCLR (SN74 pin 11) */
#define SN_CLR_PIN  PB3
#define SN_CLR_PORT PORTB
#define SN_CLR_DDR  DDRB

/* Data Latch (ATTiny pin 3) : SN74HC595 pin 12 */
#define SN_LAT_PIN  PB4
#define SN_LAT_PORT PORTB
#define SN_LAT_DDR  DDRB

/* Output Enable (ATTiny pin 6) : SN74HC595 pin 13 */
// Default unused
#define SN_OE_PIN  PB2
#define SN_OE_PORT PORTB
#define SN_OE_DDR  DDRB

#endif 
