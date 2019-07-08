/***********************************************************************
*
*                 Program: Arduino SN74HC595 Library
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.5
*                    date: Sun, 21 Jan 2018 13:11:24 -0500
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

#ifndef SN74_CONFIG_H
#define SN74_CONFIG_H

#include <stdint.h>

/***********************************************************************
*                        USER OPTIONS
************************************************************************
*      These user-definable options are to customize the library
*      to your specific needs.  Options
*
*        - NUM_SN74 -- number of SN74HC595 units daisy-chained together.
*        NOTE that the datasheets do not indicate a maximum number that
*        one can daisy-chain.  
*
*        - DATA_XFER_MOD -- Data transfer mode, SPI (default), or
*        bit-banging.
*        
*        Pin Mapping:
*          - Digital Pins 0-7 == PORTD, PD0-7
*            NOTE - D0 = RXI / D1 = TX0
*          - Digital Pins 8-13 == PORTB, PB0-5
*          - Analog Pins 0-3 / Digital Pins 14-17 == PORTC0-3
***********************************************************************/


#define NUM_SN74     1

#define SN74_SPI     1
#define SN74_BANG    2
#define AVR_ATTINY   1


/* switch this to 'SN74_SPI' for SPI mode */
#define DATA_XFER_MOD SN74_BANG

/* Include chip pinouts.  Has to know XFER Mode, so can't include til
 * now. */
#include "pinouts/chips.h"

#define PWM_PERIOD 8192
#define CLK_PERIOD 3

/* Serial Digital in to  SN74 pin 14*/
#define DIN_PIN   SN_MOSI_PIN
#define DIN_PORT  SN_MOSI_PORT
#define DIN_DDR   SN_MOSI_DDR

/* Serial Clock to SN74 pin 11 */
#define CLK_PIN   SN_CLK_PIN
#define CLK_PORT  SN_CLK_PORT
#define CLK_DDR   SN_CLK_DDR





/***********************************************************************
*                          END USER OPTIONS
************************************************************************
*
*                 Don't change anything after here.
***********************************************************************/

/* Output Enable to SN74HC595 pin 13 */
#define OE_PIN   SN_OE_PIN
#define OE_PORT  SN_OE_PORT
#define OE_DDR   SN_OE_DDR

/* Serial Clear to SN74HC595 pin 10 */
#define CLR_PIN   SN_CLR_PIN
#define CLR_PORT  SN_CLR_PORT
#define CLR_DDR   SN_CLR_DDR

/* Data Latch to SN74HC595 pin 12 */
#define LAT_PIN   SN_LAT_PIN
#define LAT_PORT  SN_LAT_PORT
#define LAT_DDR   SN_LAT_DDR


#if !(DATA_XFER_MOD == SN74_SPI || DATA_XFER_MOD == SN74_BANG)
#error "Invalid DATA_XFER_MOD set. Review DATA_XFER_MOD options"
#endif


#endif
