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

#ifndef CHIP_INC_H
#define CHIP_INC_H

/* Hopefully this'll pull in all the rest of the includes in the
 * pinouts directory ... maybe. */

#include <avr/io.h>

#ifndef PB0
#define PB0     PORTB0
#define PB1     PORTB1
#define PB2     PORTB2
#define PB3     PORTB3
#define PB4     PORTB4
#define PB5     PORTB5
#define PB6     PORTB6
#define PB7     PORTB7
#endif
#ifndef PC0
#define PC0     PORTC0
#define PC1     PORTC1
#define PC2     PORTC2
#define PC3     PORTC3
#define PC4     PORTC4
#define PC5     PORTC5
#define PC6     PORTC6
#define PC7     PORTC7
#endif
#ifndef PD0
#define PD0     PORTD0
#define PD1     PORTD1
#define PD2     PORTD2
#define PD3     PORTD3
#define PD4     PORTD4
#define PD5     PORTD5
#define PD6     PORTD6
#define PD7     PORTD7
#endif
#ifndef PH0
#define PH0     PORTH0
#define PH1     PORTH1
#define PH2     PORTH2
#define PH3     PORTH3
#define PH4     PORTH4
#define PH5     PORTH5
#define PH6     PORTH6
#define PH7     PORTH7
#endif

/* Chip Specific Pinouts */

#if defined (__AVR_ATtiny25__) 
  #include "ATtinyx5.h"
  #if NUMSN74 > 4
    #error "Tiny25 only has sufficient RAM for 4 chips."
  #endif
#elif defined (__AVR_ATtiny45__) 
  #include "ATtinyx5.h"
  #if NUMSN74 > 10
    #error "Tiny45 only has sufficient RAM for 10 chips."
  #endif
#elif defined (__AVR_ATtiny85__) 
  #include "ATtinyx5.h"
  #if NUMSN74 > 24
    #error "Tiny85 only has sufficient RAM for 24 chips."
  #endif
#if defined (__AVR_ATtiny24__) 
  #include "ATtinyx4.h"
  #if NUMSN74 > 4
    #error "Tiny24 only has sufficient RAM for 4 chips."
  #endif
#elif defined (__AVR_ATtiny44__) 
  #include "ATtinyx4.h"
  #if NUMSN74 > 10
    #error "Tiny44 only has sufficient RAM for 10 chips."
  #endif
#elif defined (__AVR_ATtiny84__) 
  #include "ATtinyx4.h"
  #if NUMSN74 > 24
    #error "Tiny85 only has sufficient RAM for 24 chips."
  #endif
#else
  #error "Unknown Chip!"
#endif

#endif
