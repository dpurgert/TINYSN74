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

#ifndef SN74_ATTINY_X4_H
#define SN74_ATTINY_X4_H

/***********************************************************************
*               SPI and Clock pins for the ATMEGA 328.
*   Don't change these.  All user-modifiable pins are in max_config.h 
***********************************************************************/

/* SPI Pins */

/* SPI MOSI (ATTiny pin 7) -> SER (SN74 pin 14) */
#define SN_MOSI_PIN  PA6
#define SN_MOSI_PORT PORTA
#define SN_MOSI_DDR  DDRA

/* SPI MISO (ATTiny pin 8) -> SN74HC595 pin 12 */
//INPUT ONLY for SPI mode
#define SN_MISO_PIN  PA5
#define SN_MISO_PORT PORTA
#define SN_MISO_DDR  DDRA

/* SPI CLK (ATTiny pin 9) -> SRCLK ( SN74 pin 11) */
#define SN_CLK_PIN  PA4
#define SN_CLK_PORT PORTA
#define SN_CLK_DDR  DDRA



/* Rest of GPIO pins */

/* CLR (ATTiny pin 10) -> SRCLR (SN74 pin 10) */
#define SN_CLR_PIN  PA3
#define SN_CLR_PORT PORTA
#define SN_CLR_DDR  DDRA

/* Data Latch (ATTiny pin 6) -> SN74HC595 pin 12 */
#define SN_LAT_PIN  PA7
#define SN_LAT_PORT PORTA
#define SN_LAT_DDR  DDRA

#endif
