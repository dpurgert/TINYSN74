/***********************************************************************
*
*                 Program: Arduino SN74CH595 Library
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.6
*                    date: Fri, 19 Jul 2019 19:27:13 -0400
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
#define DEF_MOSI_PIN  PB0
#define DEF_MOSI_PORT PORTB
#define DEF_MOSI_DDR  DDRB

/* SPI MISO (ATTiny pin 6) -> SN74HC595 pin 12 */
//INPUT ONLY for SPI mode
#define DEF_MISO_PIN  PB1
#define DEF_MISO_PORT PORTB
#define DEF_MISO_DDR  DDRB

/* SPI CLK (ATTiny pin 7) -> SRCLK ( SN74 pin 11) */
#define DEF_CLK_PIN  PB2
#define DEF_CLK_PORT PORTB
#define DEF_CLK_DDR  DDRB



/* Rest of GPIO pins */

/* CLR (ATTiny pin 2) -> SRCLR (SN74 pin 10) */
#define DEF_CLR_PIN  PB3
#define DEF_CLR_PORT PORTB
#define DEF_CLR_DDR  DDRB

/* Data Latch (ATTiny pin 3) -> SN74HC595 pin 12 */
#define DEF_LAT_PIN  PB4
#define DEF_LAT_PORT PORTB
#define DEF_LAT_DDR  DDRB

#endif
