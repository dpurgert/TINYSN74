/***********************************************************************
*
*                 Program: Arduino SN74HC595 Library
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
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

/**
 * @file
 * @brief Master configuration file for the tinysn74 library.
 *
 * This file holds the (mostly) static definitions used in the rest of
 * the library. 
*/
#ifndef SN74_CONFIG_H
#define SN74_CONFIG_H

#include <stdint.h>

// DO NOT TOUCH THESE TWO.  See below "USER OPTIONS" for configurable
// settings
#define SN74_SPI     1 
#define SN74_BANG    2


/***********************************************************************
*                        USER OPTIONS
************************************************************************
* These two options are the "basic" options that most users of the
* library will (hopefully) ever have need to change.  See "Chip Options"
* section below if you do need to change pinouts.

*  - NUMSN74 -- number of SN74HC595 units daisy-chained together. NOTE
*  that the datasheets do not indicate a maximum number that one can
*  daisy-chain.
*
*  - SN74OE -- select whether the microcontroller will or will not be in
*  control of the OE pin (default NO).
*        
***********************************************************************/

#define NUMSN74 2 

  /* GENERAL GUIDELINE, based on RAM / program size.  I don't have
  * enough LEDs (much less the SN74's) to test these out completely. 
  *   - TINY24/25 = 65 chips max ( 520 LEDs). 2.6A @ 5mA / LED
  *   - TINY44/45 = 160 chips max (1280 LEDs). 6.4A @ 5mA / LED         
  *   - TINY84/85 = 360 chips (2880 LEDs).  REQUIRES ADD'L CHANGES TO
  *   tinysn74.h AND tinysn74.c to accommodate >255 chips.
  *
  *  TODO - replace "NUMSN74" with a bank variable that allows us to set
  *  based on a word (16 bits) rather than just a byte. Easier maths for
  *  all!
  */

#define SN74OE	0


/***********************************************************************
*                         CHIP OPTIONS
************************************************************************
* 
* These options are for more "advanced" configurations where the default
* pinout (or data transfer mode) does not fit your use case.  
*
***********************************************************************/
/* switch this to 'SN74_SPI' for SPI mode */
#define DATA_XFER_MOD SN74_BANG 

/* Include chip pinouts.  Has to know XFER Mode, so can't include til
 * now. */
#include "pinouts/chips.h"

/* Serial Digital in to  SN74 pin 14*/
#define DOT_PIN   DEF_MOSI_PIN
#define DOT_PORT  DEF_MOSI_PORT
#define DOT_DDR   DEF_MOSI_DDR

/* Serial Clock to SN74 pin 11 */
#define CLK_PIN   DEF_CLK_PIN
#define CLK_PORT  DEF_CLK_PORT
#define CLK_DDR   DEF_CLK_DDR


/* Output Enable to SN74HC595 pin 13 */
//only valid for bitbang mode.
#if SN74OE == 1 
  #if DATA_XFER_MOD == SN74_BANG
    #define OE_PIN   DEF_MISO_PIN
    #define OE_PORT  DEF_MISO_PORT
    #define OE_DDR   DEF_MISO_DDR
  #else //DATA_XFER_MOD == SN74_SPI
    #error "Output Enable requires DATA_XFER_MODE == SN74_BANG"
  #endif //DataXferMod
#endif //SN74OE


/* Serial Clear to SN74HC595 pin 10 */
#define CLR_PIN   DEF_CLR_PIN
#define CLR_PORT  DEF_CLR_PORT
#define CLR_DDR   DEF_CLR_DDR

/* Data Latch to SN74HC595 pin 12 */
#define LAT_PIN   DEF_LAT_PIN
#define LAT_PORT  DEF_LAT_PORT
#define LAT_DDR   DEF_LAT_DDR


#if !(DATA_XFER_MOD == SN74_SPI || DATA_XFER_MOD == SN74_BANG)
#error "Invalid DATA_XFER_MOD set. Review DATA_XFER_MOD options"
#endif


#endif
