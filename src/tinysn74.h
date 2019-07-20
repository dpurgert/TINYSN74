/***********************************************************************
*
*                 Program: Arduino SN74HC595 Library - sn74.h
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

#ifndef SN74_H
#define SN74_H

#include <stdint.h>
#include "tinysn74_config.h"

#ifdef __cplusplus 
extern "C" {
#endif

/* Latch pulse setup.  Apparently required for when using separate pins
 * for latch (RCLK) and clock (SRCLK) clocking.
 * 
 * Commenting out for now because I have no idea if this is actually
 * necessary on the Tinies after reading other ATTinyx5 SPI libraries.
*/
/** Enable Timer1 Overflow interrupt, which fires after a LAT pulse; and 
    disable any Timer1 interrupts. */
//#define setLATinterrupt()    TIFR1 |= _BV(TOV1); TIMSK = _BV(TOIE1)
//#define clearLATinterrupt() TIMSK = 0

/** Enables Latch pulses */
//#define enableLATpulse()    TCCR0A = _BV(COM1A1) | _BV(COM1B1)

/** Disables latch pulses */
//#define disableLATpulse() TCCR0A = _BV(COM1B1)

// snInit - Initialize basic pins, etc. for communication.
void snInit (void);

//snCLR - clear the output register of the SN74 chip(s)
void snCLR (void);

//snOE - OPTIONAL function to enable / disable outputs on the SN chips.
// inverse logic, so setting to '1' = off. If you don't like it,
// complain to TI :)
void snOE (uint8_t off); 

//snShiftInit - Initialize the actual shifting.
//not 100% necessary to break it out of snInit - but it got hard to read
//with the bitbang vs. SPI code.  
void snShiftInit (void);

/*snShift - perform the data shift out to the SN chips.
*  *b - pointer to a byte array that holds the data we're outputting.
*  Normally we'd need to know the length too, but that's handled by
*  NUMSN74 in tinysn74_config.h
*/
void snShift (uint8_t *b);

// snLat - trigger a latch pulse.  This kicks the data from the serial
// input register out to the "storage register" (i.e. the pins)
void snLat (void);

#ifdef __cplusplus
}
#endif
#endif
